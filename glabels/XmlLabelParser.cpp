/*  XmlLabelParser.cpp
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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

#include "XmlLabelParser.h"

#include "EnumUtil.h"
#include "LabelModel.h"
#include "LabelModelObject.h"
//#include "LabelModelBarcodeObject.h"
#include "LabelModelBoxObject.h"
#include "LabelModelEllipseObject.h"
#include "LabelModelImageObject.h"
#include "LabelModelLineObject.h"
#include "LabelModelTextObject.h"
#include "XmlTemplateParser.h"
#include "XmlUtil.h"
#include "DataCache.h"

#include "Merge/Factory.h"

#include <QByteArray>
#include <QFile>
#include <QTextCursor>
#include <QTextDocument>
#include <QtDebug>

#include <zlib.h>


namespace glabels
{

	LabelModel*
	XmlLabelParser::readFile( const QString& fileName )
	{
		QFile file( fileName );

		if ( !file.open( QFile::ReadOnly ) )
		{
			qWarning() << "Error: Cannot read file " << qPrintable(fileName)
			           << ": " << file.errorString();
			return nullptr;
		}

		QDomDocument doc;
		bool         success;
		QString      errorString;
		int          errorLine;
		int          errorColumn;

		QByteArray rawData = file.readAll();
		if ( ((rawData[0]&0xFF) == 0x1F) && ((rawData[1]&0xFF) == 0x8b) ) // gzip magic number 0x1F, 0x8B
		{
			// gzip compressed format
			QByteArray unzippedData;
			gunzip( rawData, unzippedData );
			success = doc.setContent( unzippedData, false, &errorString, &errorLine, &errorColumn );
		}
		else
		{
			// plain text
			success = doc.setContent( rawData, false, &errorString, &errorLine, &errorColumn );
		}

		if ( !success )
		{
			qWarning() << "Error: Parse error at line " << errorLine
			           << "column " << errorColumn
			           << ": " << errorString;
			return nullptr;
		}
	

		QDomElement root = doc.documentElement();
		if ( root.tagName() != "Glabels-document" )
		{
			qWarning() << "Error: Not a Glabels-document file";
			return nullptr;
		}

		return parseRootNode( root );
	}


	LabelModel*
	XmlLabelParser::readBuffer( const QByteArray& buffer )
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
			return nullptr;
		}

		QDomElement root = doc.documentElement();
		if ( root.tagName() != "Glabels-document" )
		{
			qWarning() << "Error: Not a Glabels-document file";
			return nullptr;
		}

		return parseRootNode( root );
	}


	QList<LabelModelObject*>
	XmlLabelParser::deserializeObjects( const QByteArray& buffer )
	{
		QList<LabelModelObject*> list;
	
		QDomDocument doc;
		QString      errorString;
		int          errorLine;
		int          errorColumn;

		if ( !doc.setContent( buffer, false, &errorString, &errorLine, &errorColumn ) )
		{
			qWarning() << "Error: Parse error at line " << errorLine
			           << "column " << errorColumn
			           << ": " << errorString;
			return list;
		}

		QDomElement root = doc.documentElement();
		if ( root.tagName() != "Glabels-objects" )
		{
			qWarning() << "Error: Not a Glabels-objects stream";
			return list;
		}

		/* Pass 1, extract data nodes to pre-load cache. */
		DataCache data;
		for ( QDomNode child = root.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Data" )
			{
				parseDataNode( child.toElement(), data );
			}
		}

		/* Pass 2, now extract objects. */
		for ( QDomNode child = root.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Objects" )
			{
				list = parseObjectsNode( child.toElement(), data );
			}
		}
		return list;
	}


	void
	XmlLabelParser::gunzip( const QByteArray& data, QByteArray& result )
	{
		result.clear();

		if (data.size() <= 4) {
			qWarning("XmlLabelParser::gunzip: Input data is truncated");
			return;
		}

		// setup stream for inflate()
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = data.size();
		strm.next_in = (Bytef*)(data.data());

		int ret = inflateInit2(&strm, MAX_WBITS + 16); // gzip decoding
		if (ret != Z_OK)
		{
			return;
		}

		static const int CHUNK_SIZE = 1024;
		char out[CHUNK_SIZE];

		// run inflate(), one chunk at a time
		do {
			strm.avail_out = CHUNK_SIZE;
			strm.next_out = (Bytef*)(out);

			ret = inflate(&strm, Z_NO_FLUSH);
			Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

			if ( (ret == Z_NEED_DICT) || (ret == Z_DATA_ERROR) || (ret == Z_MEM_ERROR) )
			{
				// clean up
				inflateEnd(&strm);
				return;
			}

			result.append(out, CHUNK_SIZE - strm.avail_out);
		} while (strm.avail_out == 0);

		// clean up
		inflateEnd(&strm);
	}


	LabelModel*
	XmlLabelParser::parseRootNode( const QDomElement &node )
	{
		QString version = XmlUtil::getStringAttr( node, "version", "" );
		if ( version != "4.0" )
		{
			qWarning() << "TODO: compatability mode.";
		}

		LabelModel* label = new LabelModel();

		/* Pass 1, extract data nodes to pre-load cache. */
		DataCache data;
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			if ( child.toElement().tagName() == "Data" )
			{
				parseDataNode( child.toElement(), data );
			}
		}

		/* Pass 2, now extract everything else. */
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			QString tagName = child.toElement().tagName();
		
			if ( tagName == "Template" )
			{
				Template* tmplate = XmlTemplateParser().parseTemplateNode( child.toElement() );
				if ( tmplate == nullptr )
				{
					qWarning() << "Unable to parse template";
					delete label;
					return nullptr;
				}
				label->setTmplate( tmplate );
			}
			else if ( tagName == "Objects" )
			{
				QList<LabelModelObject*> list = parseObjectsNode( child.toElement(), data );
				foreach ( LabelModelObject* object, list )
				{
					label->addObject( object );
				}
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

		label->clearModified();
		return label;
	}


	QList<LabelModelObject*>
	XmlLabelParser::parseObjectsNode( const QDomElement &node, const DataCache& data )
	{
		QList<LabelModelObject*> list;

		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			QString tagName = child.toElement().tagName();
		
			if ( tagName == "Object-box" )
			{
				list.append( parseObjectBoxNode( child.toElement() ) );
			}
			else if ( tagName == "Object-ellipse" )
			{
				list.append( parseObjectEllipseNode( child.toElement() ) );
			}
			else if ( tagName == "Object-line" )
			{
				list.append( parseObjectLineNode( child.toElement() ) );
			}
			else if ( tagName == "Object-text" )
			{
				list.append( parseObjectTextNode( child.toElement() ) );
			}
			else if ( tagName == "Object-image" )
			{
				list.append( parseObjectImageNode( child.toElement(), data ) );
			}
#if 0
			else if ( tagName == "Object-barcode" )
			{
				list.append( parseObjectBarcodeNode( child.toElement() ) );
			}
#endif
			else if ( !child.isComment() )
			{
				qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
			}
		}

		return list;
	}


	LabelModelBoxObject*
	XmlLabelParser::parseObjectBoxNode( const QDomElement &node )
	{
		LabelModelBoxObject* object = new LabelModelBoxObject();


		/* position attrs */
		parsePositionAttrs( node, object );

		/* size attrs */
		parseSizeAttrs( node, object );

		/* line attrs */
		parseLineAttrs( node, object );

		/* fill attrs */
		parseFillAttrs( node, object );
        
		/* affine attrs */
		parseAffineAttrs( node, object );

		/* shadow attrs */
		parseShadowAttrs( node, object );

		return object;
	}


	LabelModelEllipseObject*
	XmlLabelParser::parseObjectEllipseNode( const QDomElement &node )
	{
		LabelModelEllipseObject* object = new LabelModelEllipseObject();


		/* position attrs */
		parsePositionAttrs( node, object );

		/* size attrs */
		parseSizeAttrs( node, object );

		/* line attrs */
		parseLineAttrs( node, object );

		/* fill attrs */
		parseFillAttrs( node, object );
        
		/* affine attrs */
		parseAffineAttrs( node, object );

		/* shadow attrs */
		parseShadowAttrs( node, object );

		return object;
	}


	LabelModelLineObject*
	XmlLabelParser::parseObjectLineNode( const QDomElement &node )
	{
		LabelModelLineObject* object = new LabelModelLineObject();


		/* position attrs */
		parsePositionAttrs( node, object );

		/* size attrs of line */
		object->setW( XmlUtil::getLengthAttr( node, "dx", 0 ) );
		object->setH( XmlUtil::getLengthAttr( node, "dy", 0 ) );

		/* line attrs */
		parseLineAttrs( node, object );

		/* affine attrs */
		parseAffineAttrs( node, object );

		/* shadow attrs */
		parseShadowAttrs( node, object );

		return object;
	}


	LabelModelImageObject*
	XmlLabelParser::parseObjectImageNode( const QDomElement &node, const DataCache& data )
	{
		LabelModelImageObject* object = new LabelModelImageObject();


		/* position attrs */
		parsePositionAttrs( node, object );

		/* size attrs */
		parseSizeAttrs( node, object );

		/* file attrs */
		QString key        = XmlUtil::getStringAttr( node, "src_field", "" );
		bool    field_flag = !key.isEmpty();
		QString filename   = XmlUtil::getStringAttr( node, "src", "" );

		if ( field_flag )
		{
			object->setFilenameNode( TextNode( true, key ) );
		}
		else
		{
			if ( data.hasImage( filename ) )
			{
				object->setImage( filename, data.getImage( filename ) );
			}
			else if ( data.hasSvg( filename ) )
			{
				object->setSvg( filename, data.getSvg( filename ) );
			}
			else
			{
				qWarning() << "Embedded file" << filename << "missing. Trying actual file.";
				object->setFilenameNode( TextNode( false, filename ) );
			}
		}
        
		/* affine attrs */
		parseAffineAttrs( node, object );

		/* shadow attrs */
		parseShadowAttrs( node, object );

		return object;
	}


	LabelModelBarcodeObject*
	XmlLabelParser::parseObjectBarcodeNode( const QDomElement &node )
	{
		return nullptr;
	}


	LabelModelTextObject*
	XmlLabelParser::parseObjectTextNode( const QDomElement &node )
	{
		LabelModelTextObject* object = new LabelModelTextObject();


		/* position attrs */
		parsePositionAttrs( node, object );

		/* size attrs */
		parseSizeAttrs( node, object );

		/* color attr */
		QString  key        = XmlUtil::getStringAttr( node, "color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "color", 0 );

		object->setTextColorNode( ColorNode( field_flag, color, key ) );

		/* font attrs */
		object->setFontFamily( XmlUtil::getStringAttr( node, "font_family", "Sans" ) );
		object->setFontSize( XmlUtil::getDoubleAttr( node, "font_size", 10 ) );
		object->setFontWeight( EnumUtil::stringToWeight( XmlUtil::getStringAttr( node, "font_weight", "normal" ) ) );
		object->setFontItalicFlag( XmlUtil::getBoolAttr( node, "font_italic", false ) );
		object->setFontUnderlineFlag( XmlUtil::getBoolAttr( node, "font_underline", false ) );

		/* text attrs */
		object->setTextLineSpacing( XmlUtil::getDoubleAttr( node, "line_spacing", 1 ) );
		object->setTextHAlign( EnumUtil::stringToHAlign( XmlUtil::getStringAttr( node, "align", "left" ) ) );
		object->setTextVAlign( EnumUtil::stringToVAlign( XmlUtil::getStringAttr( node, "valign", "top" ) ) );

		/* affine attrs */
		parseAffineAttrs( node, object );

		/* shadow attrs */
		parseShadowAttrs( node, object );

		/* deserialize contents. */
		QTextDocument document;
		QTextCursor cursor( &document );
		bool firstBlock = true;
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			QString tagName = child.toElement().tagName();
		
			if ( tagName == "p" )
			{
				if ( !firstBlock )
				{
					cursor.insertBlock();
				}
				firstBlock = false;
				cursor.insertText( parsePNode( child.toElement() ) );
			}
			else if ( !child.isComment() )
			{
				qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
			}
		}
		object->setText( document.toPlainText() );

		return object;
	}


	QString
	XmlLabelParser::parsePNode( const QDomElement &node )
	{
		return node.text();
	}


	void
	XmlLabelParser::parsePositionAttrs( const QDomElement &node, LabelModelObject* object )
	{
		object->setX0( XmlUtil::getLengthAttr( node, "x", 0.0 ) );
		object->setY0( XmlUtil::getLengthAttr( node, "y", 0.0 ) );
	}

	
	void
	XmlLabelParser::parseSizeAttrs( const QDomElement &node, LabelModelObject* object )
	{
		object->setW( XmlUtil::getLengthAttr( node, "w", 0 ) );
		object->setH( XmlUtil::getLengthAttr( node, "h", 0 ) );
	}

	
	void
	XmlLabelParser::parseLineAttrs( const QDomElement &node, LabelModelObject* object )
	{
		object->setLineWidth( XmlUtil::getLengthAttr( node, "line_width", 1.0 ) );

		QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "line_color", 0 );

		object->setLineColorNode( ColorNode( field_flag, color, key ) );
	}

	
	void
	XmlLabelParser::parseFillAttrs( const QDomElement &node, LabelModelObject* object )
	{
		QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
		bool     field_flag = !key.isEmpty();
		uint32_t color      = XmlUtil::getUIntAttr( node, "fill_color", 0 );

		object->setFillColorNode( ColorNode( field_flag, color, key ) );
	}


	void
	XmlLabelParser::parseAffineAttrs( const QDomElement &node, LabelModelObject* object )
	{
		double a[6];

		a[0] = XmlUtil::getDoubleAttr( node, "a0", 1.0 );
		a[1] = XmlUtil::getDoubleAttr( node, "a1", 0.0 );
		a[2] = XmlUtil::getDoubleAttr( node, "a2", 0.0 );
		a[3] = XmlUtil::getDoubleAttr( node, "a3", 1.0 );
		a[4] = XmlUtil::getDoubleAttr( node, "a4", 0.0 );
		a[5] = XmlUtil::getDoubleAttr( node, "a5", 0.0 );

		object->setMatrix( QMatrix( a[0], a[1], a[2], a[3], a[4], a[5] ) );
	}


	void
	XmlLabelParser::parseShadowAttrs( const QDomElement &node, LabelModelObject* object )
	{
		object->setShadow( XmlUtil::getBoolAttr( node, "shadow", false ) );

		if ( object->shadow() )
		{
			object->setShadowX( XmlUtil::getLengthAttr( node, "shadow_x", 0.0 ) );
			object->setShadowY( XmlUtil::getLengthAttr( node, "shadow_y", 0.0 ) );

			QString  key        = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			bool     field_flag = !key.isEmpty();
			uint32_t color      = XmlUtil::getUIntAttr( node, "shadow_color", 0 );

			object->setShadowColorNode( ColorNode( field_flag, color, key ) );

			object->setShadowOpacity( XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 ) );
		}
	}


	void
	XmlLabelParser::parseMergeNode( const QDomElement &node, LabelModel* label )
	{
		QString type = XmlUtil::getStringAttr( node, "type", "None" );
		QString src  = XmlUtil::getStringAttr( node, "src", "" );

		merge::Merge* merge = merge::Factory::createMerge( type );
		merge->setSource( src );

		label->setMerge( merge );
	}


	void
	XmlLabelParser::parseDataNode( const QDomElement &node, DataCache& data )
	{
		for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
		{
			QString tagName = child.toElement().tagName();
		
			if ( tagName == "File" )
			{
				parseFileNode( child.toElement(), data );
			}
			else if ( !child.isComment() )
			{
				qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
			}
		}
	}


	void
	XmlLabelParser::parsePixdataNode( const QDomElement& node, DataCache& data )
	{
		// TODO, compatability with glabels-3
	}


	void
	XmlLabelParser::parseFileNode( const QDomElement& node, DataCache& data )
	{
		QString name     = XmlUtil::getStringAttr( node, "name", "" );
		QString mimetype = XmlUtil::getStringAttr( node, "mimetype", "image/png" );
		QString encoding = XmlUtil::getStringAttr( node, "encoding", "base64" );

		if ( mimetype == "image/png" )
		{
			QByteArray ba64 = node.text().toUtf8();
			QByteArray ba = QByteArray::fromBase64( ba64 );
			QImage image;
			image.loadFromData( ba, "PNG" );

			data.addImage( name, image );
		}
		else if ( mimetype == "image/svg+xml" )
		{
			data.addSvg( name, node.text().toUtf8() );
		}
	}

} // namespace glabels
