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
#include <QtDebug>

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
			qWarning() << "Error: Cannot read file " << fileName
				   << ": " << file.errorString();
			return false;
		}


		QDomDocument doc;
		QString      errorString;
		int          errorLine;
		int          errorColumn;

		if ( !doc.setContent( &file, false, &errorString, &errorLine, &errorColumn ) )
		{
			qWarning() << "Error: Parse error at line " << errorLine
				   << "column " << errorColumn
				   << ": " << errorString;
			return false;
		}

		QDomElement root = doc.documentElement();
		if ( root.tagName() != "Glabels-templates" )
		{
			qWarning() << "Error: Not a Glabels-templates file";
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
					qWarning() << "Warning: could not create template, Ignored.";
				}
			}
			else if ( !child.isComment() )
			{
				qWarning() << "Warning: bad element: "
					   << child.toElement().tagName()
					   << ", Ignored.";
			}
		}
	}


	Template *XmlTemplateParser::parseTemplateNode( const QDomElement &node )
	{
		QString brand = XmlUtil::getStringAttr( node, "brand", "" );
		QString part  = XmlUtil::getStringAttr( node, "part", "" );

		if ( (brand == "") || (part == "") )
		{
			// Try the deprecated "name" attribute.
			QString name = XmlUtil::getStringAttr( node, "name", "" );
			if ( name != "" )
			{
				QStringList fields = name.split( " ", QString::SkipEmptyParts );
				brand = fields[0];
				part  = fields[1];
			}
			else
			{
				qWarning() << "Error: missing name or brand/part attributes.";
				return NULL;
			}
		}


		Template *tmplate = NULL;

		QString equivPart = XmlUtil::getStringAttr( node, "equiv", "" );
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
					qWarning() << "Warning: bad element: "
						   << child.toElement().tagName()
						   << ", Ignored.";
				}
			}
		}
		else
		{
			QString description = XmlUtil::getI18nAttr( node, "description", "" );
			QString paperId     = XmlUtil::getStringAttr( node, "size", "" );

			if ( !Db::isPaperIdOther( paperId ) )
			{
				const Paper *paper = Db::lookupPaperFromId( paperId );
				if ( paper == NULL )
				{
					qWarning() << "Error: unknown paper ID: " << paperId;
					return NULL;
				}

				tmplate = new Template( brand, part, description,
							paper->id(), paper->width(), paper->height() );
			}
			else
			{
				double width  = XmlUtil::getLengthAttr( node, "width", 0 );
				double height = XmlUtil::getLengthAttr( node, "height", 0 );

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
					qWarning() << "Warning: bad element: "
						   << child.toElement().tagName()
						   << ", Ignored.";
				}
			}
		}

		return tmplate;
	}


	void XmlTemplateParser::parseMetaNode( const QDomElement &node, Template *tmplate )
	{
		QString productUrl = XmlUtil::getStringAttr( node, "product_url", "" );
		if ( productUrl != "" )
		{
			tmplate->setProductUrl( productUrl );
		}
		
		QString categoryId = XmlUtil::getStringAttr( node, "category", "" );
		if ( categoryId != "" )
		{
			tmplate->addCategory( categoryId );
		}
	}


	void XmlTemplateParser::parseLabelRectangleNode( const QDomElement &node, Template *tmplate )
	{
		QString id = XmlUtil::getStringAttr( node, "id", "0" );

		double w   = XmlUtil::getLengthAttr( node, "width", 0 );
		double h   = XmlUtil::getLengthAttr( node, "height", 0 );
		double r   = XmlUtil::getLengthAttr( node, "round", 0 );

		double xWaste, yWaste;

		double waste = XmlUtil::getLengthAttr( node, "waste", -1 );
		if ( waste >= 0 )
		{
			xWaste = waste;
			yWaste = waste;
		}
		else
		{
			xWaste = XmlUtil::getLengthAttr( node, "x_waste", 0 );
			yWaste = XmlUtil::getLengthAttr( node, "y_waste", 0 );
		}

		Frame *frame = new FrameRect( w, h, r, xWaste, yWaste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelEllipseNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getStringAttr( node, "id", "0" );

		double  w     = XmlUtil::getLengthAttr( node, "width", 0 );
		double  h     = XmlUtil::getLengthAttr( node, "height", 0 );
		double  waste = XmlUtil::getLengthAttr( node, "waste", -1 );

		Frame *frame = new FrameEllipse( w, h, waste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelRoundNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getStringAttr( node, "id", "0" );

		double  r     = XmlUtil::getLengthAttr( node, "radius", 0 );
		double  waste = XmlUtil::getLengthAttr( node, "waste", -1 );

		Frame *frame = new FrameRound( r, waste, id );

		parseLabelNodeCommon( node, frame );

		tmplate->addFrame( frame );
	}


	void XmlTemplateParser::parseLabelCdNode( const QDomElement &node, Template *tmplate )
	{
		QString id    = XmlUtil::getStringAttr( node, "id", "0" );

		double  r1    = XmlUtil::getLengthAttr( node, "radius", 0 );
		double  r2    = XmlUtil::getLengthAttr( node, "hole", 0 );
		double  w     = XmlUtil::getLengthAttr( node, "width", 0 );
		double  h     = XmlUtil::getLengthAttr( node, "height", 0 );
		double  waste = XmlUtil::getLengthAttr( node, "waste", -1 );

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
				qWarning() << "Warning: bad element: "
					   << child.toElement().tagName()
					   << ", Ignored.";
			}
		}
	}


	void XmlTemplateParser::parseLayoutNode( const QDomElement &node, Frame *frame )
	{
		int    nX = XmlUtil::getIntAttr( node, "nx", 1 );
		int    nY = XmlUtil::getIntAttr( node, "ny", 1 );

		double x0 = XmlUtil::getLengthAttr( node, "x0", 0 );
		double y0 = XmlUtil::getLengthAttr( node, "y0", 0 );

		double dX = XmlUtil::getLengthAttr( node, "dx", 0 );
		double dY = XmlUtil::getLengthAttr( node, "dy", 0 );

		frame->addLayout( new Layout( nX, nY, x0, y0, dX, dY ) );
	}


	void XmlTemplateParser::parseMarkupMarginNode( const QDomElement &node, Frame *frame )
	{
		double size = XmlUtil::getLengthAttr( node, "size", 0 );

		frame->addMarkup( new MarkupMargin( frame, size ) );
	}


	void XmlTemplateParser::parseMarkupLineNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getLengthAttr( node, "x1", 0 );
		double y1 = XmlUtil::getLengthAttr( node, "y1", 0 );
		double x2 = XmlUtil::getLengthAttr( node, "x2", 0 );
		double y2 = XmlUtil::getLengthAttr( node, "y2", 0 );

		frame->addMarkup( new MarkupLine( x1, y1, x2, y2 ) );
	}


	void XmlTemplateParser::parseMarkupCircleNode( const QDomElement &node, Frame *frame )
	{
		double x0 = XmlUtil::getLengthAttr( node, "x0", 0 );
		double y0 = XmlUtil::getLengthAttr( node, "y0", 0 );
		double r  = XmlUtil::getLengthAttr( node, "radius", 0 );

		frame->addMarkup( new MarkupCircle( x0, y0, r ) );
	}


	void XmlTemplateParser::parseMarkupRectNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getLengthAttr( node, "x1", 0 );
		double y1 = XmlUtil::getLengthAttr( node, "y1", 0 );
		double w  = XmlUtil::getLengthAttr( node, "w", 0 );
		double h  = XmlUtil::getLengthAttr( node, "h", 0 );
		double r  = XmlUtil::getLengthAttr( node, "r", 0 );

		frame->addMarkup( new MarkupRect( x1, y1, w, h, r ) );
	}


	void XmlTemplateParser::parseMarkupEllipseNode( const QDomElement &node, Frame *frame )
	{
		double x1 = XmlUtil::getLengthAttr( node, "x1", 0 );
		double y1 = XmlUtil::getLengthAttr( node, "y1", 0 );
		double w  = XmlUtil::getLengthAttr( node, "w", 0 );
		double h  = XmlUtil::getLengthAttr( node, "h", 0 );

		frame->addMarkup( new MarkupEllipse( x1, y1, w, h ) );
	}

}

