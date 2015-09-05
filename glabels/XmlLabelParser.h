/*  XmlLabelParser.h
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

#ifndef glabels_XmlLabelParser_h
#define glabels_XmlLabelParser_h


#include <QObject>
#include <QDomElement>


namespace glabels
{
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

	private:
		static void gunzip( const QByteArray& gzippedData, QByteArray& data );
		static LabelModel* parseRootNode( const QDomElement &node );
		static void parseObjectsNode( const QDomElement &node, LabelModel* label );
		static void parseObjectBoxNode( const QDomElement &node, LabelModel* label );
		static void parseObjectEllipseNode( const QDomElement &node, LabelModel* label );
		static void parseObjectLineNode( const QDomElement &node, LabelModel* label );
		static void parseObjectImageNode( const QDomElement &node, LabelModel* label );
		static void parseObjectBarcodeNode( const QDomElement &node, LabelModel* label );
		static void parseObjectTextNode( const QDomElement &node, LabelModel* label );
		static void parseTopLevelSpanNode( const QDomElement &node, LabelModelTextObject* object );
		static void parseAffineAttrs( const QDomElement &node, LabelModelObject* object );
		static void parseShadowAttrs( const QDomElement &node, LabelModelObject* object );
		static void parseMergeNode( const QDomElement &node, LabelModel* label );
		static void parseDataNode( const QDomElement &node, LabelModel* label );
		static void parsePixdataNode( const QDomElement &node, LabelModel* label );
		static void parseFileNode( const QDomElement &node, LabelModel* label );

	};

}

#endif // glabels_XmlLabelParser_h
