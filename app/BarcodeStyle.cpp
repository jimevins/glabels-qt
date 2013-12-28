/*  BarcodeStyle.cpp
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

#include "BarcodeStyle.h"


namespace glabels
{

	///
	/// Default Constructor
	///
	BarcodeStyle::BarcodeStyle ()
		: mId( "" ),
		  mName( "" ),
		  mCanText( false ),
		  mTextOptional( false ),
		  mCanChecksum( false ),
		  mChecksumOptional( false ),
		  mDefaultDigits( "" ),
		  mCanFreeform( false ),
		  mPreferedN( 0 )
	{
	}


	///
	/// Constructor From Data
	///
	BarcodeStyle::BarcodeStyle ( const QString& id,
				     const QString& name,
				     bool           canText,
				     bool           textOptional,
				     bool           canChecksum,
				     bool           checksumOptional,
				     const QString& defaultDigits,
				     bool           canFreeform,
				     int            preferedN )
		: mId( id ),
		  mName( name ),
		  mCanText( canText ),
		  mTextOptional( textOptional ),
		  mCanChecksum( canChecksum ),
		  mChecksumOptional( checksumOptional ),
		  mDefaultDigits( defaultDigits ),
		  mCanFreeform( canFreeform ),
		  mPreferedN( preferedN )
	{
	}


	///
	/// ID Property Getter
	///
	const QString& BarcodeStyle::id() const
	{
		return mId;
	}


	///
	/// Name Property Getter
	///
	const QString& BarcodeStyle::name() const
	{
		return mName;
	}


	///
	/// Can Text Property Getter
	///
	bool BarcodeStyle::canText() const
	{
		return mCanText;
	}


	///
	/// Text Optional Property Getter
	///
	bool BarcodeStyle::textOptional() const
	{
		return mTextOptional;
	}


	///
	/// Can Checksum Property Getter
	///
	bool BarcodeStyle::canChecksum() const
	{
		return mCanChecksum;
	}


	///
	/// Checksum Optional Property Getter
	///
	bool BarcodeStyle::checksumOptional() const
	{
		return mChecksumOptional;
	}


	///
	/// Default Digits Property Getter
	///
	const QString& BarcodeStyle::defaultDigits() const
	{
		return mDefaultDigits;
	}


	///
	/// Can Freeform Property Getter
	///
	bool BarcodeStyle::canFreeform() const
	{
		return mCanFreeform;
	}


	///
	/// Prefered N Property Getter
	///
	int BarcodeStyle::preferedN() const
	{
		return mPreferedN;
	}


	///
	/// Generate Example Digits
	///
	QString BarcodeStyle::exampleDigits( int n ) const
	{
		if ( mCanFreeform )
		{
			return QString( std::max( n, 1 ), QChar('0') );
		}
		else
		{
			return mDefaultDigits;
		}
	}

}

