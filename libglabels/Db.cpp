/*  Db.cpp
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

#include "Db.h"

#include <iostream>


namespace libglabels
{

	std::list<Paper *>    mPapers;
	std::list<QString>    mPaperIds;
	std::list<QString>    mPaperNames;
	std::list<Category *> mCategories;
	std::list<QString>    mCategoryIds;
	std::list<QString>    mCategoryNames;
	std::list<Vendor *>   mVendors;
	std::list<QString>    mVendorNames;
	std::list<Template *> mTemplates;

	Db::Db()
	{
	}


	void Db::registerPaper( Paper *paper )
	{
		if ( lookupPaperFromId( paper->id() ) == NULL )
		{
			mPapers.push_back( paper );
			mPaperIds.push_back( paper->id() );
			mPaperNames.push_back( paper->name() );
		}
		else
		{
			qDebug( "Duplicate paper ID: \"%s\".", paper->id().toStdString().c_str() );
		}
	}


	const Paper *Db::lookupPaperFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL paper name." );
			return mPapers.front();
		}

		std::list<Paper*>::const_iterator it;
		for ( it = mPapers.begin(); it != mPapers.end(); it++ )
		{
			if ( (*it)->name() == name )
			{
				return *it;
			}
		}

		qDebug( "Unknown paper name: \"%s\".", name.toStdString().c_str() );
		return NULL;
	}


	const Paper *Db::lookupPaperFromId( const QString &id )
	{
		if ( id.isNull() || id.isEmpty() )
		{
			qDebug( "NULL paper ID." );
			return mPapers.front();
		}

		std::list<Paper*>::const_iterator it;
		for ( it = mPapers.begin(); it != mPapers.end(); it++ )
		{
			if ( (*it)->id() == id )
			{
				return *it;
			}
		}

		qDebug( "Unknown paper ID: \"%s\".", id.toStdString().c_str() );
		return NULL;
	}


	const QString &Db::lookupPaperIdFromName( const QString &name )
	{
		if ( !name.isNull() && !name.isEmpty() )
		{
			const Paper *paper = lookupPaperFromName( name );
			if ( paper != NULL )
			{
				return paper->id();
			}
		}

		qDebug( "Unknown paper name: \"%s\".", name.toStdString().c_str() );
		return mEmpty;
	}


	const QString &Db::lookupPaperNameFromId( const QString &id )
	{
		if ( !id.isNull() && !id.isEmpty() )
		{
			const Paper *paper = lookupPaperFromId( id );
			if ( paper != NULL )
			{
				return paper->name();
			}
		}

		qDebug( "Unknown paper id: \"%s\".", id.toStdString().c_str() );
		return mEmpty;
	}


	bool Db::isPaperIdKnown( const QString &id )
	{
		if ( !id.isNull() && !id.isEmpty() )
		{
			const Paper *paper = lookupPaperFromId( id );
			if ( paper != NULL )
			{
				return true;
			}
		}

		return false;
	}


	bool Db::isPaperIdOther( const QString &id )
	{
		return ( id == "Other" );
	}


	void Db::registerCategory( Category *category )
	{
		if ( lookupCategoryFromId( category->id() ) == NULL )
		{
			mCategories.push_back( category );
			mCategoryIds.push_back( category->id() );
			mCategoryNames.push_back( category->name() );
		}
		else
		{
			qDebug( "Duplicate category ID: \"%s\".", category->id().toStdString().c_str() );
		}
	}


	const Category *Db::lookupCategoryFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL category name." );
			return mCategories.front();
		}

		std::list<Category*>::const_iterator it;
		for ( it = mCategories.begin(); it != mCategories.end(); it++ )
		{
			if ( (*it)->name() == name )
			{
				return *it;
			}
		}

		qDebug( "Unknown category name: \"%s\".", name.toStdString().c_str() );
		return NULL;
	}


	const Category *Db::lookupCategoryFromId( const QString &id )
	{
		if ( id.isNull() || id.isEmpty() )
		{
			qDebug( "NULL category ID." );
			return mCategories.front();
		}

		std::list<Category*>::const_iterator it;
		for ( it = mCategories.begin(); it != mCategories.end(); it++ )
		{
			if ( (*it)->id() == id )
			{
				return *it;
			}
		}

		qDebug( "Unknown category ID: \"%s\".", id.toStdString().c_str() );
		return NULL;
	}


	const QString &Db::lookupCategoryIdFromName( const QString &name )
	{
		if ( !name.isNull() && !name.isEmpty() )
		{
			const Category *category = lookupCategoryFromName( name );
			if ( category != NULL )
			{
				return category->id();
			}
		}

		qDebug( "Unknown category name: \"%s\".", name.toStdString().c_str() );
		return mEmpty;
	}


	const QString &Db::lookupCategoryNameFromId( const QString &id )
	{
		if ( !id.isNull() && !id.isEmpty() )
		{
			const Category *category = lookupCategoryFromId( id );
			if ( category != NULL )
			{
				return category->name();
			}
		}

		qDebug( "Unknown category id: \"%s\".", id.toStdString().c_str() );
		return mEmpty;
	}


	bool Db::isCategoryIdKnown( const QString &id )
	{
		if ( !id.isNull() && !id.isEmpty() )
		{
			const Category *category = lookupCategoryFromId( id );
			if ( category != NULL )
			{
				return true;
			}
		}

		return false;
	}


	void Db::registerVendor( Vendor *vendor )
	{
		if ( lookupVendorFromName( vendor->name() ) == NULL )
		{
			mVendors.push_back( vendor );
			mVendorNames.push_back( vendor->name() );
		}
		else
		{
			qDebug( "Duplicate vendor name: \"%s\".", vendor->name().toStdString().c_str() );
		}
	}


	const Vendor *Db::lookupVendorFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL vendor name." );
			return mVendors.front();
		}

		std::list<Vendor*>::const_iterator it;
		for ( it = mVendors.begin(); it != mVendors.end(); it++ )
		{
			if ( (*it)->name() == name )
			{
				return *it;
			}
		}

		qDebug( "Unknown vendor name: \"%s\".", name.toStdString().c_str() );
		return NULL;
	}


	const QString &Db::lookupVendorUrlFromName( const QString &name )
	{
		if ( !name.isNull() && !name.isEmpty() )
		{
			const Vendor *vendor = lookupVendorFromName( name );
			if ( vendor != NULL )
			{
				return vendor->url();
			}
		}

		qDebug( "Unknown vendor name: \"%s\".", name.toStdString().c_str() );
		return mEmpty;
	}


	bool Db::isVendorNameKnown( const QString &name )
	{
		if ( !name.isNull() && !name.isEmpty() )
		{
			const Vendor *vendor = lookupVendorFromName( name );
			if ( vendor != NULL )
			{
				return true;
			}
		}

		return false;
	}


	void Db::registerTemplate( Template *tmplate )
	{
		if ( lookupTemplateFromName( tmplate->name() ) == NULL )
		{
			mTemplates.push_back( tmplate );
		}
		else
		{
			qDebug( "Duplicate template name: \"%s\".", tmplate->name().toStdString().c_str() );
		}
	}


	const Template *Db::lookupTemplateFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL template name." );
			return mTemplates.front();
		}

		std::list<Template*>::const_iterator it;
		for ( it = mTemplates.begin(); it != mTemplates.end(); it++ )
		{
			if ( (*it)->name() == name )
			{
				return *it;
			}
		}

		qDebug( "Unknown template name: \"%s\".", name.toStdString().c_str() );
		return NULL;
	}


	const Template *Db::lookupTemplateFromBrandPart( const QString &brand, const QString &part )
	{
		if ( brand.isNull() || brand.isEmpty() || part.isNull() || part.isEmpty() )
		{
			qDebug( "NULL template brand and/or part." );
			return mTemplates.front();
		}

		std::list<Template*>::const_iterator it;
		for ( it = mTemplates.begin(); it != mTemplates.end(); it++ )
		{
			if ( ((*it)->brand() == brand) && ((*it)->part() == part) )
			{
				return *it;
			}
		}

		qDebug( "Unknown template brand, part: \"%s\", \"%s\".",
			brand.toStdString().c_str(),
			part.toStdString().c_str() );
		return NULL;
	}


	bool Db::isTemplateKnown( const QString &brand, const QString &part )
	{
		if ( !brand.isNull() && !brand.isEmpty() && !part.isNull() && part.isEmpty() )
		{
			const Template *tmplate = lookupTemplateFromBrandPart( brand, part );
			if ( tmplate != NULL )
			{
				return true;
			}
		}

		return false;
	}


	void Db::registerUserTemplate( Template *templat )
	{
		// TODO
	}


	void Db::deleteUserTemplateByName( const QString &name )
	{
		// TODO
	}


	void Db::deleteUserTemplateByBrandPart( const QString &brand, const QString &part )
	{
		// TODO
	}


	void Db::printKnownPapers()
	{
		std::cout << "KNOWN PAPERS:" << std::endl;

		std::list<Paper*>::const_iterator it;
		for ( it = mPapers.begin(); it != mPapers.end(); it++ )
		{
			Paper *paper = *it;

			std::cout << "paper " <<
				"id='"    << paper->id().toStdString()   << "', " <<
				"name='"  << paper->name().toStdString() << "', " <<
				"width="  << paper->width()              << "pts, " <<
				"height=" << paper->height()             << "pts" <<
				std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownCategories()
	{
		std::cout << "KNOWN CATEGORIES:" << std::endl;

		std::list<Category*>::const_iterator it;
		for ( it = mCategories.begin(); it != mCategories.end(); it++ )
		{
			Category *category = *it;

			std::cout << "category " <<
				"id='"    << category->id().toStdString()   << "', " <<
				"name='"  << category->name().toStdString() << "', " <<
				std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownVendors()
	{
		std::cout << "KNOWN VENDORS:" << std::endl;

		std::list<Vendor*>::const_iterator it;
		for ( it = mVendors.begin(); it != mVendors.end(); it++ )
		{
			Vendor *vendor = *it;

			std::cout << "vendor " <<
				"name='" << vendor->name().toStdString() << "', " <<
				"url='"  << vendor->url().toStdString()  << "'" <<
				std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownTemplates()
	{
		std::cout << "KNOWN TEMPLATES:" << std::endl;

		std::list<Template*>::const_iterator it;
		for ( it = mTemplates.begin(); it != mTemplates.end(); it++ )
		{
			Template *tmplate = *it;

			std::cout << "template " <<
				"brand='"       << tmplate->brand().toStdString()       << "', " <<
				"part='"        << tmplate->part().toStdString()        << "', " <<
				"description='" << tmplate->description().toStdString() << "'" <<
				std::endl;
		}

		std::cout << std::endl;
	}


	void Db::read_papers()
	{
		// TODO
	}


	void Db::read_papers_from_dir( const QString &dirName )
	{
		// TODO
	}


	void Db::read_categories()
	{
		// TODO
	}


	void Db::read_categories_from_dir( const QString &dirName )
	{
		// TODO
	}


	void Db::read_vendors()
	{
		// TODO
	}


	void Db::read_vendors_from_dir( const QString &dirName )
	{
		// TODO
	}


	void Db::read_templates()
	{
		// TODO
	}


	void Db::read_templates_from_dir( const QString &dirName )
	{
		// TODO
	}


}
