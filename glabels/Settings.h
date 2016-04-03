/*  Settings.h
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#ifndef Settings_h
#define Settings_h


#include <QSettings>
#include "libglabels/Distance.h"
#include <QStringList>


///
/// Settings Singleton Class
///
class Settings : public QSettings
{
	Q_OBJECT
	
public:
	enum class PageSizeFamilty { ISO, US, };


	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
private:
	Settings();

public:
	static void init();
	static Settings* instance();

	
	/////////////////////////////////
	// Signals
	/////////////////////////////////
signals:
	void changed();
	

	/////////////////////////////////
	// Accessors
	/////////////////////////////////
public:
	static glabels::Distance::Units units();
	static void setUnits( glabels::Distance::Units units );

	static bool searchIsoPaperSizes();
	static void setSearchIsoPaperSizes( bool searchIsoPaperSizes );

	static bool searchUsPaperSizes();
	static void setSearchUsPaperSizes( bool searchUsPaperSizes );

	static bool searchOtherPaperSizes();
	static void setSearchOtherPaperSizes( bool searchOtherPaperSizes );

	static bool searchAllCategories();
	static void setSearchAllCategories( bool searchAllCategories );

	static QStringList searchCategoryList();
	static void setSearchCategoryList( const QStringList& searchCategoryList );


private:
	static Settings* mInstance;

};


#endif // Settings_h
