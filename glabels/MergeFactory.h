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
#include <QCoreApplication>


///
/// MergeFactory
///
struct MergeFactory
{
	Q_DECLARE_TR_FUNCTIONS(MergeFactory)
	

	/////////////////////////////////
	// Source Type
	/////////////////////////////////
public:
	enum SourceType { NONE, FIXED, FILE };
		
		
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

	static QList<QString> nameList();
	static QString idToName( const QString& id );
	static QString nameToId( const QString& name );


	/////////////////////////////////
	// private methods
	/////////////////////////////////
private:
	typedef Merge* (*CreateFct)();
	
	static void registerBackend( const QString& id,
	                             const QString& name,
	                             SourceType     type,
	                             CreateFct      create );


	/////////////////////////////////
	// private data
	/////////////////////////////////
	class BackendEntry
	{
	public:
		QString    id;
		QString    name;
		SourceType type;
		CreateFct  create;
	};
	
	static QMap<QString,BackendEntry> mBackendIdMap;
	static QMap<QString,BackendEntry> mBackendNameMap;
		
};


#endif // MergeFactory_h
