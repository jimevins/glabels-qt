/*  LabelModel.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#ifndef LabelModel_h
#define LabelModel_h

#include <QObject>
#include <QList>
#include <QPainter>

#include "MergeRecord.h"
#include "libglabels/Template.h"


// Forward References
class LabelModelObject;
class Handle;
class LabelRegion;
class ColorNode;


//////////////////////////////////////////////
//////////////////////////////////////////////
// LabelModel
//////////////////////////////////////////////
//////////////////////////////////////////////
class LabelModel : public QObject
{
	Q_OBJECT


	/////////////////////////////////
	// Lifecycle
	/////////////////////////////////
public:
	LabelModel();
	virtual ~LabelModel() {}


	/////////////////////////////////
	// Signals
	/////////////////////////////////
signals:
	void changed();
	void nameChanged();
	void sizeChanged();
	void selectionChanged();
	void modifiedChanged();


	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	inline bool isModified() const;
	void clearModified();

	QString shortName();
	inline const QString& fileName() const;
	inline void setFileName( const QString &fileName );

	inline int compressionLevel() const;
	inline void setCompressionLevel( int compressionLevel );

	inline const glabels::Template* tmplate() const;
	inline const glabels::Frame* frame() const;
	inline void setTmplate( const glabels::Template* tmplate );

	inline bool rotate() const;
	inline void setRotate( bool rotate );

	inline glabels::Distance w() const;
	inline glabels::Distance h() const;

	inline const QList<LabelModelObject*>& objectList() const;

		
	/////////////////////////////////
	// Manage objects
	/////////////////////////////////
public:
	void addObject( LabelModelObject* object );
	void deleteObject( LabelModelObject* object );

	LabelModelObject* objectAt( double                   scale,
	                            const glabels::Distance& x,
	                            const glabels::Distance& y ) const;
		
	Handle* handleAt( double                   scale,
	                  const glabels::Distance& x,
	                  const glabels::Distance& y ) const;


	/////////////////////////////////
	// Manipulate selection
	/////////////////////////////////
public:
	void selectObject( LabelModelObject* object );
	void unselectObject( LabelModelObject* object );
	void selectAll();
	void unselectAll();
	void selectRegion( const LabelRegion& region );
	bool isSelectionEmpty();
	bool isSelectionAtomic();


	/////////////////////////////////
	// Get selected objects
	/////////////////////////////////
public:
	QList<LabelModelObject*> getSelection();
	LabelModelObject* getFirstSelectedObject();


	/////////////////////////////////
	// Query selection capabilities
	/////////////////////////////////
public:
	bool canSelectionText();
	bool canSelectionFill();
	bool canSelectionLineColor();
	bool canSelectionLineWidth();


	/////////////////////////////////
	// Operations on selections
	/////////////////////////////////
public:
	void deleteSelection();
	void raiseSelectionToTop();
	void lowerSelectionToBottom();
	void rotateSelection( double thetaDegs );
	void rotateSelectionLeft();
	void rotateSelectionRight();
	void flipSelectionHoriz();
	void flipSelectionVert();
	void alignSelectionLeft();
	void alignSelectionRight();
	void alignSelectionHCenter();
	void alignSelectionTop();
	void alignSelectionBottom();
	void alignSelectionVCenter();
	void centerSelectionHoriz();
	void centerSelectionVert();
	void moveSelection( const glabels::Distance& dx, const glabels::Distance& dy );
	void setSelectionFontFamily( const QString& fontFamily );
	void setSelectionFontSize( double fontSize );
	void setSelectionFontWeight( QFont::Weight fontWeight );
	void setSelectionFontItalicFlag( bool fontItalicFlag );
	void setSelectionTextHAlign( Qt::Alignment textHAlign );
	void setSelectionTextVAlign( Qt::Alignment textVAlign );
	void setSelectionTextLineSpacing( double textLineSpacing );
	void setSelectionTextColorNode( ColorNode textColorNode );
	void setSelectionLineWidth( const glabels::Distance& lineWidth );
	void setSelectionLineColorNode( ColorNode lineColorNode );
	void setSelectionFillColorNode( ColorNode fillColorNode );


	/////////////////////////////////
	// Drawing operations
	/////////////////////////////////
public:
	void draw( QPainter* painter, bool inEditor = true, MergeRecord* record = 0 ) const;

		
	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onObjectChanged();
	void onObjectMoved();


	/////////////////////////////////
	// Private data
	/////////////////////////////////
private:
	int                       mUntitledInstance;
	bool                      mModified;
	QString                   mFileName;
	int                       mCompressionLevel;
	const glabels::Template*  mTmplate;
	const glabels::Frame*     mFrame;
	bool                      mRotate;

	QList<LabelModelObject*>  mObjectList;

};



/////////////////////////////////
// INLINE METHODS
/////////////////////////////////

inline bool LabelModel::isModified() const
{
	return mModified;
}


inline const QString& LabelModel::fileName() const
{
	return mFileName;
}


inline void LabelModel::setFileName( const QString &fileName )
{
	if ( mFileName != fileName )
	{
		mFileName = fileName;
		emit nameChanged();
	}
}


inline int LabelModel::compressionLevel() const
{
	return mCompressionLevel;
}


inline void LabelModel::setCompressionLevel( int compressionLevel )
{
	mCompressionLevel = compressionLevel;
}


inline const glabels::Template* LabelModel::tmplate() const
{
	return mTmplate;
}


inline const glabels::Frame* LabelModel::frame() const
{
	return mFrame;
}


inline void LabelModel::setTmplate( const glabels::Template* tmplate )
{
	if (mTmplate != tmplate)
	{
		mTmplate = tmplate;
		mFrame = tmplate->frames().first();
		mModified = true;
		emit changed();
		emit sizeChanged();
	}
}


inline bool LabelModel::rotate() const
{
	return mRotate;
}


inline void LabelModel::setRotate( bool rotate )
{
	if (mRotate != rotate)
	{
		mRotate = rotate;
		mModified = true;
		emit changed();
		emit sizeChanged();
	}
}


inline glabels::Distance LabelModel::w() const
{
	return mRotate ? mFrame->h() : mFrame->w();
}


inline glabels::Distance LabelModel::h() const
{
	return mRotate ? mFrame->w() : mFrame->h();
}


inline const QList<LabelModelObject*>& LabelModel::objectList() const
{
	return mObjectList;
}


#endif // LabelModel_h
