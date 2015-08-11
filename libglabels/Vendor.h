/*  Vendor.h
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

#ifndef libglabels_Vendor_h
#define libglabels_Vendor_h


#include <QString>


namespace libglabels
{

	class Vendor
	{
	public:
		Vendor( const QString &name, const QString &url );

		const QString& name() const;
		const QString& url() const;

	private:
		QString mName;
		QString mUrl;
	};

}


#include "Vendor.inl"


#endif // libglabels_Vendor_h
