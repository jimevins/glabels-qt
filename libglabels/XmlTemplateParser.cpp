/*  XmlTemplateParser.cpp
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

#include "XmlTemplateParser.h"

#include <QFile>
#include <QDomDocument>
#include <QDomNode>
#include <iostream>

#include "Template.h"
#include "XmlUtil.h"
#include "Db.h"
#include "FrameRect.h"
#include "FrameCd.h"
#include "FrameRound.h"
#include "FrameEllipse.h"
#include "Layout.h"
#include "Markup.h"


namespace libglabels
{

	bool XmlTemplateParser::readFile( const QString &fileName )
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
		if ( root.tagName() != "Glabels-templates" )
		{
			std::cerr << "Error: Not a Glabels-templates file" << std::endl;
			return false;
		}

		parseRootNode( root );
		return true;
	}


	void XmlTemplateParser::parseRootNode( const QDomElement &node )
	{
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Template" )
			{
				Template *tmplate = parseTemplateNode( child.toElement() );
				if ( tmplate != NULL )
				{
					Db::registerTemplate( tmplate );
				}
				else
				{
					std::cerr << "Warning: could not create template, Ignored." << std::endl;
				}
			}
			else if ( !child.isComment() )
			{
				std::cerr << "Warning: bad element: " << qPrintable(child.toElement().tagName())
					  << ", Ignored"
					  << std::endl;
			}
		}
	}


	Template *XmlTemplateParser::parseTemplateNode( const QDomElement &node )
	{
		QString brand = XmlUtil::getAttr( node, "brand", "" );
		QString part  = XmlUtil::getAttr( node, "part", "" );

		if ( (brand == "") || (part == "") )
		{
			// Try the deprecated "name" attribute.
			QString name = XmlUtil::getAttr( node, "name", "" );
			if ( name != "" )
			{
				QStringList fields = name.split( " " );
				brand = fields[0];
				part  = fields[1];
			}
			else
			{
				std::cerr << "Error: missing name or brand/part attributes." << std::endl;
				return NULL;
			}
		}


		Template *tmplate = NULL;

		QString equivPart = XmlUtil::getAttr( node, "equiv", "" );
		if ( equivPart != NULL )
		{
			tmplate = Template::fromEquiv( brand, part, equivPart );

			for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
			{
				if ( child.toElement().tagName() == "Meta" )
				{
					parseMetaNode( child.toElement(), tmplate );
				}
				else if ( !child.isComment() )
				{
					std::cerr << "Warning: bad element: " << qPrintable(child.toElement().tagName())
						  << ", Ignored"
						  << std::endl;
				}
			}
		}
		else
		{
			QString description = XmlUtil::getAttrI18n( node, "description", "" );
			QString paperId     = XmlUtil::getAttr( node, "size", "" );

			if ( !Db::isPaperIdOther( paperId ) )
			{
				const Paper *paper = Db::lookupPaperFromId( paperId );
				if ( paper == NULL )
				{
					std::cerr << "Error: unknown paper ID: " << qPrintable( paperId ) << std::endl;
					return NULL;
				}

				tmplate = new Template( brand, part, description,
							paper->id(), paper->width(), paper->height() );
			}
			else
			{
				double width  = XmlUtil::getAttrLength( node, "width", 0 );
				double height = XmlUtil::getAttrLength( node, "height", 0 );

				tmplate = new Template( brand, part, description, paperId, width, height );
			}

			for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
			{
				if ( child.toElement().tagName() == "Meta" )
				{
					parseMetaNode( child.toElement(), tmplate );
				}
				else if ( child.toElement().tagName() == "Label-rectangle" )
				{
					parseLabelRectangleNode( child.toElement(), tmplate );
				}
				else if ( child.toElement().tagName() == "Label-ellipse" )
				{
					parseLabelEllipseNode( child.toElement(), tmplate );
				}
				else if ( child.toElement().tagName() == "Label-round" )
				{
					parseLabelRoundNode( child.toElement(), tmplate );
				}
				else if ( child.toElement().tagName() == "Label-cd" )
				{
					parseLabelCdNode( child.toElement(), tmplate );
				}
				else if ( !child.isComment() )
				{
					std::cerr << "Warning: bad element: " << qPrintable(child.toElement().tagName())
						  << ", Ignored"
						  << std::endl;
				}
			}
		}

		return tmplate;
	}


	void XmlTemplateParser::parseMetaNode( const QDomElement &node, Template *tmplate )
	{
		QString productUrl = XmlUtil::getAttr( node, "product_url", "" );
		if ( productUrl != "" )
		{
			tmplate->setProductUrl( productUrl );
		}
		
		QString categoryId = XmlUtil::getAttr( node, "category", "" );
		if ( categoryId != "" )
		{
			tmplate->addCategory( categoryId );
		}
	}


	void XmlTemplateParser::parseLabelRectangleNode( const QDomElement &node, Template *tmplate )
	{
		QString id = XmlUtil::getAttr( node, "id", "0" );

		double w   = XmlUtil::getAttrLength( node, "width", 0 );
		double h   = XmlUtil::getAttrLength( node, "height", 0 );
		double r   = XmlUtil::getAttrLength( node, "round", 0 );

		double xWaste, yWaste;

		double waste = XmlUtil::getAttrLength( node, "waste", -1 );
		if ( waste >= 0 )
		{
			xWaste = waste;
			yWaste = waste;
		}
		else
		{
			xWaste = XmlUtil::getAttrLength( node, "x_waste", 0 );
			yWaste = XmlUtil::getAttrLength( node, "y_waste", 0 );
		}

		Frame *frame = new FrameRect( w, h, r, xWaste, yWaste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelEllipseNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getAttr( node, "id", "0" );

		double  w     = XmlUtil::getAttrLength( node, "width", 0 );
		double  h     = XmlUtil::getAttrLength( node, "height", 0 );
		double  waste = XmlUtil::getAttrLength( node, "waste", -1 );

		Frame *frame = new FrameEllipse( w, h, waste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelRoundNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getAttr( node, "id", "0" );

		double  r     = XmlUtil::getAttrLength( node, "radius", 0 );
		double  waste = XmlUtil::getAttrLength( node, "waste", -1 );

		Frame *frame = new FrameRound( r, waste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelCdNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getAttr( node, "id", "0" );

		double  r1    = XmlUtil::getAttrLength( node, "radius", 0 );
		double  r2    = XmlUtil::getAttrLength( node, "hole", 0 );
		double  w     = XmlUtil::getAttrLength( node, "width", 0 );
		double  h     = XmlUtil::getAttrLength( node, "height", 0 );
		double  waste = XmlUtil::getAttrLength( node, "waste", -1 );

		Frame *frame = new FrameCd( r1, r2, w, h, waste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelNodeCommon( const QDomElement &node, Frame *frame )
	{
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Layout" )
			{
				parseLayoutNode( child.toElement(), frame );
			}
			else if ( child.toElement().tagName() == "Markup-margin" )
			{
				parseMarkupMarginNode( child.toElement(), frame );
			}
			else if ( child.toElement().tagName() == "Markup-line" )
			{
				parseMarkupLineNode( child.toElement(), frame );
			}
			else if ( child.toElement().tagName() == "Markup-circle" )
			{
				parseMarkupCircleNode( child.toElement(), frame );
			}
			else if ( child.toElement().tagName() == "Markup-rect" )
			{
				parseMarkupRectNode( child.toElement(), frame );
			}
			else if ( child.toElement().tagName() == "Markup-ellipse" )
			{
				parseMarkupEllipseNode( child.toElement(), frame );
			}
			else if ( !child.isComment() )
			{
				std::cerr << "Warning: bad element: " << qPrintable(child.toElement().tagName())
					  << ", Ignored"
					  << std::endl;
			}
		}
	}


	void XmlTemplateParser::parseLayoutNode( const QDomElement &node, Frame *frame )
	{
		int    nX = XmlUtil::getAttr( node, "nx", 1 );
		int    nY = XmlUtil::getAttr( node, "ny", 1 );

		double x0 = XmlUtil::getAttrLength( node, "x0", 0 );
		double y0 = XmlUtil::getAttrLength( node, "y0", 0 );

		double dX = XmlUtil::getAttrLength( node, "dx", 0 );
		double dY = XmlUtil::getAttrLength( node, "dy", 0 );

		frame->addLayout( new Layout( nX, nY, x0, y0, dX, dY ) );
	}


	void XmlTemplateParser::parseMarkupMarginNode( const QDomElement &node, Frame *frame )
	{
		double size = XmlUtil::getAttrLength( node, "size", 0 );

		frame->addMarkup( new MarkupMargin( size ) );
	}


	void XmlTemplateParser::parseMarkupLineNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getAttrLength( node, "x1", 0 );
		double y1 = XmlUtil::getAttrLength( node, "y1", 0 );
		double x2 = XmlUtil::getAttrLength( node, "x2", 0 );
		double y2 = XmlUtil::getAttrLength( node, "y2", 0 );

		frame->addMarkup( new MarkupLine( x1, y1, x2, y2 ) );
	}


	void XmlTemplateParser::parseMarkupCircleNode( const QDomElement &node, Frame *frame )
	{
		double x0 = XmlUtil::getAttrLength( node, "x0", 0 );
		double y0 = XmlUtil::getAttrLength( node, "y0", 0 );
		double r  = XmlUtil::getAttrLength( node, "radius", 0 );

		frame->addMarkup( new MarkupCircle( x0, y0, r ) );
	}


	void XmlTemplateParser::parseMarkupRectNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getAttrLength( node, "x1", 0 );
		double y1 = XmlUtil::getAttrLength( node, "y1", 0 );
		double w  = XmlUtil::getAttrLength( node, "w", 0 );
		double h  = XmlUtil::getAttrLength( node, "h", 0 );
		double r  = XmlUtil::getAttrLength( node, "r", 0 );

		frame->addMarkup( new MarkupRect( x1, y1, w, h, r ) );
	}


	void XmlTemplateParser::parseMarkupEllipseNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getAttrLength( node, "x1", 0 );
		double y1 = XmlUtil::getAttrLength( node, "y1", 0 );
		double w  = XmlUtil::getAttrLength( node, "w", 0 );
		double h  = XmlUtil::getAttrLength( node, "h", 0 );

		frame->addMarkup( new MarkupEllipse( x1, y1, w, h ) );
	}

}

