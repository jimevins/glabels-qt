/*  LabelModel.cpp
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

#include "LabelModel.h"

#include <QFileInfo>
#include <algorithm>
#include <cmath>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QtDebug>

#include "LabelModelObject.h"
#include "LabelRegion.h"
#include "XmlLabelCreator.h"
#include "XmlLabelParser.h"


namespace
{
	const QString MIME_TYPE = "application/x-glabels-objects";
}


///
/// Default constructor.
///
LabelModel::LabelModel() : mUntitledInstance(0), mModified(true), mTmplate(0), mRotate(false)
{
}


///
/// Save model state
///
LabelModel* LabelModel::save() const
{
	LabelModel* savedModel = new LabelModel;
	savedModel->restore( this );

	return savedModel;
}


///
/// Restore model state
///
void LabelModel::restore( const LabelModel *savedModel )
{
	// Clear current object list
	foreach ( LabelModelObject* object, mObjectList )
	{
		delete object;
	}
	mObjectList.clear();

	// Now copy state
	mUntitledInstance = savedModel->mUntitledInstance;
	mModified         = savedModel->mModified;
	mFileName         = savedModel->mFileName;
	mCompressionLevel = savedModel->mCompressionLevel;
	mTmplate          = savedModel->mTmplate;
	mFrame            = savedModel->mFrame;
	mRotate           = savedModel->mRotate;

	foreach ( LabelModelObject* object, savedModel->mObjectList )
	{
		mObjectList.append( object->clone() );
	}

	// Emit signals based on potential changes
	emit changed();
	emit selectionChanged();
	emit modifiedChanged();
	emit nameChanged();
	emit sizeChanged();
}


///
/// Short name.
///
QString LabelModel::shortName()
{
	static int untitledCount = 0;
		
	if ( mFileName.isEmpty() )
	{
		if ( mUntitledInstance == 0 )
		{
			mUntitledInstance = ++untitledCount;
		}
		QString numString;
		numString.setNum(mUntitledInstance);;

		return tr("Untitled") + numString;
	}
	else
	{
		QFileInfo fileInfo( mFileName );
		return fileInfo.baseName();
	}
}


///
/// Clear modified status
///
void LabelModel::clearModified()
{
	mModified = false;
	emit modifiedChanged();
}


///
/// Add object.
///
void LabelModel::addObject( LabelModelObject* object )
{
	object->setParent( this );
	mObjectList << object;

	connect( object, SIGNAL(changed()), this, SLOT(onObjectChanged()) );
	connect( object, SIGNAL(moved()), this, SLOT(onObjectMoved()) );

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Delete Object
///
void LabelModel::deleteObject( LabelModelObject* object )
{
	object->unselect();
	mObjectList.removeOne( object );

	disconnect( object, 0, this, 0 );

	mModified = true;

	emit changed();
	emit modifiedChanged();

	delete object;
}


///
/// Object at x,y
///
LabelModelObject* LabelModel::objectAt( double                   scale,
					const glabels::Distance& x,
					const glabels::Distance& y ) const
{
	/* Search object list in reverse order.  I.e. from top to bottom. */
	QList<LabelModelObject*>::const_iterator it = mObjectList.end();
	while ( it != mObjectList.begin() )
	{
		it--;
		LabelModelObject* object = *it;
		if ( object->isLocatedAt( scale, x, y ) )
		{
			return object;
		}
	}

	return 0;
}


///
/// Handle at x,y
///
Handle* LabelModel::handleAt( double                   scale,
			      const glabels::Distance& x,
			      const glabels::Distance& y ) const
{
	foreach( LabelModelObject* object, mObjectList )
	{
		Handle* handle = object->handleAt( scale, x, y );
		if ( handle )
		{
			return handle;
		}
	}

	return 0;
}


///
/// Object Changed Slot
///
void LabelModel::onObjectChanged()
{
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Object Moved Slot
///
void LabelModel::onObjectMoved()
{
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Select Object
///
void LabelModel::selectObject( LabelModelObject* object )
{
	object->select();

	emit selectionChanged();
}


///
/// Unselect Object
///
void LabelModel::unselectObject( LabelModelObject* object )
{
	object->unselect();

	emit selectionChanged();
}


///
/// Select All Objects
///
void LabelModel::selectAll()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		object->select();
	}

	emit selectionChanged();
}


///
/// Unselect All Objects
///
void LabelModel::unselectAll()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		object->unselect();
	}

	emit selectionChanged();
}


///
/// Select Region
///
void LabelModel::selectRegion( const LabelRegion &region )
{
	using std::min;
	using std::max;

	glabels::Distance rX1 = min( region.x1(), region.x2() );
	glabels::Distance rY1 = min( region.y1(), region.y2() );
	glabels::Distance rX2 = max( region.x1(), region.x2() );
	glabels::Distance rY2 = max( region.y1(), region.y2() );

	foreach ( LabelModelObject* object, mObjectList )
	{
		LabelRegion objectExtent = object->getExtent();

		if ( (objectExtent.x1() >= rX1) &&
		     (objectExtent.x2() <= rX2) &&
		     (objectExtent.y1() >= rY1) &&
		     (objectExtent.y2() <= rY2) )
		{
			object->select();
		}
	}

	emit selectionChanged();
}


///
/// Is Selection Empty?
///
bool LabelModel::isSelectionEmpty()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			return false;
		}
	}

	return true;
}


///
/// Is Selection Atomic?
///
bool LabelModel::isSelectionAtomic()
{
	int nSelected = 0;

	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			nSelected++;
			if ( nSelected > 1 )
			{
				return false;
			}
		}
	}

	return (nSelected == 1);
}


///
/// Get List of Selected Objects
///
QList<LabelModelObject*> LabelModel::getSelection()
{
	QList<LabelModelObject*> selectedList;

	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			selectedList << object;
		}
	}

	return selectedList;
}


///
/// Get First Object in Selection List
///
LabelModelObject* LabelModel::getFirstSelectedObject()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			return object;
		}
	}
}


///
/// Can Any Objects in Selection Accept Text Properties?
///
bool LabelModel::canSelectionText()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() && object->canText() )
		{
			return true;
		}
	}

	return false;
}


///
/// Can Any Objects in Selection Accept Fill Property?
///
bool LabelModel::canSelectionFill()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() && object->canFill() )
		{
			return true;
		}
	}

	return false;
}


///
/// Can Any Objects in Selection Accept Line Color Property?
///
bool LabelModel::canSelectionLineColor()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() && object->canLineColor() )
		{
			return true;
		}
	}

	return false;
}


///
/// Can Any Objects in Selection Accept Line Width Property?
///
bool LabelModel::canSelectionLineWidth()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() && object->canLineWidth() )
		{
			return true;
		}
	}

	return false;
}


///
/// Delete Selected Objects
///
void LabelModel::deleteSelection()
{
	QList<LabelModelObject*> selectedList = getSelection();

	foreach ( LabelModelObject* object, selectedList )
	{
		deleteObject( object );
	}

	mModified = true;

	emit changed();
	emit selectionChanged();
	emit modifiedChanged();
}


///
/// Raise Selected Objects To Top
///
void LabelModel::raiseSelectionToTop()
{
	QList<LabelModelObject*> selectedList = getSelection();

	foreach ( LabelModelObject* object, selectedList )
	{
		mObjectList.removeOne( object );
	}

	/// Move to end of list, representing top most object.
	foreach ( LabelModelObject* object, selectedList )
	{
		mObjectList.push_back( object );
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Lower Selected Objects To Bottom
///
void LabelModel::lowerSelectionToBottom()
{
	QList<LabelModelObject*> selectedList = getSelection();

	foreach ( LabelModelObject* object, selectedList )
	{
		mObjectList.removeOne( object );
	}

	/// Move to front of list, representing bottom most object.
	foreach ( LabelModelObject* object, selectedList )
	{
		mObjectList.push_front( object );
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Rotate Selected Objects
///
void LabelModel::rotateSelection( double thetaDegs )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->rotate( thetaDegs );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Rotate Selected Objects Left 90 degrees
///
void LabelModel::rotateSelectionLeft()
{
	rotateSelection( -90.0 );
}


///
/// Rotate Selected Objects Right 90 degrees
///
void LabelModel::rotateSelectionRight()
{
	rotateSelection( 90.0 );
}


///
/// Flip Selected Objects Horizontally
///
void LabelModel::flipSelectionHoriz()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->flipHoriz();
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Flip Selected Objects Vertically
///
void LabelModel::flipSelectionVert()
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->flipVert();
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Left Edges
///
void LabelModel::alignSelectionLeft()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find left-most edge.
	glabels::Distance x1_min = 7200; /// Start with a very large value: 7200pts = 100in
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		if ( r.x1() < x1_min ) x1_min = r.x1();
	}

	/// Now adjust the object positions to line up the left edges at left-most edge.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dx = x1_min - r.x1();
		object->setPositionRelative( dx, 0 );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Right Edges
///
void LabelModel::alignSelectionRight()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find right-most edge.
	glabels::Distance x1_max = -7200; /// Start with a very large negative value: 7200pts = 100in
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		if ( r.x1() > x1_max ) x1_max = r.x1();
	}

	/// Now adjust the object positions to line up the right edges at right-most edge.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dx = x1_max - r.x1();
		object->setPositionRelative( dx, 0 );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Horizontal Centers
///
void LabelModel::alignSelectionHCenter()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find average center of objects.
	glabels::Distance xsum = 0;
	int n = 0;
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		xsum += (r.x1() + r.x2()) / 2.0;
		n++;
	}
	glabels::Distance xavg = xsum / n;

	/// Find object closest to average center of objects.
	glabels::Distance xcenter = 7200; /// Start with very large value.
	glabels::Distance dxmin = fabs( xavg - xcenter );
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dx = fabs( xavg - (r.x1() + r.x2())/2.0 );
		if ( dx < dxmin )
		{
			dxmin = dx;
			xcenter = (r.x1() + r.x2()) / 2.0;
		}
	}

	/// Now adjust the object positions to line up with the center of this object.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dx = xcenter - (r.x1() + r.x2())/2.0;
		object->setPositionRelative( dx, 0 );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Top Edges
///
void LabelModel::alignSelectionTop()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find top-most edge.
	glabels::Distance y1_min = 7200; /// Start with a very large value: 7200pts = 100in
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		if ( r.y1() < y1_min ) y1_min = r.y1();
	}

	/// Now adjust the object positions to line up the top edges at top-most edge.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dy = y1_min - r.y1();
		object->setPositionRelative( 0, dy );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Bottom Edges
///
void LabelModel::alignSelectionBottom()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find bottom-most edge.
	glabels::Distance y1_max = -7200; /// Start with a very large negative value: 7200pts = 100in
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		if ( r.y1() > y1_max ) y1_max = r.y1();
	}

	/// Now adjust the object positions to line up the bottom edges at bottom-most edge.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dy = y1_max - r.y1();
		object->setPositionRelative( 0, dy );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Their Vertical Centers Edges
///
void LabelModel::alignSelectionVCenter()
{
	if ( isSelectionEmpty() || isSelectionAtomic() )
	{
		return;
	}

	QList<LabelModelObject*> selectedList = getSelection();

	/// Find average center of objects.
	glabels::Distance ysum = 0;
	int n = 0;
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		ysum += (r.y1() + r.y2()) / 2.0;
		n++;
	}
	glabels::Distance yavg = ysum / n;

	/// Find object closest to average center of objects.
	glabels::Distance ycenter = 7200; /// Start with very large value.
	glabels::Distance dymin = fabs( yavg - ycenter );
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dy = fabs( yavg - (r.y1() + r.y2())/2.0 );
		if ( dy < dymin )
		{
			dymin = dy;
			ycenter = (r.y1() + r.y2()) / 2.0;
		}
	}

	/// Now adjust the object positions to line up with the center of this object.
	foreach ( LabelModelObject* object, selectedList )
	{
		LabelRegion r = object->getExtent();
		glabels::Distance dy = ycenter - (r.y1() + r.y2())/2.0;
		object->setPositionRelative( 0, dy );
	}
		
	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Center Of Label Horizontally
///
void LabelModel::centerSelectionHoriz()
{
	glabels::Distance xLabelCenter = w() / 2.0;

	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			LabelRegion r = object->getExtent();
			glabels::Distance xObjectCenter = (r.x1() + r.x2()) / 2.0;
			glabels::Distance dx = xLabelCenter - xObjectCenter;
			object->setPositionRelative( dx, 0 );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Align Selected Objects To Center Of Label Vertically
///
void LabelModel::centerSelectionVert()
{
	glabels::Distance yLabelCenter = h() / 2.0;

	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			LabelRegion r = object->getExtent();
			glabels::Distance yObjectCenter = (r.y1() + r.y2()) / 2.0;
			glabels::Distance dy = yLabelCenter - yObjectCenter;
			object->setPositionRelative( 0, dy );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Move Selected Objects By dx,dy
///
void LabelModel::moveSelection( const glabels::Distance& dx, const glabels::Distance& dy )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setPositionRelative( dx, dy );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Font Family Of Selected Objects
///
void LabelModel::setSelectionFontFamily( const QString &fontFamily )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setFontFamily( fontFamily );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Font Size Of Selected Objects
///
void LabelModel::setSelectionFontSize( double fontSize )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setFontSize( fontSize );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Font Weight Of Selected Objects
///
void LabelModel::setSelectionFontWeight( QFont::Weight fontWeight )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setFontWeight( fontWeight );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Font Italic Flag Of Selected Objects
///
void LabelModel::setSelectionFontItalicFlag( bool fontItalicFlag )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setFontItalicFlag( fontItalicFlag );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Text Horizontal Alignment Of Selected Objects
///
void LabelModel::setSelectionTextHAlign( Qt::Alignment textHAlign )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setTextHAlign( textHAlign );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Text Vertical Alignment Of Selected Objects
///
void LabelModel::setSelectionTextVAlign( Qt::Alignment textVAlign )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setTextVAlign( textVAlign );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Text Line Spacing Of Selected Objects
///
void LabelModel::setSelectionTextLineSpacing( double textLineSpacing )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setTextLineSpacing( textLineSpacing );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Text Color Node Of Selected Objects
///
void LabelModel::setSelectionTextColorNode( ColorNode textColorNode )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setTextColorNode( textColorNode );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Line Width Of Selected Objects
///
void LabelModel::setSelectionLineWidth( const glabels::Distance& lineWidth )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setLineWidth( lineWidth );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Line Color Node Of Selected Objects
///
void LabelModel::setSelectionLineColorNode( ColorNode lineColorNode )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setLineColorNode( lineColorNode );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Set Fill Color Node Of Selected Objects
///
void LabelModel::setSelectionFillColorNode( ColorNode fillColorNode )
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		if ( object->isSelected() )
		{
			object->setFillColorNode( fillColorNode );
		}
	}

	mModified = true;

	emit changed();
	emit modifiedChanged();
}


///
/// Copy selection to clipboard
///
void LabelModel::copySelection()
{
	if ( !isSelectionEmpty() )
	{
		QClipboard *clipboard = QApplication::clipboard();
		
		QByteArray buffer;
		XmlLabelCreator::serializeObjects( getSelection(), buffer );

		QMimeData *mimeData = new QMimeData;
		mimeData->setData( MIME_TYPE, buffer );

		clipboard->setMimeData( mimeData );
	}
}


///
/// Cut selection to clipboard
///
void LabelModel::cutSelection()
{
	copySelection();
	deleteSelection();
}


///
/// Can we paste?
///
bool LabelModel::canPaste()
{
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	if ( mimeData->hasFormat( MIME_TYPE ) )
	{
		return true;
	}
	else if ( mimeData->hasImage() )
	{
		// TODO: return true
	}
	else if ( mimeData->hasText() )
	{
		// TODO: return true
	}
	return false;
}


///
/// Paste from clipboard
///
void LabelModel::paste()
{
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	if ( mimeData->hasFormat( MIME_TYPE ) )
	{
		QByteArray buffer = mimeData->data( MIME_TYPE );
		QList <LabelModelObject*> objects = XmlLabelParser::deserializeObjects( buffer );

		unselectAll();
		foreach ( LabelModelObject* object, objects )
		{
			addObject( object );
			selectObject( object );
		}
	}
	else if ( mimeData->hasImage() )
	{
		// TODO: create an image object from image
	}
	else if ( mimeData->hasText() )
	{
		// TODO: create a text object from text
	}
}


///
/// Draw label objects
///
void LabelModel::draw( QPainter* painter, bool inEditor, MergeRecord* record ) const
{
	foreach ( LabelModelObject* object, mObjectList )
	{
		object->draw( painter, inEditor, record );
	}
}
