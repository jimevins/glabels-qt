/*  FileUtil.h
 *
 *  Copyright (C) 2015  Jim Evins <evins@snaught.com>
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

#ifndef EnumUtil_h
#define EnumUtil_h


#include <QFont>
#include <QString>
#include <Qt>


namespace glabels
{

	namespace EnumUtil
	{

		QString weightToString( QFont::Weight weight );
		QFont::Weight stringToWeight( const QString& string );

		QString hAlignToString( Qt::Alignment align );
		Qt::Alignment stringToHAlign( const QString& string );

		QString vAlignToString( Qt::Alignment align );
		Qt::Alignment stringToVAlign( const QString& string );

	}

}


#endif // EnumUtil_h
