/*  XmlLabel.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#include "XmlLabel.h"

#include "LabelModel.h"
#include "LabelModelObject.h"
#include "LabelModelBoxObject.h"
//#include "LabelObjectEllipse.h"
//#include "LabelObjectLine.h"
//#include "LabelObjectImage.h"
//#include "LabelObjectBarcode.h"
#include "libglabels/XmlTemplateParser.h"
#include "libglabels/XmlUtil.h"

#include <QFile>
#include <QtDebug>


glabels::LabelModel* glabels::XmlLabel::readFile( const QString& fileName )
{
	QFile file( fileName );

	if ( !file.open( QFile::ReadOnly | QFile::Text) )
	{
		qWarning() << "Error: Cannot read file " << qPrintable(fileName)
			   << ": " << file.errorString();
		return 0;
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
		return 0;
	}

	QDomElement root = doc.documentElement();
	if ( root.tagName() != "Glabels-document" )
	{
		qWarning() << "Error: Not a Glabels-document file";
		return 0;
	}

	return parseRootNode( root );
}


glabels::LabelModel* glabels::XmlLabel::readBuffer( const QString& buffer )
{
	QDomDocument doc;
	QString      errorString;
	int          errorLine;
	int          errorColumn;

	if ( !doc.setContent( buffer, false, &errorString, &errorLine, &errorColumn ) )
	{
		qWarning() << "Error: Parse error at line " << errorLine
			   << "column " << errorColumn
			   << ": " << errorString;
		return 0;
	}

	QDomElement root = doc.documentElement();
	if ( root.tagName() != "Glabels-document" )
	{
		qWarning() << "Error: Not a Glabels-document file";
		return 0;
	}

	return parseRootNode( root );
}


void glabels::XmlLabel::writeFile( const LabelModel* label, const QString& fileName )
{
	QDomDocument doc;

	createDoc( doc, label );
	QString buffer = doc.toString( 4 );

	QFile file( fileName );

	if ( !file.open( QFile::WriteOnly | QFile::Text) )
	{
		qWarning() << "Error: Cannot read file " << fileName
			   << ": " << file.errorString();
	}

	file.write( buffer.toStdString().c_str(), buffer.size() );
}


void glabels::XmlLabel::writeBuffer( const LabelModel* label, QString& buffer )
{
	QDomDocument doc;

	createDoc( doc, label );
	buffer = doc.toString( 4 );
}


glabels::LabelModel* glabels::XmlLabel::parseRootNode( const QDomElement &node )
{
	using namespace libglabels;

	LabelModel* label = new LabelModel();

	/* Pass 1, extract data nodes to pre-load cache. */
	for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
	{
		if ( child.toElement().tagName() == "Data" )
		{
			parseDataNode( child.toElement(), label );
		}
	}

	/* Pass 2, now extract everything else. */
	for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
	{
		QString tagName = child.toElement().tagName();
		
		if ( tagName == "Template" )
		{
			Template* tmplate = XmlTemplateParser().parseTemplateNode( child.toElement() );
			if ( tmplate == 0 )
			{
				qWarning() << "Unable to parse template";
				return 0;
			}
			label->setTmplate( tmplate );
		}
		else if ( tagName == "Objects" )
		{
			parseObjectsNode( child.toElement(), label );
		}
		else if ( tagName == "Merge" )
		{
			parseMergeNode( child.toElement(), label );
		}
		else if ( tagName == "Data" )
		{
			/* Handled in pass 1. */
		}
		else if ( !child.isComment() )
		{
			qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
		}
	}

	return label;
}


void glabels::XmlLabel::parseObjectsNode( const QDomElement &node, LabelModel* label )
{
	for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
	{
		QString tagName = child.toElement().tagName();
		
		if ( tagName == "Object-box" )
		{
			parseObjectBoxNode( child.toElement(), label );
		}
		else if ( tagName == "Object-ellipse" )
		{
			parseObjectEllipseNode( child.toElement(), label );
		}
		else if ( tagName == "Object-line" )
		{
			parseObjectLineNode( child.toElement(), label );
		}
		else if ( tagName == "Object-image" )
		{
			parseObjectImageNode( child.toElement(), label );
		}
		else if ( tagName == "Object-barcode" )
		{
			parseObjectBarcodeNode( child.toElement(), label );
		}
		else if ( tagName == "Object-text" )
		{
			parseObjectTextNode( child.toElement(), label );
		}
		else if ( !child.isComment() )
		{
			qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
		}
	}
}


void glabels::XmlLabel::parseObjectBoxNode( const QDomElement &node, LabelModel* label )
{
	using namespace libglabels;

	LabelModelBoxObject* object = new LabelModelBoxObject();
	label->addObject( object );


	/* position attrs */
	object->setX0( XmlUtil::getLengthAttr( node, "x", 0.0 ) );
	object->setY0( XmlUtil::getLengthAttr( node, "y", 0.0 ) );

	/* size attrs */
	object->setW( XmlUtil::getLengthAttr( node, "w", 0 ) );
	object->setH( XmlUtil::getLengthAttr( node, "h", 0 ) );

	/* line attrs */
	object->setLineWidth( XmlUtil::getLengthAttr( node, "line_width", 1.0 ) );
        {
		QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "line_color", 0 );

		object->setLineColorNode( ColorNode( field_flag, color, key ) );
	}

	/* fill attrs */
	{
		QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "fill_color", 0 );

		object->setFillColorNode( ColorNode( field_flag, color, key ) );
	}
        
	/* affine attrs */
	parseAffineAttrs( node, object );

	/* shadow attrs */
	parseShadowAttrs( node, object );
}


void glabels::XmlLabel::parseObjectEllipseNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseObjectLineNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseObjectImageNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseObjectBarcodeNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseObjectTextNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseTopLevelSpanNode( const QDomElement &node, LabelModelTextObject* object )
{
}


void glabels::XmlLabel::parseAffineAttrs( const QDomElement &node, LabelModelObject* object )
{
	using namespace libglabels;

	double a[6];

	a[0] = XmlUtil::getDoubleAttr( node, "a0", 0.0 );
	a[1] = XmlUtil::getDoubleAttr( node, "a1", 0.0 );
	a[2] = XmlUtil::getDoubleAttr( node, "a2", 0.0 );
	a[3] = XmlUtil::getDoubleAttr( node, "a3", 0.0 );
	a[4] = XmlUtil::getDoubleAttr( node, "a4", 0.0 );
	a[5] = XmlUtil::getDoubleAttr( node, "a5", 0.0 );

	object->setMatrix( QTransform( a[0], a[1], a[2], a[3], a[4], a[5] ) );
}


void glabels::XmlLabel::parseShadowAttrs( const QDomElement &node, LabelModelObject* object )
{
	using namespace libglabels;

	object->setShadow( XmlUtil::getBoolAttr( node, "shadow", false ) );

	if ( object->shadow() )
	{
		object->setShadowX( XmlUtil::getLengthAttr( node, "shadow_x", 0.0 ) );
		object->setShadowY( XmlUtil::getLengthAttr( node, "shadow_y", 0.0 ) );

		QString  key        = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "shadow_color", 0 );

		object->setShadowColorNode( ColorNode( field_flag, color, key ) );

		object->setShadowOpacity( XmlUtil::getLengthAttr( node, "shadow_y", 1.0 ) );
	}
}


void glabels::XmlLabel::parseMergeNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseDataNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parsePixdataNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::parseFileNode( const QDomElement &node, LabelModel* label )
{
}


void glabels::XmlLabel::createDoc( QDomDocument& doc, const LabelModel* label ) {}
void glabels::XmlLabel::createRootNode( const LabelModel* label ) {}
void glabels::XmlLabel::createObjectsNode( QDomElement &parent, const LabelModel* label ) {}
void glabels::XmlLabel::createObjectBoxNode( QDomElement &parent, const LabelModelBoxObject* object ) {}
void glabels::XmlLabel::createObjectEllipseNode( QDomElement &parent, const LabelModelEllipseObject* object ) {}
void glabels::XmlLabel::createObjectLineNode( QDomElement &parent, const LabelModelLineObject* object ) {}
void glabels::XmlLabel::createObjectImageNode( QDomElement &parent, const LabelModelImageObject* object ) {}
void glabels::XmlLabel::createObjectBarcodeNode( QDomElement &parent, const LabelModelBarcodeObject* object ) {}
void glabels::XmlLabel::createObjectTextNode( QDomElement &parent, const LabelModelTextObject* object ) {}
void glabels::XmlLabel::createObjectTopLevelSpanNode( QDomElement &parent, const LabelModelTextObject* object ) {}
void glabels::XmlLabel::createffineAttrs( QDomElement &node, const LabelModelObject* object ) {}
void glabels::XmlLabel::createShadowAttrs( QDomElement &node, const LabelModelObject* object ) {}
void glabels::XmlLabel::createMergeNode( QDomElement &node, LabelModel* label ) {}
void glabels::XmlLabel::createDataNode( QDomElement &node, LabelModel* label ) {}
void glabels::XmlLabel::createPixdataNode( QDomElement &node, LabelModel* label, const QString& name ) {}
void glabels::XmlLabel::createSvgFileNode( QDomElement &node, LabelModel* label, const QString& name ) {}

