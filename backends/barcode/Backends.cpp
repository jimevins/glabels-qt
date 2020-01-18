/*  Backends.cpp
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

#include "Backends.h"

#include "GnuBarcode.h"
#include "QrEncode.h"
#include "Zint.h"
#include "Zint_2_6.h"

#include "glbarcode/Factory.h"


namespace glabels
{
	namespace barcode
	{
	
		//
		// Static data
		//
		QStringList Backends::mBackendIdList;
		QMap<QString,QString> Backends::mBackendNameMap;

		QList<Style> Backends::mStyleList;
	

		Backends::Backends()
		{
			registerStyle( "code39", "", tr("Code 39"),
			               true, true, true, true, "1234567890", true, 10 );

			registerStyle( "code39ext", "", tr("Code 39 Extended"),
			               true, true, true, true, "1234567890", true, 10 );

			registerStyle( "upc-a", "", tr("UPC-A"),
			               true, true, true, false, "12345678901", false, 11 );

			registerStyle( "ean-13", "", tr("EAN-13"),
			               true, true, true, false, "123456789012", false, 12 );

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

			registerStyle( "datamatrix", "", tr("IEC16022 (DataMatrix)"),
			               false, false, true, false, "1234567890AB", false, 12 );

#if HAVE_GNU_BARCODE
			//
			// GNU Barcode backend
			//
			registerBackend( "gnu-barcode", "GNU Barcode" );
		
			glbarcode::Factory::registerType( "gnu-barcode::ean",      GnuBarcode::Ean::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-8",    GnuBarcode::Ean8::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-8+2",  GnuBarcode::Ean8_2::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-8+5",  GnuBarcode::Ean8_5::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-13",   GnuBarcode::Ean13::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-13+2", GnuBarcode::Ean13_2::create );
			glbarcode::Factory::registerType( "gnu-barcode::ean-13+5", GnuBarcode::Ean13_5::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc",      GnuBarcode::Upc::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-a",    GnuBarcode::UpcA::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-a+2",  GnuBarcode::UpcA_2::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-a+5",  GnuBarcode::UpcA_5::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-e",    GnuBarcode::UpcE::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-e+2",  GnuBarcode::UpcE_2::create );
			glbarcode::Factory::registerType( "gnu-barcode::upc-e+5",  GnuBarcode::UpcE_5::create );
			glbarcode::Factory::registerType( "gnu-barcode::isbn",     GnuBarcode::Isbn::create );
			glbarcode::Factory::registerType( "gnu-barcode::isbn+5",   GnuBarcode::Isbn_5::create );
			glbarcode::Factory::registerType( "gnu-barcode::code39",   GnuBarcode::Code39::create );
			glbarcode::Factory::registerType( "gnu-barcode::code128",  GnuBarcode::Code128::create );
			glbarcode::Factory::registerType( "gnu-barcode::code128c", GnuBarcode::Code128C::create );
			glbarcode::Factory::registerType( "gnu-barcode::code128b", GnuBarcode::Code128B::create );
			glbarcode::Factory::registerType( "gnu-barcode::i25",      GnuBarcode::I25::create );
			glbarcode::Factory::registerType( "gnu-barcode::cbr",      GnuBarcode::Cbr::create );
			glbarcode::Factory::registerType( "gnu-barcode::msi",      GnuBarcode::Msi::create );
			glbarcode::Factory::registerType( "gnu-barcode::pls",      GnuBarcode::Pls::create );
			glbarcode::Factory::registerType( "gnu-barcode::code93",   GnuBarcode::Code93::create );

			registerStyle( "ean", "gnu-barcode", tr("EAN (any)"),
			               true, true, true, false, "000000000000 00000", false, 17 );
			registerStyle( "ean-8", "gnu-barcode", tr("EAN-8"),
			               true, true, true, false, "0000000", false, 7 );
			registerStyle( "ean-8+2", "gnu-barcode", tr("EAN-8+2"),
			               true, true, true, false, "0000000 00", false, 9 );
			registerStyle( "ean-8+5", "gnu-barcode", tr("EAN-8+5"),
			               true, true, true, false, "0000000 00000", false, 12 );
			registerStyle( "ean-13", "gnu-barcode", tr("EAN-13"),
			               true, true, true, false, "000000000000", false, 12 );
			registerStyle( "ean-13+2", "gnu-barcode", tr("EAN-13+2"),
			               true, true, true, false, "000000000000 00", false, 14 );
			registerStyle( "ean-13+5", "gnu-barcode", tr("EAN-13+5"),
			               true, true, true, false, "000000000000 00000", false, 17 );
			registerStyle( "upc", "gnu-barcode", tr("UPC (UPC-A or UPC-E)"),
			               true, true, true, false, "00000000000 00000", false, 16 );
			registerStyle( "upc-a", "gnu-barcode", tr("UPC-A"),
			               true, true, true, false, "00000000000", false, 11 );
			registerStyle( "upc-a+2", "gnu-barcode", tr("UPC-A +2"),
			               true, true, true, false, "00000000000 00", false, 13 );
			registerStyle( "upc-a+5", "gnu-barcode", tr("UPC-A +5"),
			               true, true, true, false, "00000000000 00000", false, 16 );
			registerStyle( "upc-e", "gnu-barcode", tr("UPC-E"),
			               true, true, true, false, "000000", false, 6 );
			registerStyle( "upc-e+2", "gnu-barcode", tr("UPC-E +2"),
			               true, true, true, false, "000000 00", false, 8 );
			registerStyle( "upc-e+5", "gnu-barcode", tr("UPC-E +5"),
			               true, true, true, false, "000000 00000", false, 11 );
			registerStyle( "isbn", "gnu-barcode", tr("ISBN"),
			               true, true, true, true, "0-00000-000-0", false, 10 );
			registerStyle( "isbn+5", "gnu-barcode", tr("ISBN +5"),
			               true, true, true, true, "0-00000-000-0 00000", false, 15 );
			registerStyle( "code39", "gnu-barcode", tr("Code 39"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "code128", "gnu-barcode", tr("Code 128"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "code128c", "gnu-barcode", tr("Code 128C"),
			               true, true, true, false, "0000000000", true, 10 );
			registerStyle( "code128b", "gnu-barcode", tr("Code 128B"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "i25", "gnu-barcode", tr("Interleaved 2 of 5"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "cbr", "gnu-barcode", tr("Codabar"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "msi", "gnu-barcode", tr("MSI"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "pls", "gnu-barcode", tr("Plessey"),
			               true, true, true, true, "0000000000", true, 10 );
			registerStyle( "code93", "gnu-barcode", tr("Code 93"),
			               true, true, true, false, "0000000000", true, 10 );
#endif // HAVE_GNU_BARCODE

#if HAVE_QRENCODE
			//
			// Libqrencode backend
			//
			registerBackend( "qrencode", "QREncode" );
		
			glbarcode::Factory::registerType( "qrencode::qrcode", QrEncode::QrCode::create );

			registerStyle( "qrcode", "qrencode", tr("IEC18004 (QRCode)"),
			               false, false, true, false, "1234567890AB", false, 12 );
#endif // HAVE_QRENCODE

#if HAVE_ZINT_2_6
			//
			// Zint barcode backend (Version 2.6.x)
			//
			registerBackend( "zint_2_6", "Zint" );
		
			glbarcode::Factory::registerType( "zint_2_6::ausp",     Zint_2_6::AusP::create );
			glbarcode::Factory::registerType( "zint_2_6::ausrp",    Zint_2_6::AusRP::create );
			glbarcode::Factory::registerType( "zint_2_6::ausrt",    Zint_2_6::AusRT::create );
			glbarcode::Factory::registerType( "zint_2_6::ausrd",    Zint_2_6::AusRD::create );
			glbarcode::Factory::registerType( "zint_2_6::aztec",    Zint_2_6::Aztec::create );
			glbarcode::Factory::registerType( "zint_2_6::azrun",    Zint_2_6::Azrun::create );
			glbarcode::Factory::registerType( "zint_2_6::cbr",      Zint_2_6::Cbr::create );
			glbarcode::Factory::registerType( "zint_2_6::code1",    Zint_2_6::Code1::create );
			glbarcode::Factory::registerType( "zint_2_6::code11",   Zint_2_6::Code11::create );
			glbarcode::Factory::registerType( "zint_2_6::c16k",     Zint_2_6::C16k::create );
			glbarcode::Factory::registerType( "zint_2_6::c25m",     Zint_2_6::C25m::create );
			glbarcode::Factory::registerType( "zint_2_6::c25i",     Zint_2_6::C25i::create );
			glbarcode::Factory::registerType( "zint_2_6::c25dl",    Zint_2_6::C25dl::create );
			glbarcode::Factory::registerType( "zint_2_6::code32",   Zint_2_6::Code32::create );
			glbarcode::Factory::registerType( "zint_2_6::code39",   Zint_2_6::Code39::create );
			glbarcode::Factory::registerType( "zint_2_6::code39e",  Zint_2_6::Code39e::create );
			glbarcode::Factory::registerType( "zint_2_6::code49",   Zint_2_6::Code49::create );
			glbarcode::Factory::registerType( "zint_2_6::code93",   Zint_2_6::Code93::create );
			glbarcode::Factory::registerType( "zint_2_6::code128",  Zint_2_6::Code128::create );
			glbarcode::Factory::registerType( "zint_2_6::code128b", Zint_2_6::Code128b::create );
			glbarcode::Factory::registerType( "zint_2_6::daft",     Zint_2_6::Daft::create );
			glbarcode::Factory::registerType( "zint_2_6::dmtx",     Zint_2_6::Dmtx::create );
			glbarcode::Factory::registerType( "zint_2_6::dpl",      Zint_2_6::Dpl::create );
			glbarcode::Factory::registerType( "zint_2_6::dpi",      Zint_2_6::Dpi::create );
			glbarcode::Factory::registerType( "zint_2_6::kix",      Zint_2_6::Kix::create );
			glbarcode::Factory::registerType( "zint_2_6::ean",      Zint_2_6::Ean::create );
			glbarcode::Factory::registerType( "zint_2_6::gmtx",     Zint_2_6::Gmtx::create );
			glbarcode::Factory::registerType( "zint_2_6::gs1-128",  Zint_2_6::Gs1128::create );
			glbarcode::Factory::registerType( "zint_2_6::rss14",    Zint_2_6::Rss14::create );
			glbarcode::Factory::registerType( "zint_2_6::rssltd",   Zint_2_6::Rssltd::create );
			glbarcode::Factory::registerType( "zint_2_6::rssexp",   Zint_2_6::Rssexp::create );
			glbarcode::Factory::registerType( "zint_2_6::rsss",     Zint_2_6::Rsss::create );
			glbarcode::Factory::registerType( "zint_2_6::rssso",    Zint_2_6::Rssso::create );
			glbarcode::Factory::registerType( "zint_2_6::rssse",    Zint_2_6::Rssse::create );
			glbarcode::Factory::registerType( "zint_2_6::hibc128",  Zint_2_6::Hibc128::create );
			glbarcode::Factory::registerType( "zint_2_6::hibc39",   Zint_2_6::Hibc39::create );
			glbarcode::Factory::registerType( "zint_2_6::hibcdm",   Zint_2_6::Hibcdm::create );
			glbarcode::Factory::registerType( "zint_2_6::hibcqr",   Zint_2_6::Hibcqr::create );
			glbarcode::Factory::registerType( "zint_2_6::hibcpdf",  Zint_2_6::Hibcpdf::create );
			glbarcode::Factory::registerType( "zint_2_6::hibcmpdf", Zint_2_6::Hibcmpdf::create );
			glbarcode::Factory::registerType( "zint_2_6::hibcaz",   Zint_2_6::Hibcaz::create );
			glbarcode::Factory::registerType( "zint_2_6::i25",      Zint_2_6::I25::create );
			glbarcode::Factory::registerType( "zint_2_6::isbn",     Zint_2_6::Isbn::create );
			glbarcode::Factory::registerType( "zint_2_6::itf14",    Zint_2_6::Itf14::create );
			glbarcode::Factory::registerType( "zint_2_6::japan",    Zint_2_6::Japan::create );
			glbarcode::Factory::registerType( "zint_2_6::korea",    Zint_2_6::Korea::create );
			glbarcode::Factory::registerType( "zint_2_6::logm",     Zint_2_6::Logm::create );
			glbarcode::Factory::registerType( "zint_2_6::maxi",     Zint_2_6::Maxi::create );
			glbarcode::Factory::registerType( "zint_2_6::mpdf",     Zint_2_6::Mpdf::create );
			glbarcode::Factory::registerType( "zint_2_6::mqr",      Zint_2_6::Mqr::create );
			glbarcode::Factory::registerType( "zint_2_6::msi",      Zint_2_6::Msi::create );
			glbarcode::Factory::registerType( "zint_2_6::nve",      Zint_2_6::Nve::create );
			glbarcode::Factory::registerType( "zint_2_6::pdf",      Zint_2_6::Pdf::create );
			glbarcode::Factory::registerType( "zint_2_6::pdft",     Zint_2_6::Pdft::create );
			glbarcode::Factory::registerType( "zint_2_6::plan",     Zint_2_6::Plan::create );
			glbarcode::Factory::registerType( "zint_2_6::postnet",  Zint_2_6::Postnet::create );
			glbarcode::Factory::registerType( "zint_2_6::pharma",   Zint_2_6::Pharma::create );
			glbarcode::Factory::registerType( "zint_2_6::pharma2",  Zint_2_6::Pharma2::create );
			glbarcode::Factory::registerType( "zint_2_6::pzn",      Zint_2_6::Pzn::create );
			glbarcode::Factory::registerType( "zint_2_6::qr",       Zint_2_6::Qr::create );
			glbarcode::Factory::registerType( "zint_2_6::rm4",      Zint_2_6::Rm4::create );
			glbarcode::Factory::registerType( "zint_2_6::tele",     Zint_2_6::Tele::create );
			glbarcode::Factory::registerType( "zint_2_6::telex",    Zint_2_6::Telex::create );
			glbarcode::Factory::registerType( "zint_2_6::upc-a",    Zint_2_6::UpcA::create );
			glbarcode::Factory::registerType( "zint_2_6::upc-e",    Zint_2_6::UpcE::create );
			glbarcode::Factory::registerType( "zint_2_6::usps",     Zint_2_6::Usps::create );
			glbarcode::Factory::registerType( "zint_2_6::pls",      Zint_2_6::Pls::create );

			registerStyle( "ausp", "zint_2_6", tr("Australia Post Standard"),
			               false, false, true, false, "12345678901234567890123", true, 23 );

			registerStyle( "ausrp", "zint_2_6", tr("Australia Post Reply Paid"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "ausrt", "zint_2_6", tr("Australia Post Route Code"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "ausrd", "zint_2_6", tr("Australia Post Redirect"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "aztec", "zint_2_6", tr("Aztec Code"),
			               false, false, true, false, "1234567890", true, 10 );
          
			registerStyle( "azrun", "zint_2_6", tr("Aztec Rune"),
			               false, false, true, false, "255", true, 3 );

			registerStyle( "cbr", "zint_2_6", tr("Codabar"),
			               true, true, true, false, "ABCDABCDAB", true, 10 );

			registerStyle( "code1", "zint_2_6", tr("Code One"), 
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "code11", "zint_2_6", tr("Code 11"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c16k", "zint_2_6", tr("Code 16K"),
			               false, false, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25m", "zint_2_6", tr("Code 2 of 5 Matrix"), 
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25i", "zint_2_6", tr("Code 2 of 5 IATA"), 
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25dl", "zint_2_6", tr("Code 2 of 5 Data Logic"), 
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code32", "zint_2_6", tr("Code 32 (Italian Pharmacode)"), 
			               true, true, true, false, "12345678", true, 8 );

			registerStyle( "code39", "zint_2_6", tr("Code 39"),
			               true, true, false, false, "0000000000", true, 10 );
          
			registerStyle( "code39e", "zint_2_6", tr("Code 39 Extended"), 
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code49", "zint_2_6", tr("Code 49"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "code93", "zint_2_6", tr("Code 93"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code128", "zint_2_6", tr("Code 128"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "code128b", "zint_2_6", tr("Code 128 (Mode C suppression)"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "daft", "zint_2_6", tr("DAFT Code"),
			               false, false, false, false, "DAFTDAFTDAFTDAFT", true, 16 );

			registerStyle( "dmtx", "zint_2_6", tr("Data Matrix"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "dpl", "zint_2_6", tr("Deutsche Post Leitcode"),
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "dpi", "zint_2_6", tr("Deutsche Post Identcode"),
			               true, true, true, false, "12345678901", true, 11 );
          
			registerStyle( "kix", "zint_2_6", tr("Dutch Post KIX Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "ean", "zint_2_6", tr("EAN"),
			               true, true, true, false, "1234567890123", false, 13 );

			registerStyle( "gmtx", "zint_2_6", tr("Grid Matrix"), 
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "gs1-128", "zint_2_6", tr("GS1-128"),
			               true, true, true, false, "[01]12345678901234", false, 18 );

			registerStyle( "rss14", "zint_2_6", tr("GS1 DataBar-14"),
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "rssltd", "zint_2_6", "GS1 DataBar-14 Limited", 
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "rssexp", "zint_2_6", "GS1 DataBar Extended", 
			               true, true, true, false, "[01]12345678901234", false, 18 );
          
			registerStyle( "rsss", "zint_2_6", tr("GS1 DataBar-14 Stacked"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "rssso", "zint_2_6", tr("GS1 DataBar-14 Stacked Omni."),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "rssse", "zint_2_6", tr("GS1 DataBar Extended Stacked"),
			               false, false, true, false, "[01]12345678901234", false, 18 );

			registerStyle( "hibc128", "zint_2_6", tr("HIBC Code 128"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "hibc39", "zint_2_6", tr("HIBC Code 39"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "hibcdm", "zint_2_6", tr("HIBC Data Matrix"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcqr", "zint_2_6", tr("HIBC QR Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcpdf", "zint_2_6", tr("HIBC PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcmpdf", "zint_2_6", tr("HIBC Micro PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcaz", "zint_2_6", tr("HIBC Aztec Code"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "i25", "zint_2_6", tr("Interleaved 2 of 5"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "isbn", "zint_2_6", tr("ISBN"),
			               true, true, true, false, "123456789", false, 9 );

			registerStyle( "itf14", "zint_2_6", tr("ITF-14"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "japan", "zint_2_6", tr("Japanese Postal"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "korea", "zint_2_6", tr("Korean Postal"),
			               true, true, true, false, "123456", false, 6 );

			registerStyle( "logm", "zint_2_6", tr("LOGMARS"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "maxi", "zint_2_6", tr("Maxicode"),
			               false, false, false, false, "0000000000", true, 10 );

			registerStyle( "mpdf", "zint_2_6", tr("Micro PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "mqr", "zint_2_6", tr("Micro QR Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "msi", "zint_2_6", tr("MSI Plessey"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "nve", "zint_2_6", tr("NVE-18"),
			               true, true, true, false, "12345678901234567", false, 17 );

			registerStyle( "pdf", "zint_2_6", tr("PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "pdft", "zint_2_6", tr("PDF417 Truncated"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "plan", "zint_2_6", tr("PLANET"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "postnet", "zint_2_6", tr("PostNet"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "pharma", "zint_2_6", tr("Pharmacode"),
			               false, false, true, false, "123456", false, 6 );

			registerStyle( "pharma2", "zint_2_6", tr("Pharmacode 2-track"),
			               false, false, true, false, "12345678", false, 8 );

			registerStyle( "pzn", "zint_2_6", tr("Pharmazentral Nummer (PZN)"),
			               true, true, true, false, "123456", false, 6 );

			registerStyle( "qr", "zint_2_6", tr("QR Code"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "rm4", "zint_2_6", tr("Royal Mail 4-State"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "tele", "zint_2_6", tr("Telepen"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "telex", "zint_2_6", tr("Telepen Numeric"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "upc-a", "zint_2_6", tr("UPC-A"), 
			               true, true, true, false, "12345678901", false, 11 );
          
			registerStyle( "upc-e", "zint_2_6", tr("UPC-E"), 
			               true, true, true, false, "1234567", false, 7 );
          
			registerStyle( "usps", "zint_2_6", tr("USPS One Code"),
			               false, false, true, false, "12345678901234567890", true, 20 );

			registerStyle( "pls", "zint_2_6", tr("UK Plessey"),
			               true, true, true, false, "0000000000", true, 10 );
#endif // HAVE_ZINT_2_6

#if HAVE_ZINT
			//
			// Zint barcode backend (Version 2.7+)
			//
			registerBackend( "zint", "Zint" );
		
			glbarcode::Factory::registerType( "zint::ausp",     Zint::AusP::create );
			glbarcode::Factory::registerType( "zint::ausrp",    Zint::AusRP::create );
			glbarcode::Factory::registerType( "zint::ausrt",    Zint::AusRT::create );
			glbarcode::Factory::registerType( "zint::ausrd",    Zint::AusRD::create );
			glbarcode::Factory::registerType( "zint::aztec",    Zint::Aztec::create );
			glbarcode::Factory::registerType( "zint::azrun",    Zint::Azrun::create );
			glbarcode::Factory::registerType( "zint::cbr",      Zint::Cbr::create );
			glbarcode::Factory::registerType( "zint::code1",    Zint::Code1::create );
			glbarcode::Factory::registerType( "zint::code11",   Zint::Code11::create );
			glbarcode::Factory::registerType( "zint::c16k",     Zint::C16k::create );
			glbarcode::Factory::registerType( "zint::c25m",     Zint::C25m::create );
			glbarcode::Factory::registerType( "zint::c25i",     Zint::C25i::create );
			glbarcode::Factory::registerType( "zint::c25dl",    Zint::C25dl::create );
			glbarcode::Factory::registerType( "zint::code32",   Zint::Code32::create );
			glbarcode::Factory::registerType( "zint::code39",   Zint::Code39::create );
			glbarcode::Factory::registerType( "zint::code39e",  Zint::Code39e::create );
			glbarcode::Factory::registerType( "zint::code49",   Zint::Code49::create );
			glbarcode::Factory::registerType( "zint::code93",   Zint::Code93::create );
			glbarcode::Factory::registerType( "zint::code128",  Zint::Code128::create );
			glbarcode::Factory::registerType( "zint::code128b", Zint::Code128b::create );
			glbarcode::Factory::registerType( "zint::daft",     Zint::Daft::create );
			glbarcode::Factory::registerType( "zint::dmtx",     Zint::Dmtx::create );
			glbarcode::Factory::registerType( "zint::dpl",      Zint::Dpl::create );
			glbarcode::Factory::registerType( "zint::dpi",      Zint::Dpi::create );
			glbarcode::Factory::registerType( "zint::kix",      Zint::Kix::create );
			glbarcode::Factory::registerType( "zint::ean",      Zint::Ean::create );
			glbarcode::Factory::registerType( "zint::gmtx",     Zint::Gmtx::create );
			glbarcode::Factory::registerType( "zint::gs1-128",  Zint::Gs1128::create );
			glbarcode::Factory::registerType( "zint::rss14",    Zint::Rss14::create );
			glbarcode::Factory::registerType( "zint::rssltd",   Zint::Rssltd::create );
			glbarcode::Factory::registerType( "zint::rssexp",   Zint::Rssexp::create );
			glbarcode::Factory::registerType( "zint::rsss",     Zint::Rsss::create );
			glbarcode::Factory::registerType( "zint::rssso",    Zint::Rssso::create );
			glbarcode::Factory::registerType( "zint::rssse",    Zint::Rssse::create );
			glbarcode::Factory::registerType( "zint::hibc128",  Zint::Hibc128::create );
			glbarcode::Factory::registerType( "zint::hibc39",   Zint::Hibc39::create );
			glbarcode::Factory::registerType( "zint::hibcdm",   Zint::Hibcdm::create );
			glbarcode::Factory::registerType( "zint::hibcqr",   Zint::Hibcqr::create );
			glbarcode::Factory::registerType( "zint::hibcpdf",  Zint::Hibcpdf::create );
			glbarcode::Factory::registerType( "zint::hibcmpdf", Zint::Hibcmpdf::create );
			glbarcode::Factory::registerType( "zint::hibcaz",   Zint::Hibcaz::create );
			glbarcode::Factory::registerType( "zint::i25",      Zint::I25::create );
			glbarcode::Factory::registerType( "zint::isbn",     Zint::Isbn::create );
			glbarcode::Factory::registerType( "zint::itf14",    Zint::Itf14::create );
			glbarcode::Factory::registerType( "zint::japan",    Zint::Japan::create );
			glbarcode::Factory::registerType( "zint::korea",    Zint::Korea::create );
			glbarcode::Factory::registerType( "zint::logm",     Zint::Logm::create );
			glbarcode::Factory::registerType( "zint::maxi",     Zint::Maxi::create );
			glbarcode::Factory::registerType( "zint::mpdf",     Zint::Mpdf::create );
			glbarcode::Factory::registerType( "zint::mqr",      Zint::Mqr::create );
			glbarcode::Factory::registerType( "zint::msi",      Zint::Msi::create );
			glbarcode::Factory::registerType( "zint::nve",      Zint::Nve::create );
			glbarcode::Factory::registerType( "zint::pdf",      Zint::Pdf::create );
			glbarcode::Factory::registerType( "zint::pdft",     Zint::Pdft::create );
			glbarcode::Factory::registerType( "zint::plan",     Zint::Plan::create );
			glbarcode::Factory::registerType( "zint::postnet",  Zint::Postnet::create );
			glbarcode::Factory::registerType( "zint::pharma",   Zint::Pharma::create );
			glbarcode::Factory::registerType( "zint::pharma2",  Zint::Pharma2::create );
			glbarcode::Factory::registerType( "zint::pzn",      Zint::Pzn::create );
			glbarcode::Factory::registerType( "zint::qr",       Zint::Qr::create );
			glbarcode::Factory::registerType( "zint::rm4",      Zint::Rm4::create );
			glbarcode::Factory::registerType( "zint::tele",     Zint::Tele::create );
			glbarcode::Factory::registerType( "zint::telex",    Zint::Telex::create );
			glbarcode::Factory::registerType( "zint::upc-a",    Zint::UpcA::create );
			glbarcode::Factory::registerType( "zint::upc-e",    Zint::UpcE::create );
			glbarcode::Factory::registerType( "zint::usps",     Zint::Usps::create );
			glbarcode::Factory::registerType( "zint::pls",      Zint::Pls::create );

			registerStyle( "ausp", "zint", tr("Australia Post Standard"),
			               false, false, true, false, "12345678901234567890123", true, 23 );

			registerStyle( "ausrp", "zint", tr("Australia Post Reply Paid"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "ausrt", "zint", tr("Australia Post Route Code"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "ausrd", "zint", tr("Australia Post Redirect"),
			               false, false, true, false, "12345678", true, 8 );

			registerStyle( "aztec", "zint", tr("Aztec Code"),
			               false, false, true, false, "1234567890", true, 10 );
          
			registerStyle( "azrun", "zint", tr("Aztec Rune"),
			               false, false, true, false, "255", true, 3 );

			registerStyle( "cbr", "zint", tr("Codabar"),
			               true, true, true, false, "ABCDABCDAB", true, 10 );

			registerStyle( "code1", "zint", tr("Code One"), 
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "code11", "zint", tr("Code 11"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c16k", "zint", tr("Code 16K"),
			               false, false, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25m", "zint", tr("Code 2 of 5 Matrix"), 
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25i", "zint", tr("Code 2 of 5 IATA"), 
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "c25dl", "zint", tr("Code 2 of 5 Data Logic"), 
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code32", "zint", tr("Code 32 (Italian Pharmacode)"), 
			               true, true, true, false, "12345678", true, 8 );

			registerStyle( "code39", "zint", tr("Code 39"),
			               true, true, false, false, "0000000000", true, 10 );
          
			registerStyle( "code39e", "zint", tr("Code 39 Extended"), 
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code49", "zint", tr("Code 49"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "code93", "zint", tr("Code 93"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "code128", "zint", tr("Code 128"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "code128b", "zint", tr("Code 128 (Mode C suppression)"),
			               true, true, true, false, "0000000000", true, 10 );
          
			registerStyle( "daft", "zint", tr("DAFT Code"),
			               false, false, false, false, "DAFTDAFTDAFTDAFT", true, 16 );

			registerStyle( "dmtx", "zint", tr("Data Matrix"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "dpl", "zint", tr("Deutsche Post Leitcode"),
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "dpi", "zint", tr("Deutsche Post Identcode"),
			               true, true, true, false, "12345678901", true, 11 );
          
			registerStyle( "kix", "zint", tr("Dutch Post KIX Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "ean", "zint", tr("EAN"),
			               true, true, true, false, "1234567890123", false, 13 );

			registerStyle( "gmtx", "zint", tr("Grid Matrix"), 
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "gs1-128", "zint", tr("GS1-128"),
			               true, true, true, false, "[01]12345678901234", false, 18 );

			registerStyle( "rss14", "zint", tr("GS1 DataBar-14"),
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "rssltd", "zint", "GS1 DataBar-14 Limited", 
			               true, true, true, false, "1234567890123", true, 13 );
          
			registerStyle( "rssexp", "zint", "GS1 DataBar Extended", 
			               true, true, true, false, "[01]12345678901234", false, 18 );
          
			registerStyle( "rsss", "zint", tr("GS1 DataBar-14 Stacked"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "rssso", "zint", tr("GS1 DataBar-14 Stacked Omni."),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "rssse", "zint", tr("GS1 DataBar Extended Stacked"),
			               false, false, true, false, "[01]12345678901234", false, 18 );

			registerStyle( "hibc128", "zint", tr("HIBC Code 128"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "hibc39", "zint", tr("HIBC Code 39"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "hibcdm", "zint", tr("HIBC Data Matrix"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcqr", "zint", tr("HIBC QR Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcpdf", "zint", tr("HIBC PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcmpdf", "zint", tr("HIBC Micro PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "hibcaz", "zint", tr("HIBC Aztec Code"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "i25", "zint", tr("Interleaved 2 of 5"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "isbn", "zint", tr("ISBN"),
			               true, true, true, false, "123456789", false, 9 );

			registerStyle( "itf14", "zint", tr("ITF-14"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "japan", "zint", tr("Japanese Postal"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "korea", "zint", tr("Korean Postal"),
			               true, true, true, false, "123456", false, 6 );

			registerStyle( "logm", "zint", tr("LOGMARS"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "maxi", "zint", tr("Maxicode"),
			               false, false, false, false, "0000000000", true, 10 );

			registerStyle( "mpdf", "zint", tr("Micro PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "mqr", "zint", tr("Micro QR Code"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "msi", "zint", tr("MSI Plessey"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "nve", "zint", tr("NVE-18"),
			               true, true, true, false, "12345678901234567", false, 17 );

			registerStyle( "pdf", "zint", tr("PDF417"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "pdft", "zint", tr("PDF417 Truncated"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "plan", "zint", tr("PLANET"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "postnet", "zint", tr("PostNet"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "pharma", "zint", tr("Pharmacode"),
			               false, false, true, false, "123456", false, 6 );

			registerStyle( "pharma2", "zint", tr("Pharmacode 2-track"),
			               false, false, true, false, "12345678", false, 8 );

			registerStyle( "pzn", "zint", tr("Pharmazentral Nummer (PZN)"),
			               true, true, true, false, "123456", false, 6 );

			registerStyle( "qr", "zint", tr("QR Code"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "rm4", "zint", tr("Royal Mail 4-State"),
			               false, false, true, false, "0000000000", true, 10 );

			registerStyle( "tele", "zint", tr("Telepen"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "telex", "zint", tr("Telepen Numeric"),
			               true, true, true, false, "0000000000", true, 10 );

			registerStyle( "upc-a", "zint", tr("UPC-A"), 
			               true, true, true, false, "12345678901", false, 11 );
          
			registerStyle( "upc-e", "zint", tr("UPC-E"), 
			               true, true, true, false, "1234567", false, 7 );
          
			registerStyle( "usps", "zint", tr("USPS One Code"),
			               false, false, true, false, "12345678901234567890", true, 20 );

			registerStyle( "pls", "zint", tr("UK Plessey"),
			               true, true, true, false, "0000000000", true, 10 );
#endif // HAVE_ZINT

		}


		void Backends::init()
		{
			static Backends* singletonInstance = nullptr;
                
			if ( singletonInstance == nullptr )
			{
				singletonInstance = new Backends();
			}
		}


		const QStringList& Backends::backendList()
		{
			return mBackendIdList;
		}

	
		QString Backends::backendName( const QString& backendId )
		{
			return mBackendNameMap[ backendId ];
		}

	
		const QList<Style>& Backends::styleList()
		{
			return mStyleList;
		}


		const Style& Backends::defaultStyle()
		{
			return mStyleList[0];
		}


		const Style& Backends::style( const QString& backendId, const QString& StyleId )
		{
			foreach ( const Style& bcStyle, mStyleList )
			{
				if ( (bcStyle.backendId() == backendId) && (bcStyle.id() == StyleId) )
				{
					return bcStyle;
				}
			}

			return defaultStyle();
		}


		void Backends::registerBackend( const QString& backendId, const QString& backendName )
		{
			mBackendIdList.append( backendId );
			mBackendNameMap[ backendId ] = backendName;
		}


		void Backends::registerStyle( const QString& id,
		                              const QString& backendId,
		                              const QString& name,
		                              bool           canText,
		                              bool           textOptional,
		                              bool           canChecksum,
		                              bool           checksumOptional,
		                              const QString& defaultDigits,
		                              bool           canFreeForm,
		                              int            preferedN )
		{
			Style style( id, backendId, name,
			             canText, textOptional,
			             canChecksum, checksumOptional,
			             defaultDigits,
			             canFreeForm, preferedN );

			mStyleList.append( style );
		}

	} // namespace barcode
} //namespace glabels
