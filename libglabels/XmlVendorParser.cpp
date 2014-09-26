/*  XmlVendorParser.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "XmlVendorParser.h"

#include <QFile>
#include <QDomDocument>
#include <QDomNode>
#include <iostream>

#include "Vendor.h"
#include "XmlUtil.h"
#include "Db.h"


namespace libglabels
{

	bool XmlVendorParser::readFile( const QString &fileName )
	{
		QFile file( fileName );

		if ( !file.open( QFile::ReadOnly | QFile::Text) )
		{
			std::cerr << "Error: Cannot read file " << qPrintable(fileName)
			          << ": " << qPrintable(file.errorString())
			          << std::endl;
			return false;
		}


		QDomDocument doc;
		QString      errorString;
		int          errorLine;
		int          errorColumn;

		if ( !doc.setContent( &file, false, &errorString, &errorLine, &errorColumn ) )
		{
			std::cerr << "Error: Parse error at line " << errorLine
				  << "column " << errorColumn
				  << ": " << qPrintable(errorString)
				  << std::endl;
			return false;
		}

		QDomElement root = doc.documentElement();
		if ( root.tagName() != "Glabels-vendors" )
		{
			std::cerr << "Error: Not a Glabels-vendors file" << std::endl;
			return false;
		}

		parseRootNode( root );
		return true;
	}


	void XmlVendorParser::parseRootNode( const QDomElement &node )
	{
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Vendor" )
			{
				parseVendorNode( child.toElement() );
			}
			else if ( !child.isComment() )
			{
				std::cerr << "Warning: bad element: " << qPrintable(child.toElement().tagName())
					  << ", Ignored"
					  << std::endl;
			}
		}
	}


	void XmlVendorParser::parseVendorNode( const QDomElement &node )
	{
		QString name = XmlUtil::getStringAttr( node, "name", "" );
		QString url  = XmlUtil::getStringAttr( node, "url", "" );

		Vendor *vendor = new Vendor( name, url );
		if ( vendor != NULL )
		{
			Db::registerVendor( vendor );
		}
	}

}

