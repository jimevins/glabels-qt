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

#include <list>
#include <vector>

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
		Frame( QString id = "0" ) : mId(id)
		{
		}

	public:
		inline const QString &id() const { return mId; }

		virtual void getSize( double *w, double *h ) const = 0;
		virtual bool isSimilar( Frame *b ) const = 0;
		virtual QString &getSizeDescription( Units *units ) const = 0;

		int nLabels() const;
		QString &getLayoutDescription() const;
		std::vector<Point> getOrigins() const;

		void addLayout( Layout *layout );
		void addMarkup( Markup *markup );

	private:
		QString mId;

		std::list<Layout*> mLayouts;
		std::list<Markup*> mMarkups;
	};

}

#endif // libglabels_Frame_h
