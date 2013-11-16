/*  Db.h
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

#ifndef libglabels_Db_h
#define libglabels_Db_h


#include <QCoreApplication>
#include <QString>
#include <QDir>
#include <QList>

#include "Paper.h"
#include "Category.h"
#include "Vendor.h"
#include "Template.h"


namespace libglabels
{

	class Db
	{
		Q_DECLARE_TR_FUNCTIONS(Db)

	private:
		Db();

	public:
		static void init() { instance(); }
		static Db *instance() { static Db *db = new Db(); return db; }


		static const QList<Paper*>    &papers() { return mPapers; }
		static const QStringList      &paperIds() { return mPaperIds; }
		static const QStringList      &paperNames() { return mPaperNames; }

		static const QList<Category*> &categories() { return mCategories; }
		static const QStringList      &categoryIds() { return mCategoryIds; }
		static const QStringList      &categoryNames() { return mCategoryNames; }

		static const QList<Vendor*>   &vendors() { return mVendors; }
		static const QStringList      &vendorNames() { return mVendorNames; }

		static const QList<Template*> &templates() { return mTemplates; }


		static void registerPaper( Paper *paper );
		static const Paper *lookupPaperFromName( const QString &name );
		static const Paper *lookupPaperFromId( const QString &id );
		static const QString &lookupPaperIdFromName( const QString &name );
		static const QString &lookupPaperNameFromId( const QString &id );
		static bool isPaperIdKnown( const QString &id );
		static bool isPaperIdOther( const QString &id );

		static void registerCategory( Category *category );
		static const Category *lookupCategoryFromName( const QString &name );
		static const Category *lookupCategoryFromId( const QString &id );
		static const QString &lookupCategoryIdFromName( const QString &name );
		static const QString &lookupCategoryNameFromId( const QString &id );
		static bool isCategoryIdKnown( const QString &id );

		static void registerVendor( Vendor *vendor );
		static const Vendor *lookupVendorFromName( const QString &name );
		static const QString &lookupVendorUrlFromName( const QString &name );
		static bool isVendorNameKnown( const QString &id );

		static void registerTemplate( Template *tmplate );
		static const Template *lookupTemplateFromName( const QString &name );
		static const Template *lookupTemplateFromBrandPart( const QString &brand, const QString &part );
		static bool isTemplateKnown( const QString &brand, const QString &part );
		static QStringList getNameListOfSimilarTemplates( const QString &name );

		static void registerUserTemplate( Template *tmplate );
		static void deleteUserTemplateByName( const QString &name );
		static void deleteUserTemplateByBrandPart( const QString &brand, const QString &part );

		static void printKnownPapers();
		static void printKnownCategories();
		static void printKnownVendors();
		static void printKnownTemplates();


	private:
		static QDir systemTemplatesDir();

		static void readPapers();
		static void readPapersFromDir( const QDir &dir );

		static void readCategories();
		static void readCategoriesFromDir( const QDir &dir );

		static void readVendors();
		static void readVendorsFromDir( const QDir &dir );

		static void readTemplates();
		static void readTemplatesFromDir( const QDir &dir );


	private:
		static QList<Paper*>    mPapers;
		static QStringList      mPaperIds;
		static QStringList      mPaperNames;

		static QList<Category*> mCategories;
		static QStringList      mCategoryIds;
		static QStringList      mCategoryNames;

		static QList<Vendor*>   mVendors;
		static QStringList      mVendorNames;

		static QList<Template*> mTemplates;

		static QString mEmpty;
	};

}

#endif // libglabels_Db_h
