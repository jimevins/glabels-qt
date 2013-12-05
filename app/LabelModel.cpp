/*  LabelModel.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#include <cmath>


namespace glabels
{

	/**
	 * Default constructor.
	 */
	LabelModel::LabelModel() : mModified(true)
	{
	}


	/**
	 * Add item.
	 */
	void LabelModel::addItem( LabelModelItem *item )
	{
		item->setParent( this );
		mItemList << item;

		connect( item, SIGNAL(changed()), this, SLOT(itemChanged(LabelModelItem*)) );
		connect( item, SIGNAL(moved()), this, SLOT(itemMoved(LabelModelItem*)) );

		mModified = true;

		emit itemAdded( item );
		emit changed();
	}


	void LabelModel::onItemChanged( LabelModelItem *item )
	{
		mModified = true;

		emit itemChanged( item );
		emit changed();
	}


	void LabelModel::onItemMoved( LabelModelItem *item )
	{
		mModified = true;

		emit itemMoved( item );
		emit changed();
	}


	void LabelModel::deleteItem( LabelModelItem *item )
	{
		item->unselect();
		mItemList.removeOne( item );

		disconnect( item, 0, this, 0 );

		mModified = true;

		emit itemDeleted( item );
		emit changed();
	}


	/**
	 * Select item.
	 */
	void LabelModel::selectItem( LabelModelItem *item )
	{
		item->select();

		emit selectionChanged();
	}


	/**
	 * Unselect item.
	 */
	void LabelModel::unselectItem( LabelModelItem *item )
	{
		item->unselect();

		emit selectionChanged();
	}


	/**
	 * Select all items.
	 */
	void LabelModel::selectAll()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			item->select();
		}

		emit selectionChanged();
	}


	/**
	 * Unselect item all items.
	 */
	void LabelModel::unselectAll()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			item->unselect();
		}

		emit selectionChanged();
	}


	void LabelModel::selectRegion( const LabelRegion &region )
	{
		double rX1 = std::min( region.x1(), region.x2() );
		double rY1 = std::min( region.y1(), region.y2() );
		double rX2 = std::max( region.x1(), region.x2() );
		double rY2 = std::max( region.y1(), region.y2() );

		foreach ( LabelModelItem *item, mItemList )
		{
			LabelRegion itemExtent = item->getExtent();

			if ( (itemExtent.x1() >= rX1) &&
			     (itemExtent.x2() <= rX2) &&
			     (itemExtent.y1() >= rY1) &&
			     (itemExtent.y2() <= rY2) )
			{
				item->select();
			}
		}

		emit selectionChanged();
	}


	bool LabelModel::isSelectionEmpty()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				return false;
			}
		}

		return true;
	}


	bool LabelModel::isSelectionAtomic()
	{
		int nSelected = 0;

		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
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


	QList<LabelModelItem *> LabelModel::getSelection()
	{
		QList<LabelModelItem*> selectedList;

		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				selectedList << item;
			}
		}
		
	}


	LabelModelItem *LabelModel::getFirstSelectedItem()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				return item;
			}
		}
	}


	bool LabelModel::canSelectionText()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() && item->canText() )
			{
				return true;
			}
		}

		return false;
	}


	bool LabelModel::canSelectionFill()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() && item->canFill() )
			{
				return true;
			}
		}

		return false;
	}


	bool LabelModel::canSelectionLineColor()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() && item->canLineColor() )
			{
				return true;
			}
		}

		return false;
	}


	bool LabelModel::canSelectionLineWidth()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() && item->canLineWidth() )
			{
				return true;
			}
		}

		return false;
	}


	void LabelModel::deleteSelection()
	{
		QList<LabelModelItem*> selectedList = getSelection();

		foreach ( LabelModelItem *item, selectedList )
		{
			deleteItem( item );
		}

		mModified = true;

		emit changed();
		emit selectionChanged();
	}


	void LabelModel::raiseSelectionToTop()
	{
		QList<LabelModelItem*> selectedList = getSelection();

		foreach ( LabelModelItem *item, selectedList )
		{
			mItemList.removeOne( item );
		}

		/* Move to end of list, representing top most item. */
		foreach ( LabelModelItem *item, selectedList )
		{
			mItemList.push_back( item );
			emit itemToTop( item );
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::lowerSelectionToBottom()
	{
		QList<LabelModelItem*> selectedList = getSelection();

		foreach ( LabelModelItem *item, selectedList )
		{
			mItemList.removeOne( item );
		}

		/* Move to front of list, representing bottom most item. */
		foreach ( LabelModelItem *item, selectedList )
		{
			mItemList.push_front( item );
			emit itemToBottom( item );
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::rotateSelection( double thetaDegs )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->rotate( thetaDegs );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::rotateSelectionLeft()
	{
		rotateSelection( -90.0 );
	}


	void LabelModel::rotateSelectionRight()
	{
		rotateSelection( 90.0 );
	}


	void LabelModel::flipSelectionHoriz()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->flipHoriz();
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::flipSelectionVert()
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->flipVert();
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionLeft()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find left-most edge. */
		double x1_min = 7200; /* Start with a very large value: 7200pts = 100in */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			if ( r.x1() < x1_min ) x1_min = r.x1();
		}

		/* Now adjust the object positions to line up the left edges at left-most edge. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dx = x1_min - r.x1();
			item->setPositionRelative( dx, 0 );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionRight()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find right-most edge. */
		double x1_max = -7200; /* Start with a very large negative value: 7200pts = 100in */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			if ( r.x1() > x1_max ) x1_max = r.x1();
		}

		/* Now adjust the object positions to line up the right edges at right-most edge. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dx = x1_max - r.x1();
			item->setPositionRelative( dx, 0 );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionHCenter()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find average center of objects. */
		double xsum = 0;
		int n = 0;
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			xsum += (r.x1() + r.x2()) / 2.0;
			n++;
		}
		double xavg = xsum / n;

		/* Find item closest to average center of objects. */
		double xcenter = 7200; /* Start with very large value. */
		double dxmin = fabs( xavg - xcenter );
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dx = fabs( xavg - (r.x1() + r.x2())/2.0 );
			if ( dx < dxmin )
			{
				dxmin = dx;
				xcenter = (r.x1() + r.x2()) / 2.0;
			}
		}

		/* Now adjust the object positions to line up with the center of this item. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dx = xcenter - (r.x1() + r.x2())/2.0;
			item->setPositionRelative( dx, 0 );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionTop()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find top-most edge. */
		double y1_min = 7200; /* Start with a very large value: 7200pts = 100in */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			if ( r.y1() < y1_min ) y1_min = r.y1();
		}

		/* Now adjust the object positions to line up the top edges at top-most edge. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dy = y1_min - r.y1();
			item->setPositionRelative( 0, dy );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionBottom()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find bottom-most edge. */
		double y1_max = -7200; /* Start with a very large negative value: 7200pts = 100in */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			if ( r.y1() > y1_max ) y1_max = r.y1();
		}

		/* Now adjust the object positions to line up the bottom edges at bottom-most edge. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dy = y1_max - r.y1();
			item->setPositionRelative( 0, dy );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::alignSelectionVCenter()
	{
		if ( isSelectionEmpty() || isSelectionAtomic() )
		{
			return;
		}

		QList<LabelModelItem*> selectedList = getSelection();

		/* Find average center of objects. */
		double ysum = 0;
		int n = 0;
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			ysum += (r.y1() + r.y2()) / 2.0;
			n++;
		}
		double yavg = ysum / n;

		/* Find item closest to average center of objects. */
		double ycenter = 7200; /* Start with very large value. */
		double dymin = fabs( yavg - ycenter );
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dy = fabs( yavg - (r.y1() + r.y2())/2.0 );
			if ( dy < dymin )
			{
				dymin = dy;
				ycenter = (r.y1() + r.y2()) / 2.0;
			}
		}

		/* Now adjust the object positions to line up with the center of this item. */
		foreach ( LabelModelItem *item, selectedList )
		{
			LabelRegion r = item->getExtent();
			double dy = ycenter - (r.y1() + r.y2())/2.0;
			item->setPositionRelative( 0, dy );
		}
		
		mModified = true;

		emit changed();
	}


	void LabelModel::centerSelectionHoriz()
	{
		double xLabelCenter = w() / 2.0;

		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				LabelRegion r = item->getExtent();
				double xItemCenter = (r.x1() + r.x2()) / 2.0;
				double dx = xLabelCenter - xItemCenter;
				item->setPositionRelative( dx, 0 );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::centerSelectionVert()
	{
		double yLabelCenter = h() / 2.0;

		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				LabelRegion r = item->getExtent();
				double yItemCenter = (r.y1() + r.y2()) / 2.0;
				double dy = yLabelCenter - yItemCenter;
				item->setPositionRelative( 0, dy );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::moveSelection( double dx, double dy )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setPositionRelative( dx, dy );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionFontFamily( const QString &fontFamily )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setFontFamily( fontFamily );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionFontSize( double fontSize )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setFontSize( fontSize );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionFontWeight( QFont::Weight fontWeight )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setFontWeight( fontWeight );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionFontItalicFlag( bool fontItalicFlag )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setFontItalicFlag( fontItalicFlag );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionTextHAlign( Qt::Alignment textHAlign )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setTextHAlign( textHAlign );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionTextVAlign( Qt::Alignment textVAlign )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setTextVAlign( textVAlign );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionTextLineSpacing( double textLineSpacing )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setTextLineSpacing( textLineSpacing );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionTextColorNode( ColorNode textColorNode )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setTextColorNode( textColorNode );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionLineWidth( double lineWidth )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setLineWidth( lineWidth );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionLineColorNode( ColorNode lineColorNode )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setLineColorNode( lineColorNode );
			}
		}

		mModified = true;

		emit changed();
	}


	void LabelModel::setSelectionFillColorNode( ColorNode fillColorNode )
	{
		foreach ( LabelModelItem *item, mItemList )
		{
			if ( item->isSelected() )
			{
				item->setFillColorNode( fillColorNode );
			}
		}

		mModified = true;

		emit changed();
	}

}

