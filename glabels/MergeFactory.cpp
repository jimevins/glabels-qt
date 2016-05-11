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
QMap<QString,MergeFactory::BackendEntry> MergeFactory::mBackendIdMap;
QMap<QString,MergeFactory::BackendEntry> MergeFactory::mBackendNameMap;


///
/// Constructor
///
MergeFactory::MergeFactory()
{
	registerBackend( MergeNone::id(),
			 tr("None"),
			 NONE,
			 &MergeNone::create );
	
	registerBackend( MergeTextCsv::id(),
			 tr("Text: Comma Separated Values (CSV)"),
			 FILE,
			 &MergeTextCsv::create );
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
	QMap<QString,BackendEntry>::iterator iBackend = mBackendIdMap.find( id );
	if ( iBackend != mBackendIdMap.end() )
	{
		return iBackend->create();
	}
	
	return MergeNone::create();
}


///
/// Get name list
///
QStringList MergeFactory::nameList()
{
	QStringList list;
	
	foreach ( BackendEntry backend, mBackendIdMap )
	{
		list << backend.name;
	}

	return list;
}


///
/// Convert ID to name
///
QString MergeFactory::idToName( const QString& id )
{
	if ( mBackendIdMap.contains( id ) )
	{
		return mBackendIdMap[id].name;
	}
	else
	{
		return tr("None");
	}
}


///
/// Convert name to ID
///
QString MergeFactory::nameToId( const QString& name )
{
	if ( mBackendNameMap.contains( name ) )
	{
		return mBackendNameMap[name].id;
	}
	else
	{
		return "None";
	}
}


///
/// Convert ID to type
///
MergeFactory::SourceType MergeFactory::idToType( const QString& id )
{
	if ( mBackendIdMap.contains( id ) )
	{
		return mBackendIdMap[id].type;
	}
	else
	{
		return NONE;
	}
}


///
/// Register backend
///
void MergeFactory::registerBackend( const QString& id,
				    const QString& name,
				    SourceType     type,
				    CreateFct      create )
{
	BackendEntry backend;

	backend.name   = name;
	backend.type   = type;
	backend.create = create;
	
	mBackendIdMap[ id ] = backend;
}


