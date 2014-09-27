/*  XmlUtil.cpp
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

#include "XmlUtil.h"

#include <QTextStream>
#include <QtDebug>


namespace libglabels
{

	Units *XmlUtil::mDefaultUnits;


	QString XmlUtil::getStringAttr( const QDomElement& node,
					const QString&     name,
					const QString& default_value )
	{
		return node.attribute( name, default_value );
	}


	double XmlUtil::getDoubleAttr( const QDomElement& node,
				       const QString&     name,
				       double             default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			double value = valueString.toDouble(& ok );

			if ( !ok )
			{
				qWarning() << "Error: bad double value in attribute "
					   << node.tagName() << ":" << name
					   << " : " << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	bool XmlUtil::getBoolAttr( const QDomElement& node,
				   const QString&     name,
				   bool               default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			int intValue = valueString.toInt();

			if ( (valueString == "True") ||
			     (valueString == "TRUE") ||
			     (valueString == "true") ||
			     (intValue == 1) )
			{
				return true;
			}

			if ( (valueString == "False") ||
			     (valueString == "FALSE") ||
			     (valueString == "false") ||
			     (intValue == 0) )
			{
				return false;
			}

			qWarning() << "Error: bad boolean value in attribute "
				   << node.tagName() << ":" << name
				   << " : " << valueString;
			return default_value;
		}

		return default_value;
	}


	int XmlUtil::getIntAttr( const QDomElement& node,
				 const QString&     name,
				 int                default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			int value = valueString.toInt(& ok );

			if ( !ok )
			{
				qWarning() << "Error: bad integer value in attribute "
					   << node.tagName() << ":" << name
					   << " : " << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	uint32_t XmlUtil::getUIntAttr( const QDomElement& node,
				       const QString&     name,
				       uint32_t           default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			// TODO: Does base-0 do what we want?  I.e. use base determined by format e.g. "0xff"
			bool ok;
			uint32_t value = valueString.toInt(& ok, 0 );

			if ( !ok )
			{
				qWarning() << "Error: bad unsigned integer value in attribute "
					   << node.tagName() << ":" << name
					   << " : " << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	QString  XmlUtil::getI18nAttr( const QDomElement& node,
				       const QString&     name,
				       const QString&     default_value )
	{
		// TODO: are translations done in a compatable way, so that we can use "_name" attributes?
		QString i18nString = node.attribute( QString("_").append(name), "" );

		if ( i18nString == "" )
		{
			return node.attribute( name, default_value );
		}

		return i18nString;
	}


	double XmlUtil::getLengthAttr( const QDomElement& node,
				       const QString&     name,
				       double             default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			double value;
			QString unitsString;
			QTextStream valueStream( &valueString, QIODevice::ReadOnly );

			valueStream >> value >> unitsString;

			if ( !Units::isIdValid( unitsString ) )
			{
				qWarning() << "Error: bad length value in attribute "
					   << node.tagName() << ":" <<  name
					   << " : " << valueString;
				return default_value;
			}

			Units *units = Units::fromId( unitsString );

			return value * units->pointsPerUnit();
		}

		return default_value;
	}


	void XmlUtil::setStringAttr( const QDomElement& node,
				     const QString&     name,
				     const QString&     value )
	{
		// TODO
	}


	void XmlUtil::setDoubleAttr( const QDomElement& node,
				     const QString&     name,
				     double             value )
	{
		// TODO
	}


	void XmlUtil::setBoolAttr( const QDomElement& node,
				   const QString&     name,
				   bool               value )
	{
		// TODO
	}


	void XmlUtil::setIntAttr( const QDomElement& node,
				  const QString&     name,
				  int                value )
	{
		// TODO
	}


	void XmlUtil::setUIntAttr( const QDomElement& node,
				   const QString&     name,
				   uint32_t           value )
	{
		// TODO
	}


	void XmlUtil::setLengthAttr( const QDomElement& node,
				     const QString&     name,
				     double             value )
	{
		// TODO
	}

}
