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

#include "Distance.h"
#include "Point.h"
#include "Layout.h"


namespace libglabels
{
	class Markup;  // Forward reference


	class Frame
	{
		Q_DECLARE_TR_FUNCTIONS(Frame)

	protected:
		Frame( const QString& id = "0" );
		Frame( const Frame& other );

	public:
		virtual Frame* dup() const = 0;

		const QString& id() const;
		int nLabels() const;
		const QString& layoutDescription() const;
		const QList<Layout*>& layouts() const;
		const QList<Markup*>& markups() const;

		QVector<Point> getOrigins() const;

		void addLayout( Layout* layout );
		void addMarkup( Markup* markup );

		virtual Distance w() const = 0;
		virtual Distance h() const = 0;

		virtual const QString sizeDescription( Distance::Units units ) const = 0;
		virtual bool isSimilarTo( Frame* other ) const = 0;

		virtual const QPainterPath& path() const = 0;
		virtual QPainterPath marginPath( const Distance& size ) const = 0;


	private:
		QString mId;
		int     mNLabels;
		QString mLayoutDescription;

		QList<Layout*> mLayouts;
		QList<Markup*> mMarkups;
	};

}


#include "Frame.inl"


#endif // libglabels_Frame_h
