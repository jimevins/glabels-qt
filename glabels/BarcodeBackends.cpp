/*  BarcodeBackends.cpp
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

#include "BarcodeBackends.h"


namespace
{
	const std::string default_id = "code39";
}

BarcodeBackends::BackendMap BarcodeBackends::mBackendIdMap;
BarcodeBackends::BackendMap BarcodeBackends::mBackendNameMap;

BarcodeBackends::StyleMap BarcodeBackends::mStyleIdMap;
BarcodeBackends::StyleMap BarcodeBackends::mStyleNameMap;

QList<QString> BarcodeBackends::mBackendNameList;
QList<QString> BarcodeBackends::mNameList;


BarcodeBackends::BarcodeBackends()
{
	registerStyle( "postnet", "", tr("POSTNET (any)"),
		       false, false, true, false, "12345-6789-12", false, 11 );

	registerStyle( "postnet-5", "", tr("POSTNET-5 (ZIP only)"),
		       false, false, true, false, "12345", false, 5 );

	registerStyle( "postnet-9", "", tr("POSTNET-9 (ZIP+4)"),
		       false, false, true, false, "12345-6789", false, 9 );

	registerStyle( "postnet-11", "", tr("POSTNET-11 (DPBC)"),
		       false, false, true, false, "12345-6789-12", false, 11 );

	registerStyle( "cepnet", "", tr("CEPNET"),
		       false, false, true, false, "12345-678", false, 8 );

	registerStyle( "onecode", "", tr("USPS Intelligent Mail"),
		       false, false, true, false, "12345678901234567890", false, 20 );

	registerStyle( "code39", "", tr("Code 39"),
		       true, true, true, true, "1234567890", true, 10 );

	registerStyle( "code39ext", "", tr("Code 39 Extended"),
		       true, true, true, true, "1234567890", true, 10 );

	registerStyle( "upc-A", "", tr("UPC-A"),
		       true, false, true, false, "12345678901", false, 11 );

	registerStyle( "ean-13", "", tr("EAN-13"),
		       true, false, true, false, "123456789012", false, 12 );

	registerStyle( "datamatrix", "", tr("DataMatrix"),
		       false, false, true, false, "1234567890AB", false, 12 );

	registerStyle( "qrcode", "", tr("QRCode"),
		       false, false, true, false, "1234567890AB", false, 12 );
}


void BarcodeBackends::init( void )
{
	static BarcodeBackends* singletonInstance = NULL;
                
	if ( singletonInstance == NULL )
	{
		singletonInstance = new BarcodeBackends();
	}
}


QString BarcodeBackends::BackendIdToName( const QString& backendId )
{
	BackendMap::iterator i = mBackendIdMap.find( backendId );
	if ( i != mBackendIdMap.end()  )
	{
		return i.value();
	}
		
	return "";
}


QString BarcodeBackends::BackendNameToId( const QString& backendName )
{
	BackendMap::iterator i = mBackendNameMap.find( backendName );
	if ( i != mBackendNameMap.end()  )
	{
		return i.value();
	}
		
	return "";
}


const QList<QString>& BarcodeBackends::getBackendNameList()
{
	return mBackendNameList;
}


const QList<QString>& BarcodeBackends::getNameList()
{
	return mNameList;
}


const BarcodeStyle* BarcodeBackends::lookupStyleFromId( const QString& id )
{
	StyleMap::iterator i = mStyleIdMap.find( id );
	if ( i != mStyleIdMap.end()  )
	{
		return i.value();
	}
		
	return 0;
}


const BarcodeStyle* BarcodeBackends::lookupStyleFromName( const QString& name )
{
	StyleMap::iterator i = mStyleNameMap.find( name );
	if ( i != mStyleNameMap.end()  )
	{
		return i.value();
	}
		
	return 0;
}


void BarcodeBackends::registerBackend( QString& id, QString& name)
{
	mBackendNameList.append( name );
	mBackendIdMap.insert( id, name );
	mBackendNameMap.insert( name, id );
}


void BarcodeBackends::registerStyle( const char*    id,
				     const char*    backendId,
				     const QString& name,
				     bool           canText,
				     bool           textOptional,
				     bool           canChecksum,
				     bool           checksumOptional,
				     const char*    defaultDigits,
				     bool           canFreeForm,
				     int            preferedN )
{
	BarcodeStyle* style = new BarcodeStyle( QString(id), QString(backendId), name,
						canText, textOptional,
						canChecksum, checksumOptional,
						QString(defaultDigits), canFreeForm, preferedN );

	QString fqName = QString(backendId) + QString(".") + name; // Name may not be unique

	mNameList.append( name );
	mStyleIdMap.insert( id, style );
	mStyleNameMap.insert( fqName, style );
}
