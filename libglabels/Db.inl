/*  Db.inl
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


namespace libglabels
{

	inline const QList<Paper*>& Db::papers()
	{
		return mPapers;
	}


	inline const QStringList& Db::paperIds()
	{
		return mPaperIds;
	}


	inline const QStringList& Db::paperNames()
	{
		return mPaperNames;
	}


	inline const QList<Category*>& Db::categories()
	{
		return mCategories;
	}


	inline const QStringList& Db::categoryIds()
	{
		return mCategoryIds;
	}


	inline const QStringList& Db::categoryNames()
	{
		return mCategoryNames;
	}


	inline const QList<Vendor*>& Db::vendors()
	{
		return mVendors;
	}


	inline const QStringList& Db::vendorNames()
	{
		return mVendorNames;
	}

	inline const QList<Template*>& Db::templates()
	{
		return mTemplates;
	}

}
