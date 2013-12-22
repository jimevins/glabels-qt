/*  BarcodeStyle.h
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

#ifndef glabels_BarcodeStyle_h
#define glabels_BarcodeStyle_h

#include <QString>
#include <algorithm>

namespace glabels
{

	class BarcodeStyle
	{

	public:
		BarcodeStyle ();

		BarcodeStyle ( const QString& id,
			       const QString& name,
			       bool           canText,
			       bool           textOptional,
			       bool           canChecksum,
			       bool           checksumOptional,
			       const QString& defaultDigits,
			       bool           canFreeform,
			       int            preferedN );


		const QString& id() const;

		const QString& name() const;

		bool canText() const;

		bool textOptional() const;

		bool canChecksum() const;

		bool checksumOptional() const;

		const QString& defaultDigits() const;

		bool canFreeform() const;

		int preferedN() const;


		QString exampleDigits( int n ) const;


	private:
		QString mId;
		QString mName;
		bool    mCanText;
		bool    mTextOptional;
		bool    mCanChecksum;
		bool    mChecksumOptional;
		QString mDefaultDigits;
		bool    mCanFreeform;
		int     mPreferedN;

	};


}

#endif // glabels_BarcodeStyle_h
