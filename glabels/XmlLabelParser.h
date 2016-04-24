/*  XmlLabelParser.h
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

#ifndef XmlLabelParser_h
#define XmlLabelParser_h


#include <QObject>
#include <QDomElement>


class LabelModel;
class LabelModelObject;
class LabelModelBoxObject;
class LabelModelEllipseObject;
class LabelModelLineObject;
class LabelModelImageObject;
class LabelModelBarcodeObject;
class LabelModelTextObject;


///
/// XmlLabelParser
///
class XmlLabelParser : public QObject
{
	Q_OBJECT

public:
	static LabelModel* readFile( const QString& fileName );
	static LabelModel* readBuffer( const QString& buffer );
	static QList<LabelModelObject*> deserializeObjects( const QString& buffer );

private:
	static void gunzip( const QByteArray& gzippedData, QByteArray& data );
	static LabelModel* parseRootNode( const QDomElement &node );
	static QList<LabelModelObject*> parseObjects( const QDomElement &node );
	static void parseObjectsNode( const QDomElement &node, LabelModel* label );
	static LabelModelBoxObject* parseObjectBoxNode( const QDomElement &node );
	static LabelModelEllipseObject* parseObjectEllipseNode( const QDomElement &node );
	static LabelModelLineObject* parseObjectLineNode( const QDomElement &node );
	static LabelModelImageObject* parseObjectImageNode( const QDomElement &node );
	static LabelModelBarcodeObject* parseObjectBarcodeNode( const QDomElement &node );
	static LabelModelTextObject* parseObjectTextNode( const QDomElement &node );
	static void parseTopLevelSpanNode( const QDomElement &node, LabelModelTextObject* object );
	static void parseAffineAttrs( const QDomElement &node, LabelModelObject* object );
	static void parseShadowAttrs( const QDomElement &node, LabelModelObject* object );
	static void parseMergeNode( const QDomElement &node, LabelModel* label );
	static void parseDataNode( const QDomElement &node, LabelModel* label );
	static void parsePixdataNode( const QDomElement &node, LabelModel* label );
	static void parseFileNode( const QDomElement &node, LabelModel* label );

};


#endif // XmlLabelParser_h
