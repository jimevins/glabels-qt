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

#if HAVE_ZINT

#include "Zint.h"

#include <QtDebug>
#include <zint.h>


namespace
{
	const double FONT_SCALE = 0.9;
	const int W_PTS_DEFAULT = 144;
	const int H_PTS_DEFAULT = 72;
}


namespace glabels
{
	namespace barcode
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
						double fsize = FONT_SCALE*zstring->fsize;
						addText( zstring->x, zstring->y+0.75*fsize, fsize, QString((char*)(zstring->text)).toStdString() );
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
		

			//////////////////////////////////////////////////////
			// AusRP Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* AusRP::create()
			{
				return new AusRP();
			}

		
			std::string AusRP::encode( const std::string& cookedData )
			{
				symbology = BARCODE_AUSREPLY;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// AusRT Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* AusRT::create()
			{
				return new AusRT();
			}

		
			std::string AusRT::encode( const std::string& cookedData )
			{
				symbology = BARCODE_AUSROUTE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// AusRD Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* AusRD::create()
			{
				return new AusRD();
			}

		
			std::string AusRD::encode( const std::string& cookedData )
			{
				symbology = BARCODE_AUSREDIRECT;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Aztec Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Aztec::create()
			{
				return new Aztec();
			}

		
			std::string Aztec::encode( const std::string& cookedData )
			{
				symbology = BARCODE_AZTEC;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Azrun Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Azrun::create()
			{
				return new Azrun();
			}

		
			std::string Azrun::encode( const std::string& cookedData )
			{
				symbology = BARCODE_AZRUNE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Cbr Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Cbr::create()
			{
				return new Cbr();
			}

		
			std::string Cbr::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODABAR;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code1 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code1::create()
			{
				return new Code1();
			}

		
			std::string Code1::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODEONE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code11 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code11::create()
			{
				return new Code11();
			}

		
			std::string Code11::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE11;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// C16k Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* C16k::create()
			{
				return new C16k();
			}

		
			std::string C16k::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE16K;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// C25m Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* C25m::create()
			{
				return new C25m();
			}

		
			std::string C25m::encode( const std::string& cookedData )
			{
				symbology = BARCODE_C25MATRIX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// C25i Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* C25i::create()
			{
				return new C25i();
			}

		
			std::string C25i::encode( const std::string& cookedData )
			{
				symbology = BARCODE_C25IATA;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// C25dl Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* C25dl::create()
			{
				return new C25dl();
			}

		
			std::string C25dl::encode( const std::string& cookedData )
			{
				symbology = BARCODE_C25LOGIC;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code32 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code32::create()
			{
				return new Code32();
			}

		
			std::string Code32::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE32;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code39 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code39::create()
			{
				return new Code39();
			}

		
			std::string Code39::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE39;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code39e Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code39e::create()
			{
				return new Code39e();
			}

		
			std::string Code39e::encode( const std::string& cookedData )
			{
				symbology = BARCODE_EXCODE39;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code49 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code49::create()
			{
				return new Code49();
			}

		
			std::string Code49::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE49;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code93 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code93::create()
			{
				return new Code93();
			}

		
			std::string Code93::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE93;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code128 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code128::create()
			{
				return new Code128();
			}

		
			std::string Code128::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE128;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Code128b Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Code128b::create()
			{
				return new Code128b();
			}

		
			std::string Code128b::encode( const std::string& cookedData )
			{
				symbology = BARCODE_CODE128B;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Daft Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Daft::create()
			{
				return new Daft();
			}

		
			std::string Daft::encode( const std::string& cookedData )
			{
				symbology = BARCODE_DAFT;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Dmtx Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Dmtx::create()
			{
				return new Dmtx();
			}

		
			std::string Dmtx::encode( const std::string& cookedData )
			{
				symbology = BARCODE_DATAMATRIX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Dpl Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Dpl::create()
			{
				return new Dpl();
			}

		
			std::string Dpl::encode( const std::string& cookedData )
			{
				symbology = BARCODE_DPLEIT;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Dpi Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Dpi::create()
			{
				return new Dpi();
			}

		
			std::string Dpi::encode( const std::string& cookedData )
			{
				symbology = BARCODE_DPIDENT;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Kix Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Kix::create()
			{
				return new Kix();
			}

		
			std::string Kix::encode( const std::string& cookedData )
			{
				symbology = BARCODE_KIX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Ean Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Ean::create()
			{
				return new Ean();
			}

		
			std::string Ean::encode( const std::string& cookedData )
			{
				symbology = BARCODE_EANX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibc128 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibc128::create()
			{
				return new Hibc128();
			}

		
			std::string Hibc128::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_128;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibc39 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibc39::create()
			{
				return new Hibc39();
			}

		
			std::string Hibc39::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_39;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibcdm Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibcdm::create()
			{
				return new Hibcdm();
			}

		
			std::string Hibcdm::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_DM;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibcqr Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibcqr::create()
			{
				return new Hibcqr();
			}

		
			std::string Hibcqr::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_QR;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibcpdf Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibcpdf::create()
			{
				return new Hibcpdf();
			}

		
			std::string Hibcpdf::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_PDF;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibcmpdf Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibcmpdf::create()
			{
				return new Hibcmpdf();
			}

		
			std::string Hibcmpdf::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_MICPDF;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Hibcaz Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Hibcaz::create()
			{
				return new Hibcaz();
			}

		
			std::string Hibcaz::encode( const std::string& cookedData )
			{
				symbology = BARCODE_HIBC_AZTEC;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// I25 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* I25::create()
			{
				return new I25();
			}

		
			std::string I25::encode( const std::string& cookedData )
			{
				symbology = BARCODE_C25INTER;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Isbn Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Isbn::create()
			{
				return new Isbn();
			}

		
			std::string Isbn::encode( const std::string& cookedData )
			{
				symbology = BARCODE_ISBNX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Itf14 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Itf14::create()
			{
				return new Itf14();
			}

		
			std::string Itf14::encode( const std::string& cookedData )
			{
				symbology = BARCODE_ITF14;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Gmtx Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Gmtx::create()
			{
				return new Gmtx();
			}

		
			std::string Gmtx::encode( const std::string& cookedData )
			{
				symbology = BARCODE_GRIDMATRIX;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Gs1128 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Gs1128::create()
			{
				return new Gs1128();
			}

		
			std::string Gs1128::encode( const std::string& cookedData )
			{
				symbology = BARCODE_EAN128;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Logm Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Logm::create()
			{
				return new Logm();
			}

		
			std::string Logm::encode( const std::string& cookedData )
			{
				symbology = BARCODE_LOGMARS;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rss14 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rss14::create()
			{
				return new Rss14();
			}

		
			std::string Rss14::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS14;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rssltd Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rssltd::create()
			{
				return new Rssltd();
			}

		
			std::string Rssltd::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS_LTD;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rssexp Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rssexp::create()
			{
				return new Rssexp();
			}

		
			std::string Rssexp::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS_EXP;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rsss Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rsss::create()
			{
				return new Rsss();
			}

		
			std::string Rsss::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS14STACK;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rssso Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rssso::create()
			{
				return new Rssso();
			}

		
			std::string Rssso::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS14STACK_OMNI;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rssse Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rssse::create()
			{
				return new Rssse();
			}

		
			std::string Rssse::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RSS_EXPSTACK;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pharma Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pharma::create()
			{
				return new Pharma();
			}

		
			std::string Pharma::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PHARMA;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pharma2 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pharma2::create()
			{
				return new Pharma2();
			}

		
			std::string Pharma2::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PHARMA_TWO;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pzn Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pzn::create()
			{
				return new Pzn();
			}

		
			std::string Pzn::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PZN;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Tele Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Tele::create()
			{
				return new Tele();
			}

		
			std::string Tele::encode( const std::string& cookedData )
			{
				symbology = BARCODE_TELEPEN;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Telex Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Telex::create()
			{
				return new Telex();
			}

		
			std::string Telex::encode( const std::string& cookedData )
			{
				symbology = BARCODE_TELEPEN_NUM;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Japan Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Japan::create()
			{
				return new Japan();
			}

		
			std::string Japan::encode( const std::string& cookedData )
			{
				symbology = BARCODE_JAPANPOST;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Korea Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Korea::create()
			{
				return new Korea();
			}

		
			std::string Korea::encode( const std::string& cookedData )
			{
				symbology = BARCODE_KOREAPOST;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Maxi Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Maxi::create()
			{
				return new Maxi();
			}

		
			std::string Maxi::encode( const std::string& cookedData )
			{
				symbology = BARCODE_MAXICODE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Mpdf Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Mpdf::create()
			{
				return new Mpdf();
			}

		
			std::string Mpdf::encode( const std::string& cookedData )
			{
				symbology = BARCODE_MICROPDF417;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Msi Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Msi::create()
			{
				return new Msi();
			}

		
			std::string Msi::encode( const std::string& cookedData )
			{
				symbology = BARCODE_MSI_PLESSEY;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Mqr Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Mqr::create()
			{
				return new Mqr();
			}

		
			std::string Mqr::encode( const std::string& cookedData )
			{
				symbology = BARCODE_MICROQR;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Nve Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Nve::create()
			{
				return new Nve();
			}

		
			std::string Nve::encode( const std::string& cookedData )
			{
				symbology = BARCODE_NVE18;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Plan Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Plan::create()
			{
				return new Plan();
			}

		
			std::string Plan::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PLANET;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Postnet Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Postnet::create()
			{
				return new Postnet();
			}

		
			std::string Postnet::encode( const std::string& cookedData )
			{
				symbology = BARCODE_POSTNET;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pdf Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pdf::create()
			{
				return new Pdf();
			}

		
			std::string Pdf::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PDF417;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pdft Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pdft::create()
			{
				return new Pdft();
			}

		
			std::string Pdft::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PDF417TRUNC;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Qr Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Qr::create()
			{
				return new Qr();
			}

		
			std::string Qr::encode( const std::string& cookedData )
			{
				symbology = BARCODE_QRCODE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Rm4 Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Rm4::create()
			{
				return new Rm4();
			}

		
			std::string Rm4::encode( const std::string& cookedData )
			{
				symbology = BARCODE_RM4SCC;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// UpcA Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* UpcA::create()
			{
				return new UpcA();
			}

		
			std::string UpcA::encode( const std::string& cookedData )
			{
				symbology = BARCODE_UPCA;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// UpcE Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* UpcE::create()
			{
				return new UpcE();
			}

		
			std::string UpcE::encode( const std::string& cookedData )
			{
				symbology = BARCODE_UPCE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Usps Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Usps::create()
			{
				return new Usps();
			}

		
			std::string Usps::encode( const std::string& cookedData )
			{
				symbology = BARCODE_ONECODE;
				return ""; // Actual encoding is done in vectorize
			}
		

			//////////////////////////////////////////////////////
			// Pls Barcode
			//////////////////////////////////////////////////////
			glbarcode::Barcode* Pls::create()
			{
				return new Pls();
			}

		
			std::string Pls::encode( const std::string& cookedData )
			{
				symbology = BARCODE_PLESSEY;
				return ""; // Actual encoding is done in vectorize
			}
		

		}
	}
}


#endif // HAVE_ZINT
