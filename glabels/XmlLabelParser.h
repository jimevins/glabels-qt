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


namespace glabels
{

	// Forward references
	class LabelModel;
	class LabelModelObject;
	class LabelModelBoxObject;
	class LabelModelEllipseObject;
	class LabelModelLineObject;
	class LabelModelImageObject;
	class LabelModelBarcodeObject;
	class LabelModelTextObject;
	class DataCache;


	///
	/// XmlLabelParser
	///
	class XmlLabelParser : public QObject
	{
		Q_OBJECT

	public:
		static LabelModel* readFile( const QString& fileName );
		static LabelModel* readBuffer( const QByteArray& buffer );
		static QList<LabelModelObject*> deserializeObjects( const QByteArray& buffer );

	private:
		static void gunzip( const QByteArray& gzippedData, QByteArray& data );
		static LabelModel* parseRootNode( const QDomElement &node );
		static QList<LabelModelObject*> parseObjectsNode( const QDomElement &node, const DataCache& data );
		static LabelModelBoxObject* parseObjectBoxNode( const QDomElement &node );
		static LabelModelEllipseObject* parseObjectEllipseNode( const QDomElement &node );
		static LabelModelLineObject* parseObjectLineNode( const QDomElement &node );
		static LabelModelImageObject* parseObjectImageNode( const QDomElement &node, const DataCache& data );
		static LabelModelBarcodeObject* parseObjectBarcodeNode( const QDomElement &node );
		static LabelModelTextObject* parseObjectTextNode( const QDomElement &node );
		static QString parsePNode( const QDomElement &node );
		static void parseAffineAttrs( const QDomElement &node, LabelModelObject* object );
		static void parseShadowAttrs( const QDomElement &node, LabelModelObject* object );
		static void parseMergeNode( const QDomElement &node, LabelModel* label );
		static void parseDataNode( const QDomElement &node, DataCache& data );
		static void parsePixdataNode( const QDomElement &node, DataCache& data );
		static void parseFileNode( const QDomElement &node, DataCache& data );

	};

}


#endif // XmlLabelParser_h
