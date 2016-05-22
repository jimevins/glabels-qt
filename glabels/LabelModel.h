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

#include "libglabels/Template.h"
#include "Merge/Merge.h"
#include "Merge/Record.h"

#include "Settings.h"


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
	// Save/restore model state
	/////////////////////////////////
	LabelModel* save() const;
	void restore( const LabelModel *savedModel );
	

	/////////////////////////////////
	// Signals
	/////////////////////////////////
signals:
	void changed();
	void nameChanged();
	void sizeChanged();
	void selectionChanged();
	void modifiedChanged();
	void mergeChanged();
	void mergeSourceChanged();


	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	bool isModified() const;
	void setModified();
	void clearModified();

	QString shortName();
	const QString& fileName() const;
	void setFileName( const QString &fileName );

	int compressionLevel() const;
	void setCompressionLevel( int compressionLevel );

	const glabels::Template* tmplate() const;
	const glabels::Frame* frame() const;
	void setTmplate( const glabels::Template* tmplate );

	bool rotate() const;
	void setRotate( bool rotate );

	glabels::Distance w() const;
	glabels::Distance h() const;

	const QList<LabelModelObject*>& objectList() const;

	merge::Merge* merge() const;
	void setMerge( merge::Merge* merge );
	
		
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
	// Clipboard operations
	/////////////////////////////////
	void copySelection();
	void cutSelection();
	bool canPaste();
	void paste();
	
	/////////////////////////////////
	// Drawing operations
	/////////////////////////////////
public:
	void draw( QPainter* painter, bool inEditor = true, merge::Record* record = 0 ) const;

		
	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onObjectChanged();
	void onObjectMoved();
	void onMergeSourceChanged();


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

	merge::Merge*             mMerge;
};


#endif // LabelModel_h
