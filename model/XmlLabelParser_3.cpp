/*  XmlLabelParser_0_4.cpp
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
#include "XmlLabelParser_0_4.h"

#include "Model.h"
#include "ModelObject.h"
#include "ModelBarcodeObject.h"
#include "ModelBoxObject.h"
#include "ModelEllipseObject.h"
#include "ModelImageObject.h"
#include "ModelLineObject.h"
#include "ModelTextObject.h"
#include "XmlTemplateParser.h"
#include "XmlUtil.h"
#include "DataCache.h"

#include "barcode/Backends.h"
#include "merge/Factory.h"

#include <QByteArray>
#include <QFile>
#include <QTextCursor>
#include <QTextDocument>
#include <QtDebug>

#if HAVE_ZLIB
#include <zlib.h>
#endif

#define GDK_PIXBUF_MAGIC_NUMBER (0x47646b50)

typedef enum
{
  /* colorspace + alpha */
  GDK_PIXDATA_COLOR_TYPE_RGB    = 0x01,
  GDK_PIXDATA_COLOR_TYPE_RGBA   = 0x02,
  GDK_PIXDATA_COLOR_TYPE_MASK   = 0xff,
  /* width, support 8bits only currently */
  GDK_PIXDATA_SAMPLE_WIDTH_8    = 0x01 << 16,
  GDK_PIXDATA_SAMPLE_WIDTH_MASK = 0x0f << 16,
  /* encoding */
  GDK_PIXDATA_ENCODING_RAW      = 0x01 << 24,
  GDK_PIXDATA_ENCODING_RLE      = 0x02 << 24,
  GDK_PIXDATA_ENCODING_MASK     = 0x0f << 24
} GdkPixdataType;


namespace glabels
{
	namespace model
	{

		Model*
		XmlLabelParser_0_4::parseRootNode( const QDomElement &node )
		{
			if(node.namespaceURI() != XmlNameSpace)
			{
				qWarning() << "TODO: compatability mode.";
			}

			auto* label = new Model();

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
					label->setRotate( parseRotateAttr( child.toElement() ) );
					QList<ModelObject*> list = parseObjectsNode( child.toElement(), data );
					foreach ( ModelObject* object, list )
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


		QList<ModelObject*>
		XmlLabelParser_0_4::parseObjectsNode( const QDomElement &node, const DataCache& data )
		{
			QList<ModelObject*> list;

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
				else if ( tagName == "Object-barcode" )
				{
					list.append( parseObjectBarcodeNode( child.toElement() ) );
				}
				else if ( !child.isComment() )
				{
					qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
				}
			}

			return list;
		}


		ModelBoxObject*
		XmlLabelParser_0_4::parseObjectBoxNode( const QDomElement &node )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs */
			Distance w = XmlUtil::getLengthAttr( node, "w", 0 );
			Distance h = XmlUtil::getLengthAttr( node, "h", 0 );

			/* line attrs */
			Distance lineWidth = XmlUtil::getLengthAttr( node, "line_width", 1.0 );

			QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
			bool     field_flag = !key.isEmpty();
			uint32_t color      = XmlUtil::getUIntAttr( node, "line_color", 0 );
			ColorNode lineColorNode( field_flag, color, key );

			/* fill attrs */
			key        = XmlUtil::getStringAttr( node, "fill_color_field", "" );
			field_flag = !key.isEmpty();
			color      = XmlUtil::getUIntAttr( node, "fill_color", 0 );
			ColorNode fillColorNode( field_flag, color, key );
        
			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			/* shadow attrs */
			bool     shadowState   = XmlUtil::getBoolAttr( node, "shadow", false );
			Distance shadowX       = XmlUtil::getLengthAttr( node, "shadow_x", 0.0 );
			Distance shadowY       = XmlUtil::getLengthAttr( node, "shadow_y", 0.0 );
			double   shadowOpacity = XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 );

			key        = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			field_flag = !key.isEmpty();
			color      = XmlUtil::getUIntAttr( node, "shadow_color", 0 );
			ColorNode shadowColorNode( field_flag, color, key );

			return new ModelBoxObject( x0, y0, w, h,
			                           lineWidth, lineColorNode,
			                           fillColorNode,
						   affineTransformation,
			                           shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
		}


		ModelEllipseObject*
		XmlLabelParser_0_4::parseObjectEllipseNode( const QDomElement &node )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs */
			Distance w = XmlUtil::getLengthAttr( node, "w", 0 );
			Distance h = XmlUtil::getLengthAttr( node, "h", 0 );

			/* line attrs */
			Distance lineWidth = XmlUtil::getLengthAttr( node, "line_width", 1.0 );

			QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
			bool     field_flag = !key.isEmpty();
			uint32_t color      = XmlUtil::getUIntAttr( node, "line_color", 0 );
			ColorNode lineColorNode( field_flag, color, key );

			/* fill attrs */
			key        = XmlUtil::getStringAttr( node, "fill_color_field", "" );
			field_flag = !key.isEmpty();
			color      = XmlUtil::getUIntAttr( node, "fill_color", 0 );
			ColorNode fillColorNode( field_flag, color, key );
        
			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			/* shadow attrs */
			bool     shadowState   = XmlUtil::getBoolAttr( node, "shadow", false );
			Distance shadowX       = XmlUtil::getLengthAttr( node, "shadow_x", 0.0 );
			Distance shadowY       = XmlUtil::getLengthAttr( node, "shadow_y", 0.0 );
			double   shadowOpacity = XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 );

			key        = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			field_flag = !key.isEmpty();
			color      = XmlUtil::getUIntAttr( node, "shadow_color", 0 );
			ColorNode shadowColorNode( field_flag, color, key );

			return new ModelEllipseObject( x0, y0, w, h,
			                               lineWidth, lineColorNode,
			                               fillColorNode,
						       affineTransformation,
			                               shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
		}


		ModelLineObject*
		XmlLabelParser_0_4::parseObjectLineNode( const QDomElement &node )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs of line */
			Distance dx = XmlUtil::getLengthAttr( node, "dx", 0 );
			Distance dy = XmlUtil::getLengthAttr( node, "dy", 0 );

			/* line attrs */
			Distance lineWidth = XmlUtil::getLengthAttr( node, "line_width", 1.0 );

			QString  key        = XmlUtil::getStringAttr( node, "line_color_field", "" );
			bool     field_flag = !key.isEmpty();
			uint32_t color      = XmlUtil::getUIntAttr( node, "line_color", 0 );
			ColorNode lineColorNode( field_flag, color, key );

			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			/* shadow attrs */
			bool     shadowState   = XmlUtil::getBoolAttr( node, "shadow", false );
			Distance shadowX       = XmlUtil::getLengthAttr( node, "shadow_x", 0.0 );
			Distance shadowY       = XmlUtil::getLengthAttr( node, "shadow_y", 0.0 );
			double   shadowOpacity = XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 );

			key        = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			field_flag = !key.isEmpty();
			color      = XmlUtil::getUIntAttr( node, "shadow_color", 0 );
			ColorNode shadowColorNode( field_flag, color, key );

			return new ModelLineObject( x0, y0, dx, dy,
			                            lineWidth, lineColorNode,
						    affineTransformation,
			                            shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
		}


		ModelImageObject*
		XmlLabelParser_0_4::parseObjectImageNode( const QDomElement &node, const DataCache& data )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs */
			Distance w = XmlUtil::getLengthAttr( node, "w", 0 );
			Distance h = XmlUtil::getLengthAttr( node, "h", 0 );

			/* file attrs */
			QString key        = XmlUtil::getStringAttr( node, "field", "" );
			bool    field_flag = !key.isEmpty();
			QString filename   = XmlUtil::getStringAttr( node, "src", "" );
			TextNode filenameNode( field_flag, field_flag ? key : filename );

			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			/* shadow attrs */
			bool     shadowState   = XmlUtil::getBoolAttr( node, "shadow", false );
			Distance shadowX       = XmlUtil::getLengthAttr( node, "shadow_x", 0.0 );
			Distance shadowY       = XmlUtil::getLengthAttr( node, "shadow_y", 0.0 );
			double   shadowOpacity = XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 );

			key            = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			field_flag     = !key.isEmpty();
			uint32_t color = XmlUtil::getUIntAttr( node, "shadow_color", 0 );
			ColorNode shadowColorNode( field_flag, color, key );

			if ( filenameNode.isField() )
			{
				return new ModelImageObject( x0, y0, w, h,
				                             filenameNode,
							     affineTransformation,
				                             shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
			}
			if ( data.hasImage( filename ) )
			{
				return new ModelImageObject( x0, y0, w, h,
							     filename, data.getImage( filename ),
							     affineTransformation,
							     shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
			}
			if ( data.hasSvg( filename ) )
			{
				return new ModelImageObject( x0, y0, w, h,
							     filename, data.getSvg( filename ),
							     affineTransformation,
							     shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
			}
			qWarning() << "Embedded file" << filename << "missing. Trying actual file.";
			return new ModelImageObject( x0, y0, w, h,
						     filenameNode,
						     affineTransformation,
						     shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
		}


		ModelBarcodeObject*
		XmlLabelParser_0_4::parseObjectBarcodeNode( const QDomElement &node )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs */
			Distance w = XmlUtil::getLengthAttr( node, "w", 0 );
			Distance h = XmlUtil::getLengthAttr( node, "h", 0 );

			/* barcode attrs */
			auto backend = XmlUtil::getStringAttr( node, "backend", "");
			// one major difference between glabels-3.0.dtd and glabels-4.0.dtd
			// is the lowercase of the style names
			auto style = XmlUtil::getStringAttr( node, "style", "").toLower();
			if(backend == "libiec16022" & style == "iec16022")
			{
				backend = "";
				style = "datamatrix";
			}
			barcode::Style bcStyle = barcode::Backends::style( backend, style );
			bool bcTextFlag = XmlUtil::getBoolAttr( node, "text", true );
			bool bcChecksumFlag = XmlUtil::getBoolAttr( node, "checksum", true );

			QString  key        = XmlUtil::getStringAttr( node, "color_field", "" );
			bool     field_flag = !key.isEmpty();
			uint32_t color      = XmlUtil::getUIntAttr( node, "color", 0 );
			ColorNode bcColorNode( field_flag, color, key );

			QString bcData = XmlUtil::getStringAttr( node, "data", "" );
			if(bcData.isEmpty())
			{
				bcData = XmlUtil::getStringAttr( node, "field", "" );
			}

			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			return new ModelBarcodeObject( x0, y0, w, h,
			                               bcStyle, bcTextFlag, bcChecksumFlag, bcData, bcColorNode,
						       affineTransformation );
		}

		QMatrix
		XmlLabelParser_0_4::parseAffineTransformation(const QDomElement &node)
		{
			return {XmlUtil::getDoubleAttr( node, "a0", 1.0 ),
				XmlUtil::getDoubleAttr( node, "a1", 0.0 ),
				XmlUtil::getDoubleAttr( node, "a2", 0.0 ),
				XmlUtil::getDoubleAttr( node, "a3", 1.0 ),
				XmlUtil::getDoubleAttr( node, "a4", 0.0 ),
				XmlUtil::getDoubleAttr( node, "a5", 0.0 )};
		}

		ModelTextObject*
		XmlLabelParser_0_4::parseObjectTextNode( const QDomElement &node )
		{
			/* position attrs */
			Distance x0 = XmlUtil::getLengthAttr( node, "x", 0.0 );
			Distance y0 = XmlUtil::getLengthAttr( node, "y", 0.0 );

			/* size attrs */
			Distance w = XmlUtil::getLengthAttr( node, "w", 0 );
			Distance h = XmlUtil::getLengthAttr( node, "h", 0 );



			/* justify attr */
			Qt::Alignment textHAlign           = getHAlignmentAttr( node, "justify", Qt::AlignLeft );

			/* valign attr */
			Qt::Alignment textVAlign           = getVAlignmentAttr( node, "valign", Qt::AlignTop );

			/* auto_shrink attr */
			bool textAutoShrink                = XmlUtil::getBoolAttr( node, "auto_shrink", false );

			/* affine attrs */
			auto affineTransformation = parseAffineTransformation(node);

			/* shadow attrs */
			bool     shadowState   = XmlUtil::getBoolAttr( node, "shadow", false );
			Distance shadowX       = XmlUtil::getLengthAttr( node, "shadow_x", 0.0 );
			Distance shadowY       = XmlUtil::getLengthAttr( node, "shadow_y", 0.0 );
			double   shadowOpacity = XmlUtil::getDoubleAttr( node, "shadow_opacity", 1.0 );

			QString key            = XmlUtil::getStringAttr( node, "shadow_color_field", "" );
			bool field_flag        = !key.isEmpty();
			uint32_t color         = XmlUtil::getUIntAttr( node, "shadow_color", 0 );
			ColorNode shadowColorNode( field_flag, color, key );

			/* font attrs */
			QString       fontFamily = "Sans";
			double        fontSize = 10.;
			QFont::Weight fontWeight = QFont::Normal;
			bool          fontItalicFlag = false;

			/* text attrs */
			double textLineSpacing = 1.;
			QTextOption::WrapMode textWrapMode = QTextOption::WordWrap;

			ColorNode textColorNode;

			/* deserialize contents. */
			QTextDocument document;
			QTextCursor cursor( &document );
			bool firstBlock = true;
			for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
			{
				QString tagName = child.toElement().tagName();

				if(tagName == "Span")
				{
					QString text;
					QDomElement element = child.toElement();
					for(QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
					{
						QDomText t = n.toText();
						if (!t.isNull())
						{
							text += t.data();
						}
						else
						{
							if(n.toElement().tagName() == "NL")
							{
								text += "\n";
							}
						}
					}

					if ( !firstBlock )
					{
						cursor.insertBlock();
					}
					firstBlock = false;

					cursor.insertText( text );

					/* font attrs */
					fontFamily        = XmlUtil::getStringAttr( element, "font_family", "Sans" );
					fontSize          = XmlUtil::getDoubleAttr( element, "font_size", 10 ) * 0.75;
					fontWeight        = getWeightAttr( element, "font_weight", QFont::Normal );
					fontItalicFlag    = XmlUtil::getBoolAttr( element, "font_italic", false );

					/* color attr */
					key        = XmlUtil::getStringAttr( element, "color_field", "" );
					field_flag = !key.isEmpty();
					color      = XmlUtil::getUIntAttr( element, "color", 0 );

					textColorNode = ColorNode(field_flag, color, key );

					/* text attrs */
					textLineSpacing   = XmlUtil::getDoubleAttr( element, "line_spacing", 1 );
					textWrapMode = QTextOption::WordWrap;

				}
				else if ( !child.isComment() )
				{
					qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
				}
			}
			QString text = document.toPlainText();

			return new ModelTextObject( x0, y0, w, h, text,
						fontFamily, fontSize, fontWeight, fontItalicFlag, false,
						textColorNode, textHAlign, textVAlign, textWrapMode, textLineSpacing,
						textAutoShrink,
						affineTransformation,
						shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode );
		}


		bool
		XmlLabelParser_0_4::parseRotateAttr( const QDomElement &node )
		{
			return XmlUtil::getBoolAttr( node, "rotate", false );
		}


		void
		XmlLabelParser_0_4::parseMergeNode( const QDomElement &node, Model* label )
		{
			QString type = XmlUtil::getStringAttr( node, "type", "None" );
			QString src  = XmlUtil::getStringAttr( node, "src", "" );

			merge::Merge* merge = merge::Factory::createMerge( type );
			merge->setSource( src );

			label->setMerge( merge );
		}


		void
		XmlLabelParser_0_4::parseDataNode( const QDomElement &node, DataCache& data )
		{
			for ( QDomNode child = node.firstChild(); !child.isNull(); child = child.nextSibling() )
			{
				QString tagName = child.toElement().tagName();

				if ( tagName == "File" )
				{
					parseFileNode( child.toElement(), data );
				}
				else if (tagName == "Pixdata")
				{
					parsePixdataNode(child.toElement(), data);
				}
				else if ( !child.isComment() )
				{
					qWarning() << "Unexpected" << node.tagName() << "child:" << tagName;
				}
			}
		}


		void
		XmlLabelParser_0_4::parsePixdataNode( const QDomElement& node, DataCache& data )
		{
			QString name     = XmlUtil::getStringAttr( node, "name", "" );
			QString encoding = XmlUtil::getStringAttr( node, "encoding", "base64" );

			/*
			 * Struct of the GdkPixdata from the header file
			 */
			struct _GdkPixdata
			{
				uint32_t magic;        /* GDK_PIXBUF_MAGIC_NUMBER */
				int32_t  length;       /* <1 to disable length checks, otherwise:
							* GDK_PIXDATA_HEADER_LENGTH + pixel_data length*/
				uint32_t pixdata_type; /* GdkPixdataType */
				uint32_t rowstride;
				uint32_t width;
				uint32_t height;
				//uint8_t *pixel_data;
			} mypixdata{};

			if ( encoding.toLower() == "base64" )
			{
				QByteArray ba64 = node.text().toUtf8();
				QByteArray ba = QByteArray::fromBase64( ba64 );

				// Use the QDataStream to import the header cause it is in big endian
				QDataStream ds(ba);
				ds.setByteOrder(QDataStream::ByteOrder::BigEndian);

				ds >> mypixdata.magic
				   >> mypixdata.length
				   >> mypixdata.pixdata_type
				   >> mypixdata.rowstride
				   >> mypixdata.width
				   >> mypixdata.height;

				if(mypixdata.magic !=GDK_PIXBUF_MAGIC_NUMBER)
				{
					qCritical() << "GDK pixbuf magic is not correct. Abort reading of pixdata. "
						    << "Node:" << node.tagName();
					return;
				}

				// check if the data fits in a sigend int
				if(mypixdata.width > INT32_MAX || mypixdata.height > INT32_MAX || mypixdata.rowstride > INT32_MAX)
				{
					qCritical() << "rowstride, width or height is to large. Abort reading of pixdata. "
						    << "Node:" << node.tagName();;
					return;
				}

				const auto width = static_cast<int32_t>(mypixdata.width);
				const auto height = static_cast<int32_t>(mypixdata.height);
				const auto rowstride = static_cast<int32_t>(mypixdata.rowstride);

				QImage::Format pixformat;
				int32_t rawpadding;
				if((mypixdata.pixdata_type & GDK_PIXDATA_COLOR_TYPE_MASK) == GDK_PIXDATA_COLOR_TYPE_RGB)
				{
					pixformat = QImage::Format_RGB888;
					rawpadding = rowstride - (3 * width);
				}
				else if((mypixdata.pixdata_type & GDK_PIXDATA_COLOR_TYPE_MASK) == GDK_PIXDATA_COLOR_TYPE_RGBA)
				{
					pixformat = QImage::Format_RGBA8888;
					rawpadding = rowstride - (4 * width);
				}
				else
				{
					qCritical() << "pixdata color type is unknown. Abort reading of pixdata. "
						    << "Node:" << node.tagName();
					return;
				}

				if(rawpadding < 0){
					qCritical() << "padding to is negativ. Abort reading of pixdata. "
						    << "Node:" << node.tagName();
					return;
				}

				QImage image(width, height, pixformat);

				const auto padding = static_cast<int32_t>(rawpadding);

				int x = 0;
				int y = 0;
				uint8_t r,g,b,a;
				for(y = 0; y < height; y++)
				{
					for(x = 0; x < width; x++)
					{
						if(pixformat == QImage::Format_RGB888)
						{
							ds >> r >> g >> b;
							image.setPixelColor(x, y, QColor(r, g, b));
						}
						else
						{
							ds >> r >> g >> b >> a;
							image.setPixelColor(x, y, QColor(r, g, b, a));
						}

					}
					ds.skipRawData(padding);
				}

				data.addImage( name, image );
			}
			else
			{
				qWarning() << "Unexpected encoding:" << encoding << "node:" << node.tagName();
			}
		}


		void
		XmlLabelParser_0_4::parseFileNode( const QDomElement& node, DataCache& data )
		{
			QString name     = XmlUtil::getStringAttr( node, "name", "" );
			QString format = XmlUtil::getStringAttr( node, "format", "invalid" );

			if ( format == "SVG" )
			{
				data.addSvg( name, node.text().toUtf8() );
			}
			else
			{
				qCritical() << "Unknown embedded file format:" << format;
			}
		}

		Qt::Alignment
		XmlLabelParser_0_4::getHAlignmentAttr( const QDomElement& node, const QString&     name,
						 Qt::Alignment      default_value )
		{

			QString valueString = node.attribute( name, "" );
			if ( !valueString.isEmpty())
			{
				if ( valueString == "Right" )
				{
					return Qt::AlignRight;
				}
				if ( valueString == "Center")
				{
					return Qt::AlignHCenter;
				}
				if ( valueString == "Left" )
				{
					return Qt::AlignLeft;
				}
			}
			return default_value;
		}

		Qt::Alignment
		XmlLabelParser_0_4::getVAlignmentAttr( const QDomElement& node, const QString&     name,
							 Qt::Alignment      default_value )
		{

			QString valueString = node.attribute( name, "" );
			if ( ! valueString.isEmpty() )
			{
				if ( valueString == "Bottom" )
				{
					return Qt::AlignBottom;
				}
				if ( valueString == "Center" )
				{
					return Qt::AlignVCenter;
				}
				if ( valueString == "Top" )
				{
					return Qt::AlignTop;
				}
			}

			return default_value;
		}

		QFont::Weight
		XmlLabelParser_0_4::getWeightAttr( const QDomElement& node, const QString&     name,
					     QFont::Weight      default_value )
		{
			QString valueString = node.attribute( name, "" );
			if ( valueString != "" )
			{
				if ( valueString == "Bold" )
				{
					return QFont::Bold;
				}
				if ( valueString == "Regular" )
				{
					return QFont::Normal;
				}
			}

			return default_value;
		}

	}  // namespace model
}  // namespace glabels
