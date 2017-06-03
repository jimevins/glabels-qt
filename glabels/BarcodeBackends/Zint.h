/*  Zint.h
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#ifndef barcode_Zint_h
#define barcode_Zint_h

#if HAVE_ZINT

#include "glbarcode/Barcode1dBase.h"


namespace glabels
{
	namespace Zint
	{

		/**
		 * Zint::Base base class for all Zint barcodes
		 *
		 * Implements glbarcode::Barcode1dBase.
		 */
		class Base : public glbarcode::Barcode1dBase
		{
		protected:
			int symbology;
			
			
			bool validate( const std::string& rawData ) override;

			void vectorize( const std::string& encodedData,
			                const std::string& displayText,
			                const std::string& cookedData,
			                double&            w,
			                double&            h ) override;
		};


		/**
		 * AusP Barcode
		 */
		class AusP : public Base
		{
		public:
			static Barcode* create();
			
		protected:
			std::string encode( const std::string& cookedData ) override;
		};


	}
}


#endif // HAVE_ZINT

#endif // barcode_Zint_h
