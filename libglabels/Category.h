/*  Category.h
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

#ifndef libglabels_Category_h
#define libglabels_Category_h


#include <QString>


namespace libglabels
{

	class Category
	{
	public:
		Category( const QString &id, const QString &name ) : mId(id), mName(name)
		{
		}

		inline const QString &id() const { return mId; }
		inline const QString &name() const { return mName; }

	private:
		QString mId;
		QString mName;
	};

}

#endif // libglabels_Category_h
