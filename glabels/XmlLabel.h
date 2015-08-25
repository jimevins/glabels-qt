/*  XmlLabel.h
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

#ifndef glabels_XmlLabel_h
#define glabels_XmlLabel_h


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
	/// XmlLabel Actions
	///
	class XmlLabel : public QObject
	{
		Q_OBJECT

	public:
		static LabelModel* readFile( const QString& fileName );
		static LabelModel* readBuffer( const QString& buffer );
		static void writeFile( const LabelModel* label, const QString& fileName );
		static void writeBuffer( const LabelModel* label, QString& buffer );

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

		static void createDoc( QDomDocument& doc, const LabelModel* label );
		static void createRootNode( const LabelModel* label );
		static void createObjectsNode( QDomElement &parent, const LabelModel* label );
		static void createObjectBoxNode( QDomElement &parent, const LabelModelBoxObject* object );
		static void createObjectEllipseNode( QDomElement &parent, const LabelModelEllipseObject* object );
		static void createObjectLineNode( QDomElement &parent, const LabelModelLineObject* object );
		static void createObjectImageNode( QDomElement &parent, const LabelModelImageObject* object );
		static void createObjectBarcodeNode( QDomElement &parent, const LabelModelBarcodeObject* object );
		static void createObjectTextNode( QDomElement &parent, const LabelModelTextObject* object );
		static void createObjectTopLevelSpanNode( QDomElement &parent, const LabelModelTextObject* object );
		static void createffineAttrs( QDomElement &node, const LabelModelObject* object );
		static void createShadowAttrs( QDomElement &node, const LabelModelObject* object );
		static void createMergeNode( QDomElement &node, LabelModel* label );
		static void createDataNode( QDomElement &node, LabelModel* label );
		static void createPixdataNode( QDomElement &node, LabelModel* label, const QString& name );
		static void createSvgFileNode( QDomElement &node, LabelModel* label, const QString& name );

	};

}

#endif // glabels_XmlLabel_h
