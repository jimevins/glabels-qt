/*  BarcodeBackends.h
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#ifndef BarcodeBackends_h
#define BarcodeBackends_h


#include "BarcodeStyle.h"

#include <QList>
#include <QMap>
#include <QObject>
#include <QString>


namespace glabels
{
	
	///
	/// Barcode Backends Database
	///
	class BarcodeBackends : public QObject
	{
		Q_OBJECT

	  
		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	private:
		BarcodeBackends();

	public:
		static void init();

		/////////////////////////////////
		// Public Methods
		/////////////////////////////////
	public:
		static QString BackendIdToName( const QString& backendId );
		static QString BackendNameToId( const QString& backendName );

		static const QList<QString>& getBackendNameList();
		static const QList<QString>& getNameList();

		static const BarcodeStyle* lookupStyleFromId( const QString& id );
		static const BarcodeStyle* lookupStyleFromName( const QString& name );


		/////////////////////////////////
		// Private Methods
		/////////////////////////////////
	private:
		static void registerBackend( QString &id, QString &name);

		static void registerStyle( const char*    id,
		                           const char*    backendId,
		                           const QString& name,
		                           bool           canText,
		                           bool           textOptional,
		                           bool           canChecksum,
		                           bool           checksumOptional,
		                           const char*    defaultDigits,
		                           bool           canFreeForm,
		                           int            preferedN );


		/////////////////////////////////
		// Private Members
		/////////////////////////////////
		typedef QMap<QString,QString> BackendMap;
		static BackendMap mBackendIdMap;
		static BackendMap mBackendNameMap;

		typedef QMap<QString,BarcodeStyle*> StyleMap;
		static StyleMap mStyleIdMap;
		static StyleMap mStyleNameMap;

		static QList<QString> mBackendNameList;
		static QList<QString> mNameList;

	};

}


#endif // BarcodeBackends_h
