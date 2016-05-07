/*  MergeFactory.cpp
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

#include "MergeFactory.h"

#include "MergeNone.h"
#include "MergeTextCsv.h"


///
/// Static data
///
QMap<QString,MergeFactory::BackendEntry> MergeFactory::mBackendMap;


///
/// Constructor
///
MergeFactory::MergeFactory()
{
	registerBackend( "None",     &MergeNone::create );
	registerBackend( "Text/CSV", &MergeTextCsv::create );
}


///
/// Initialize
///
void MergeFactory::init()
{
	static MergeFactory* singletonInstance = 0;
	if ( !singletonInstance )
	{
		singletonInstance = new MergeFactory();
	}
}


///
/// Create Merge object
///
Merge* MergeFactory::createMerge( const QString& id )
{
	QMap<QString,BackendEntry>::iterator iBackend = mBackendMap.find( id );
	if ( iBackend != mBackendMap.end() )
	{
		return iBackend->create();
	}
	
	return MergeNone::create();
}


///
/// Register backend
///
void MergeFactory::registerBackend( const QString& id, CreateFct create )
{
	BackendEntry backend;

	backend.id     = id;
	backend.create = create;
	
	mBackendMap[ id ] = backend;
}


