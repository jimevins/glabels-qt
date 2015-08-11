/*  Units.h
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

#ifndef libglabels_Units_h
#define libglabels_Units_h


#include <QCoreApplication>
#include <QString>


namespace libglabels
{


	class Units
	{
		Q_DECLARE_TR_FUNCTIONS(Units)


	private:
		Units( const QString &id, const QString &name, double pointsPerUnit );

	public:
		QString id() const;
		QString name() const;

		double pointsPerUnit() const;
		double unitsPerPoint() const;

		static Units *fromId( const QString &id );

		static Units *point();

		static Units *inch();

		static Units *mm();

		static Units *cm();

		static Units *pica();

		static bool isIdValid( QString id );


	private:
		QString mId;
		QString mName;
		double  mPointsPerUnit;
		double  mUnitsPerPoint;

	};

}


#include "Units.inl"


#endif // libglabels_Units_h
