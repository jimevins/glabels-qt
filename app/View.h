/*  View.h
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

#ifndef glabels_View_h
#define glabels_View_h

#include <QGraphicsView>
#include <QGraphicsScene>

#include "LabelModel.h"


namespace glabels
{

	class View : public QGraphicsView
	{
		Q_OBJECT

	public:
		View( QWidget *parent = 0 );


	signals:
		void zoomChanged();


	public:
		inline double zoom() const;

		void setModel( LabelModel* model );

		void zoomIn();
		void zoomOut();
		void zoom1To1();
		void zoomToFit();
		bool isZoomMax() const;
		bool isZoomMin() const;
	private:
		void setZoomReal( double zoom, bool zoomToFitFlag );


	private:
		QGraphicsScene*  mScene;

		double           mZoom;
		bool             mZoomToFitFlag;

		LabelModel*      mModel;

	};


	inline double View::zoom() const
	{
		return mZoom;
	}

}



#endif // glabels_View_h
