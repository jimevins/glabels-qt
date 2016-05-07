/*  MergeFactory.h
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

#ifndef MergeFactory_h
#define MergeFactory_h

#include "Merge.h"


///
/// MergeFactory
///
struct MergeFactory
{

	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
protected:
	MergeFactory();


	/////////////////////////////////
	// Static methods
	/////////////////////////////////
public:
	static void init();
	static Merge* createMerge( const QString& id );


	/////////////////////////////////
	// private methods
	/////////////////////////////////
private:
	typedef Merge* (*CreateFct)();
	
	static void registerBackend( const QString& id, CreateFct create );


	/////////////////////////////////
	// private data
	/////////////////////////////////
	class BackendEntry
	{
	public:
		QString   id;
		CreateFct create;
	};
	
	static QMap<QString,BackendEntry> mBackendMap;
		
};


#endif // MergeFactory_h
