/*  XmlLabelCreator.cpp
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

#include "XmlLabelCreator.h"

#include "LabelModel.h"
#include "LabelModelObject.h"
#include "LabelModelBoxObject.h"
//#include "LabelObjectEllipse.h"
//#include "LabelObjectLine.h"
//#include "LabelObjectImage.h"
//#include "LabelObjectBarcode.h"
#include "libglabels/XmlTemplateCreator.h"
#include "libglabels/XmlUtil.h"

#include <QFile>
#include <QByteArray>
#include <QtDebug>


void
glabels::XmlLabelCreator::writeFile( const LabelModel* label, const QString& fileName )
{
	QDomDocument doc;

	createDoc( doc, label );
	QString buffer = doc.toString( 2 );

	QFile file( fileName );

	if ( !file.open( QFile::WriteOnly | QFile::Text) )
	{
		qWarning() << "Error: Cannot write file " << fileName
			   << ": " << file.errorString();
	}

	file.write( buffer.toStdString().c_str(), buffer.size() );
}


void
glabels::XmlLabelCreator::writeBuffer( const LabelModel* label, QString& buffer )
{
	QDomDocument doc;

	createDoc( doc, label );
	buffer = doc.toString( 2 );
}


void
glabels::XmlLabelCreator::createDoc( QDomDocument& doc, const LabelModel* label )
{
	QDomNode xmlNode( doc.createProcessingInstruction( "xml", "version=\"1.0\"" ) );
	doc.appendChild( xmlNode );

	QDomElement root = doc.createElement( "Glabels-document" );
	doc.appendChild( root );

	libglabels::XmlTemplateCreator().createTemplateNode( root, label->tmplate() );

	createObjectsNode( root, label );

	// TODO merge node

	createDataNode( root, label );
}


void
glabels::XmlLabelCreator::createObjectsNode( QDomElement &parent, const LabelModel* label )
{
	QDomDocument doc = parent.ownerDocument();
	QDomElement node = doc.createElement( "Objects" );
	parent.appendChild( node );

	libglabels::XmlUtil::setStringAttr( node, "id", "0" );
	libglabels::XmlUtil::setBoolAttr( node, "rotate", label->rotate() );

	foreach ( LabelModelObject* object, label->objectList() )
	{
		if ( LabelModelBoxObject* boxObject = dynamic_cast<LabelModelBoxObject*>(object) )
		{
			createObjectBoxNode( node, boxObject );
		}
		// TODO: other object types
		else
		{
			Q_ASSERT_X( false, "XmlLabelCreator::createObjectsNode", "Invalid object type." );
		}
	}
}


void
glabels::XmlLabelCreator::createObjectBoxNode( QDomElement &parent, const LabelModelBoxObject* object )
{
	QDomDocument doc = parent.ownerDocument();
	QDomElement node = doc.createElement( "Object-box" );
	parent.appendChild( node );

	/* position attrs */
	libglabels::XmlUtil::setLengthAttr( node, "x", object->x0() );
	libglabels::XmlUtil::setLengthAttr( node, "y", object->y0() );

	/* size attrs */
	libglabels::XmlUtil::setLengthAttr( node, "w", object->w() );
	libglabels::XmlUtil::setLengthAttr( node, "h", object->h() );

	/* line attrs */
	libglabels::XmlUtil::setLengthAttr( node, "line_width", object->lineWidth() );
	if ( object->lineColorNode().fieldFlag() )
	{
		libglabels::XmlUtil::setStringAttr( node, "line_color_field", object->lineColorNode().key() );
	}
	else
	{
		libglabels::XmlUtil::setUIntAttr( node, "line_color", object->lineColorNode().rgba() );
	}

	/* fill attrs */
	if ( object->fillColorNode().fieldFlag() )
	{
		libglabels::XmlUtil::setStringAttr( node, "fill_color_field", object->fillColorNode().key() );
	}
	else
	{
		libglabels::XmlUtil::setUIntAttr( node, "fill_color", object->fillColorNode().rgba() );
	}

	/* affine attrs */
	createAffineAttrs( node, object );

	/* shadow attrs */
	createShadowAttrs( node, object );
}


void
glabels::XmlLabelCreator::createObjectEllipseNode( QDomElement &parent, const LabelModelEllipseObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createObjectLineNode( QDomElement &parent, const LabelModelLineObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createObjectImageNode( QDomElement &parent, const LabelModelImageObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createObjectBarcodeNode( QDomElement &parent, const LabelModelBarcodeObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createObjectTextNode( QDomElement &parent, const LabelModelTextObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createObjectTopLevelSpanNode( QDomElement &parent, const LabelModelTextObject* object )
{
	// TODO
}


void
glabels::XmlLabelCreator::createAffineAttrs( QDomElement &node, const LabelModelObject* object )
{
	QTransform a = object->matrix();
	
	libglabels::XmlUtil::setDoubleAttr( node, "a0", a.m11() );
	libglabels::XmlUtil::setDoubleAttr( node, "a1", a.m12() );
	libglabels::XmlUtil::setDoubleAttr( node, "a2", a.m21() );
	libglabels::XmlUtil::setDoubleAttr( node, "a3", a.m22() );
	libglabels::XmlUtil::setDoubleAttr( node, "a4", a.dx() );
	libglabels::XmlUtil::setDoubleAttr( node, "a5", a.dy() );
}


void
glabels::XmlLabelCreator::createShadowAttrs( QDomElement &node, const LabelModelObject* object )
{
	if ( object->shadow() )
	{
		libglabels::XmlUtil::setBoolAttr( node, "shadow", object->shadow() );

		libglabels::XmlUtil::setLengthAttr( node, "shadow_x", object->shadowX() );
		libglabels::XmlUtil::setLengthAttr( node, "shadow_y", object->shadowY() );

		if ( object->fillColorNode().fieldFlag() )
		{
			libglabels::XmlUtil::setStringAttr( node, "shadow_color_field", object->shadowColorNode().key() );
		}
		else
		{
			libglabels::XmlUtil::setUIntAttr( node, "shadow_color", object->shadowColorNode().rgba() );
		}

		libglabels::XmlUtil::setDoubleAttr( node, "shadow_opacity", object->shadowOpacity() );
	}
}


void
glabels::XmlLabelCreator::createMergeNode( QDomElement &parent, const LabelModel* label )
{
	// TODO
}


void
glabels::XmlLabelCreator::createDataNode( QDomElement &parent, const LabelModel* label )
{
	// TODO
}


void
glabels::XmlLabelCreator::createPixdataNode( QDomElement &parent, const LabelModel* label, const QString& name )
{
	// TODO
}


void
glabels::XmlLabelCreator::createSvgFileNode( QDomElement &parent, const LabelModel* label, const QString& name )
{
	// TODO
}

