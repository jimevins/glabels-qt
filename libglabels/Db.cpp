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

#include <QApplication>
#include <iostream>

#include "Config.h"
#include "XmlPaperParser.h"
#include "XmlCategoryParser.h"
#include "XmlVendorParser.h"
#include "XmlTemplateParser.h"


namespace libglabels
{

	QList<Paper*>    Db::mPapers;
	QStringList      Db::mPaperIds;
	QStringList      Db::mPaperNames;
	QList<Category*> Db::mCategories;
	QStringList      Db::mCategoryIds;
	QStringList      Db::mCategoryNames;
	QList<Vendor*>   Db::mVendors;
	QStringList      Db::mVendorNames;
	QList<Template*> Db::mTemplates;

	QString Db::mEmpty = "";

	Db::Db()
	{
		readPapers();
		readCategories();
		readVendors();
		readTemplates();
	}


	void Db::registerPaper( Paper *paper )
	{
		if ( !isPaperIdKnown( paper->id() ) )
		{
			mPapers << paper;
			mPaperIds << paper->id();
			mPaperNames << paper->name();
		}
		else
		{
			qDebug( "Duplicate paper ID: \"%s\".", qPrintable(paper->id()) );
		}
	}


	const Paper *Db::lookupPaperFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL paper name." );
			return mPapers.first();
		}

		foreach ( Paper *paper, mPapers )
		{
			if ( paper->name() == name )
			{
				return paper;
			}
		}

		qDebug( "Unknown paper name: \"%s\".", qPrintable(name) );
		return NULL;
	}


	const Paper *Db::lookupPaperFromId( const QString &id )
	{
		if ( id.isNull() || id.isEmpty() )
		{
			qDebug( "NULL paper ID." );
			return mPapers.first();
		}

		foreach ( Paper *paper, mPapers )
		{
			if ( paper->id() == id )
			{
				return paper;
			}
		}

		qDebug( "Unknown paper ID: \"%s\".", qPrintable(id) );
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

		qDebug( "Unknown paper name: \"%s\".", qPrintable(name) );
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

		qDebug( "Unknown paper id: \"%s\".", qPrintable(id) );
		return mEmpty;
	}


	bool Db::isPaperIdKnown( const QString &id )
	{
		foreach ( Paper *paper, mPapers )
		{
			if ( paper->id() == id )
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
		if ( !isCategoryIdKnown( category->id() ) )
		{
			mCategories << category;
			mCategoryIds << category->id();
			mCategoryNames << category->name();
		}
		else
		{
			qDebug( "Duplicate category ID: \"%s\".", qPrintable(category->id()) );
		}
	}


	const Category *Db::lookupCategoryFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL category name." );
			return mCategories.first();
		}

		foreach ( Category *category, mCategories )
		{
			if ( category->name() == name )
			{
				return category;
			}
		}

		qDebug( "Unknown category name: \"%s\".", qPrintable(name) );
		return NULL;
	}


	const Category *Db::lookupCategoryFromId( const QString &id )
	{
		if ( id.isNull() || id.isEmpty() )
		{
			qDebug( "NULL category ID." );
			return mCategories.first();
		}

		foreach ( Category *category, mCategories )
		{
			if ( category->id() == id )
			{
				return category;
			}
		}

		qDebug( "Unknown category ID: \"%s\".", qPrintable(id) );
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

		qDebug( "Unknown category name: \"%s\".", qPrintable(name) );
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

		qDebug( "Unknown category id: \"%s\".", qPrintable(id) );
		return mEmpty;
	}


	bool Db::isCategoryIdKnown( const QString &id )
	{
		foreach ( Category *category, mCategories )
		{
			if ( category->id() == id )
			{
				return true;
			}
		}

		return false;
	}


	void Db::registerVendor( Vendor *vendor )
	{
		if ( !isVendorNameKnown( vendor->name() ) )
		{
			mVendors << vendor;
			mVendorNames << vendor->name();
		}
		else
		{
			qDebug( "Duplicate vendor name: \"%s\".", qPrintable(vendor->name()) );
		}
	}


	const Vendor *Db::lookupVendorFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL vendor name." );
			return mVendors.first();
		}

		foreach ( Vendor *vendor, mVendors )
		{
			if ( vendor->name() == name )
			{
				return vendor;
			}
		}

		qDebug( "Unknown vendor name: \"%s\".", qPrintable(name) );
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

		qDebug( "Unknown vendor name: \"%s\".", qPrintable(name) );
		return mEmpty;
	}


	bool Db::isVendorNameKnown( const QString &name )
	{
		foreach ( Vendor *vendor, mVendors )
		{
			if ( vendor->name() == name )
			{
				return true;
			}
		}

		return false;
	}


	void Db::registerTemplate( Template *tmplate )
	{
		if ( !isTemplateKnown( tmplate->brand(), tmplate->part() ) )
		{
			mTemplates << tmplate;
		}
		else
		{
			qDebug( "Duplicate template name: \"%s\".", qPrintable(tmplate->name()) );
		}
	}


	const Template *Db::lookupTemplateFromName( const QString &name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			qDebug( "NULL template name." );
			return mTemplates.first();
		}

		foreach ( Template *tmplate, mTemplates )
		{
			if ( tmplate->name() == name )
			{
				return tmplate;
			}
		}

		qDebug( "Unknown template name: \"%s\".", qPrintable(name) );
		return NULL;
	}


	const Template *Db::lookupTemplateFromBrandPart( const QString &brand, const QString &part )
	{
		if ( brand.isNull() || brand.isEmpty() || part.isNull() || part.isEmpty() )
		{
			qDebug( "NULL template brand and/or part." );
			return mTemplates.first();
		}

		foreach ( Template *tmplate, mTemplates )
		{
			if ( (tmplate->brand() == brand) && (tmplate->part() == part) )
			{
				return tmplate;
			}
		}

		qDebug( "Unknown template brand, part: \"%s\", \"%s\".", qPrintable(brand), qPrintable(part) );
		return NULL;
	}


	bool Db::isTemplateKnown( const QString &brand, const QString &part )
	{
		foreach ( Template *tmplate, mTemplates )
		{
			if ( (tmplate->brand() == brand) && (tmplate->part() == part) )
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

		foreach ( Paper *paper, mPapers )
		{
			std::cout << "paper "
				  << "id='"      << qPrintable(paper->id())      << "', "
				  << "name='"    << qPrintable(paper->name())    << "', "
				  << "width="    << paper->width()               << "pts, "
				  << "height="   << paper->height()              << "pts, "
				  << "pwg_size=" << qPrintable(paper->pwgSize())
				  << std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownCategories()
	{
		std::cout << "KNOWN CATEGORIES:" << std::endl;

		foreach ( Category *category, mCategories )
		{
			std::cout << "category "
				  << "id='"    << category->id().toStdString()   << "', "
				  << "name='"  << category->name().toStdString() << "', "
				  << std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownVendors()
	{
		std::cout << "KNOWN VENDORS:" << std::endl;

		foreach ( Vendor *vendor, mVendors )
		{
			std::cout << "vendor "
				  << "name='" << vendor->name().toStdString() << "', "
				  << "url='"  << vendor->url().toStdString()  << "'"
				  << std::endl;
		}

		std::cout << std::endl;
	}


	void Db::printKnownTemplates()
	{
		std::cout << "KNOWN TEMPLATES:" << std::endl;

		foreach ( Template *tmplate, mTemplates )
		{
			std::cout << "template "
				  << "brand='"       << tmplate->brand().toStdString()       << "', "
				  << "part='"        << tmplate->part().toStdString()        << "', "
				  << "description='" << tmplate->description().toStdString() << "'"
				  << std::endl;
		}

		std::cout << std::endl;
	}


	QDir Db::systemTemplatesDir()
	{
		QDir dir(QApplication::applicationDirPath());

		if ( dir.dirName() == "bin" )
		{
			dir.cdUp();
			dir.cd( "share" );
			dir.cd( "libglabels-3.0" ); // TODO: install qt version
		}
		else
		{
			// Working out of build directory
			dir.cd( Config::PROJECT_SOURCE_DIR );
		}

		dir.cd( "templates" );
		return dir;
	}


	void Db::readPapers()
	{
		readPapersFromDir( systemTemplatesDir() );
	}


	void Db::readPapersFromDir( const QDir &dir )
	{
		XmlPaperParser parser;

		foreach ( QString fileName, dir.entryList( QDir::Files ) )
		{
			if ( fileName == "paper-sizes.xml" )
			{
				parser.readFile( dir.absoluteFilePath( fileName ) );
			}
		}
	}


	void Db::readCategories()
	{
		readCategoriesFromDir( systemTemplatesDir() );
	}


	void Db::readCategoriesFromDir( const QDir &dir )
	{
		XmlCategoryParser parser;

		foreach ( QString fileName, dir.entryList( QDir::Files ) )
		{
			if ( fileName == "categories.xml" )
			{
				parser.readFile( dir.absoluteFilePath( fileName ) );
			}
		}
	}


	void Db::readVendors()
	{
		readVendorsFromDir( systemTemplatesDir() );
	}


	void Db::readVendorsFromDir( const QDir &dir )
	{
		XmlVendorParser parser;

		foreach ( QString fileName, dir.entryList( QDir::Files ) )
		{
			if ( fileName == "vendors.xml" )
			{
				parser.readFile( dir.absoluteFilePath( fileName ) );
			}
		}
	}


	void Db::readTemplates()
	{
		readTemplatesFromDir( systemTemplatesDir() );

		// TODO: Read user directories
	}


	void Db::readTemplatesFromDir( const QDir &dir )
	{
		QStringList filters;
		filters << "*-templates.xml" << "*.template";

		XmlTemplateParser parser;

		foreach ( QString fileName, dir.entryList( filters, QDir::Files ) )
		{
			parser.readFile( dir.absoluteFilePath( fileName ) );
		}
	}

}
