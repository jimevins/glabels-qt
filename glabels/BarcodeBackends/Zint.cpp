/*  Zint.cpp
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

#if HAVE_GNU_BARCODE

#include "Zint.h"

#include <QtDebug>
#include <zint.h>


namespace
{
	const int W_PTS_DEFAULT = 144;
	const int H_PTS_DEFAULT = 72;
}


namespace glabels
{
	namespace Zint
	{


		//
		// Zint barcode data validation method
		//
		bool Base::validate( const std::string& rawData )
		{
			return rawData.size() != 0;
		}

		
		//
		// Zint barcode data vectorization method
		//
		void Base::vectorize( const std::string& encodedData,
		                      const std::string& displayText,
		                      const std::string& cookedData,
		                      double&            w,
		                      double&            h )
		{
			/*
			 * First encode using Zint barcode library.
			 */
			if ( w == 0 )
			{
				w = W_PTS_DEFAULT;
			}
			if ( h == 0 )
			{
				h = H_PTS_DEFAULT;
			}

			zint_symbol* symbol = ZBarcode_Create();;

			symbol->symbology = symbology;

			if ( ZBarcode_Encode( symbol, (unsigned char*)(cookedData.c_str()), 0 ) != 0 )
			{
				qDebug() << "Zint::ZBarcode_Encode: " << QString(symbol->errtxt);
				setIsDataValid( false );
				return;
			}

			symbol->show_hrt = showText();

			if ( ZBarcode_Render( symbol, (float)w, (float)h ) == 0 )
			{
				qDebug() << "Zint::ZBarcode_Render: " << QString(symbol->errtxt);
				setIsDataValid( false );
				return;
			}


			/*
			 * Now do the actual vectorization.
			 */
			zint_render *render = symbol->rendered;

			setWidth( render->width );
			setHeight( render->height );

			for ( zint_render_line *zline = render->lines; zline != nullptr; zline = zline->next )
			{
				addBox( zline->x, zline->y, zline->width, zline->length );
			}

			for ( zint_render_ring *zring = render->rings; zring != nullptr; zring = zring->next )
			{
				addRing( zring->x, zring->y, zring->radius, zring->line_width );
			}

			for ( zint_render_hexagon *zhexagon = render->hexagons; zhexagon != nullptr; zhexagon = zhexagon->next )
			{
				addHexagon( zhexagon->x, zhexagon->y, 2.89 );
			}

			if( showText() )
			{
				for ( zint_render_string *zstring = render->strings; zstring != nullptr; zstring = zstring->next )
				{
					addText( zstring->x, zstring->y, zstring->fsize, QString((char*)(zstring->text)).toStdString() );
				}
			}

			ZBarcode_Delete( symbol );
		}


		//////////////////////////////////////////////////////
		// AusP Barcode
		//////////////////////////////////////////////////////
		glbarcode::Barcode* AusP::create()
		{
			return new AusP();
		}

		
		std::string AusP::encode( const std::string& cookedData )
		{
			symbology = BARCODE_AUSPOST;
			return ""; // Actual encoding is done in vectorize
		}
		

	}
}

#endif // HAVE_GNU_BARCODE
