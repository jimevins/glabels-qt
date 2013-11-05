/*  Frame.h
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

#ifndef libglabels_Frame_h
#define libglabels_Frame_h

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QPainterPath>
#include <QVector>

#include "Units.h"
#include "Point.h"
#include "Layout.h"
#include "Markup.h"


namespace libglabels
{

	class Frame
	{
		Q_DECLARE_TR_FUNCTIONS(Frame)

	protected:
		Frame( const QString &id = "0" ) : mId(id), mNLabels(0), mLayoutDescription("")
		{
		}

		Frame( const Frame &other );

	public:
		virtual Frame *dup() const = 0;

		inline const QString &id() const { return mId; }
		inline int nLabels() const { return mNLabels; }
		inline const QString &layoutDescription() { return mLayoutDescription; }
		inline const QList<Layout*> &layouts() { return mLayouts; }
		inline const QList<Markup*> &markups() { return mMarkups; }

		QVector<Point> getOrigins() const;

		void addLayout( Layout *layout );
		void addMarkup( Markup *markup );

		virtual double w() const = 0;
		virtual double h() const = 0;

		virtual const QString &sizeDescription( Units *units ) = 0;
		virtual bool isSimilarTo( Frame *other ) const = 0;

		virtual const QPainterPath &path() const = 0;


	private:
		QString mId;
		int     mNLabels;
		QString mLayoutDescription;

		QList<Layout*> mLayouts;
		QList<Markup*> mMarkups;
	};

}

#endif // libglabels_Frame_h
