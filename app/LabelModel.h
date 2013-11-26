/*  LabelModel.h
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

#ifndef glabels_LabelModel_h
#define glabels_LabelModel_h

#include <QObject>
#include <QList>

#include "libglabels/Template.h"
#include "LabelModelItem.h"


namespace glabels
{

	class LabelModel : public QObject
	{
		Q_OBJECT

	public:
		LabelModel();
		virtual ~LabelModel() {}

	signals:
		void changed();
		void sizeChanged();
		void selectionChanged();
		void itemAdded( LabelModelItem *item );
		void itemDeleted( LabelModelItem *item );
		void itemToTop( LabelModelItem *item );
		void itemToBottom( LabelModelItem *item );

	public:
		bool isModified( void ) const { return mModified; }

		const libglabels::Template *tmplate() const { return mTmplate; }
		void setTmplate( const libglabels::Template *tmplate )
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

		bool rotate() const { return mRotate; }
		void setRotate( bool rotate )
		{
			if (mRotate != rotate)
			{
				mRotate = rotate;
				mModified = true;
				emit changed();
				emit sizeChanged();
			}
		}

		double w() const { return mRotate ? mFrame->h() : mFrame->w(); }
		double h() const { return mRotate ? mFrame->w() : mFrame->h(); }


		void addItem( LabelModelItem *item );

		void deleteItem( LabelModelItem *item );


		void selectItem( LabelModelItem *item );

		void unselectItem( LabelModelItem *item );

		void selectAll();

		void unselectAll();

		void selectRegion( const LabelRegion &region );

		bool isSelectionEmpty();

		bool isSelectionAtomic();


		QList<LabelModelItem *> getSelection();

		LabelModelItem *getFirstSelectedItem();


		bool canSelectionText();
		bool canSelectionFill();
		bool canSelectionLineColor();
		bool canSelectionLineWidth();


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
		void moveSelection( double dx, double dy );


	private slots:
		void itemChanged( LabelModelItem *item );
		void itemMoved( LabelModelItem *item );


	private:

		QList<LabelModelItem*> mItemList;

		bool                         mModified;
		const libglabels::Template  *mTmplate;
		const libglabels::Frame     *mFrame;
		bool                         mRotate;
	};

}

#endif // glabels_LabelModel_h
