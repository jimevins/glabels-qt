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


	void LabelModel::itemChanged( LabelModelItem *item )
	{
		mModified = true;

		emit changed();
	}


	void LabelModel::itemMoved( LabelModelItem *item )
	{
		mModified = true;

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

}

