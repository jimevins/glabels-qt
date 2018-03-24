/*  TemplateDesigner.cpp
 *
 *  Copyright (C) 2018  Jim Evins <evins@snaught.com>
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

#include "TemplateDesigner.h"

#include "model/Db.h"
#include "model/Distance.h"
#include "model/FrameRect.h"
#include "model/FrameRound.h"
#include "model/FrameEllipse.h"
#include "model/FrameCd.h"
#include "model/Markup.h"
#include "model/Settings.h"

#include <QVBoxLayout>
#include <QtDebug>

#include <algorithm>
#include <iostream>

namespace glabels
{

	//
	// Private types and constants
	//
	namespace
	{

		enum PageId
		{
			IntroPageId,
			NamePageId,
			PageSizePageId,
			ShapePageId,
			RectPageId,
			RoundPageId,
			EllipsePageId,
			CdPageId,
			NLayoutsPageId,
			OneLayoutPageId,
			TwoLayoutPageId,
			ApplyPageId
		};

	
		const QString defaultPageSize[] =
		{
			/* ISO */ "A4",
			/* US  */ "US Letter"
		};

	
		const double maxPageSize[] =
		{
			/* PT */ 5000,
			/* IN */ 70,
			/* MM */ 1800,
			/* CM */ 180,
			/* PC */ 420
		};

		const model::Distance defaultMargin    = model::Distance::in(0.125);
		const model::Distance defaultWaste     = model::Distance::in(0);

		const model::Distance defaultRectW     = model::Distance::in(3.5);
		const model::Distance defaultRectH     = model::Distance::in(2.0);
		const model::Distance defaultRectR     = model::Distance::in(0);

		const model::Distance defaultRoundR    = model::Distance::in(0.75);

		const model::Distance defaultEllipseW  = model::Distance::in(3.5);
		const model::Distance defaultEllipseH  = model::Distance::in(2.0);

		const model::Distance defaultCdR1      = model::Distance::in(2.3125);
		const model::Distance defaultCdR2      = model::Distance::in(0.8125);
		const model::Distance defaultCdClip    = model::Distance::in(0);
		
	}


	///
	/// Constructor
	///
	TemplateDesigner::TemplateDesigner( QWidget* parent )
		: QWizard(parent)
	{
		setWindowTitle( tr("Product Template Designer") );
		setPixmap( QWizard::LogoPixmap, QPixmap( ":icons/scalable/apps/glabels.svg" ) );
		setWizardStyle( QWizard::ModernStyle );

		setPage( IntroPageId,     new TemplateDesignerIntroPage() );
		setPage( NamePageId,      new TemplateDesignerNamePage() );
		setPage( PageSizePageId,  new TemplateDesignerPageSizePage() );
		setPage( ShapePageId,     new TemplateDesignerShapePage() );
		setPage( RectPageId,      new TemplateDesignerRectPage() );
		setPage( RoundPageId,     new TemplateDesignerRoundPage() );
		setPage( EllipsePageId,   new TemplateDesignerEllipsePage() );
		setPage( CdPageId,        new TemplateDesignerCdPage() );
		setPage( NLayoutsPageId,  new TemplateDesignerNLayoutsPage() );
		setPage( OneLayoutPageId, new TemplateDesignerOneLayoutPage() );
		setPage( TwoLayoutPageId, new TemplateDesignerTwoLayoutPage() );
		setPage( ApplyPageId,     new TemplateDesignerApplyPage() );
	}


	///
	/// Control wizard's non-linear page order
	///
	int TemplateDesigner::nextId() const
	{
		switch (currentId())
		{
			
		case IntroPageId:
			return NamePageId;
			
		case NamePageId:
			return PageSizePageId;
			
		case PageSizePageId:
			return ShapePageId;
			
		case ShapePageId:
			if ( field( "shape.rect" ).toBool() )
			{
				return RectPageId;
			}
			else if ( field( "shape.round" ).toBool() )
			{
				return RoundPageId;
			}
			else if ( field( "shape.ellipse" ).toBool() )
			{
				return EllipsePageId;
			}
			else
			{
				return CdPageId;
			}
			
		case RectPageId:
			return NLayoutsPageId;
			
		case RoundPageId:
			return NLayoutsPageId;
			
		case EllipsePageId:
			return NLayoutsPageId;
			
		case CdPageId:
			return NLayoutsPageId;
			
		case NLayoutsPageId:
			if ( field( "nLayouts.one" ).toBool() )
			{
				return OneLayoutPageId;
			}
			else
			{
				return TwoLayoutPageId;
			}

		case OneLayoutPageId:
			return ApplyPageId;
			
		case TwoLayoutPageId:
			return ApplyPageId;
			
		default:
			return -1;
		}
	}


	///
	/// Determine width of individual item
	///
	double TemplateDesigner::itemWidth()
	{
		// Note: all distance units are the same in wizard, so no conversions needed
		if ( field( "shape.rect" ).toBool() )
		{
			return field( "rect.w" ).toDouble();
		}
		else if ( field( "shape.round" ).toBool() )
		{
			return 2 * field( "round.r" ).toDouble();
		}
		else if ( field( "shape.ellipse" ).toBool() )
		{
			return field( "ellipse.w" ).toDouble();
		}
		else
		{
			if ( field( "cd.xClip" ).toDouble() == 0 )
			{
				return 2 * field( "cd.r1" ).toDouble();
			}
			else
			{
				return field( "cd.xClip" ).toDouble();
			}
		}
	}


	///
	/// Determine height of individual item
	///
	double TemplateDesigner::itemHeight()
	{
		// Note: all distance units are the same in wizard, so no conversions needed
		if ( field( "shape.rect" ).toBool() )
		{
			return field( "rect.h" ).toDouble();
		}
		else if ( field( "shape.round" ).toBool() )
		{
			return 2 * field( "round.r" ).toDouble();
		}
		else if ( field( "shape.ellipse" ).toBool() )
		{
			return field( "ellipse.h" ).toDouble();
		}
		else
		{
			if ( field( "cd.xClip" ).toDouble() == 0 )
			{
				return 2 * field( "cd.r1" ).toDouble();
			}
			else
			{
				return field( "cd.yClip" ).toDouble();
			}
		}
	}


	///
	/// Determine X Waste of individual item
	///
	double TemplateDesigner::itemXWaste()
	{
		// Note: all distance units are the same in wizard, so no conversions needed
		if ( field( "shape.rect" ).toBool() )
		{
			return field( "rect.xWaste" ).toDouble();
		}
		else if ( field( "shape.round" ).toBool() )
		{
			return 2 * field( "round.waste" ).toDouble();
		}
		else if ( field( "shape.ellipse" ).toBool() )
		{
			return field( "ellipse.waste" ).toDouble();
		}
		else
		{
			return field( "cd.waste" ).toDouble();
		}
	}


	///
	/// Determine Y Waste of individual item
	///
	double TemplateDesigner::itemYWaste()
	{
		// Note: all distance units are the same in wizard, so no conversions needed
		if ( field( "shape.rect" ).toBool() )
		{
			return field( "rect.yWaste" ).toDouble();
		}
		else if ( field( "shape.round" ).toBool() )
		{
			return 2 * field( "round.waste" ).toDouble();
		}
		else if ( field( "shape.ellipse" ).toBool() )
		{
			return field( "ellipse.waste" ).toDouble();
		}
		else
		{
			return field( "cd.waste" ).toDouble();
		}
	}


	///
	/// Build template from wizard pages
	///
	model::Template* TemplateDesigner::buildTemplate()
	{
		model::Units units = model::Settings::units();

		QString brand = field( "name.brand" ).toString();
		QString part = field( "name.part" ).toString();
		QString description = field( "name.description" ).toString();
		QString paperId = model::Db::lookupPaperIdFromName( field( "pageSize.pageSize" ).toString() );
		model::Distance pageW( field( "pageSize.w" ).toDouble(), units );
		model::Distance pageH( field( "pageSize.h" ).toDouble(), units );
		
		auto t = new model::Template( brand, part, description, paperId, pageW, pageH );

		model::Frame* frame;
		if ( field( "shape.rect" ).toBool() )
		{
			model::Distance w( field( "rect.w" ).toDouble(), units );
			model::Distance h( field( "rect.h" ).toDouble(), units );
			model::Distance r( field( "rect.r" ).toDouble(), units );
			model::Distance xWaste( field( "rect.xWaste" ).toDouble(), units );
			model::Distance yWaste( field( "rect.yWaste" ).toDouble(), units );
			model::Distance margin( field( "rect.margin" ).toDouble(), units );

			frame = new model::FrameRect( w, h, r, xWaste, yWaste );
			frame->addMarkup( new model::MarkupMargin( frame, margin ) );
		}
		else if ( field( "shape.round" ).toBool() )
		{
			model::Distance r( field( "round.r" ).toDouble(), units );
			model::Distance waste( field( "round.waste" ).toDouble(), units );
			model::Distance margin( field( "round.margin" ).toDouble(), units );

			frame = new model::FrameRound( r, waste );
			frame->addMarkup( new model::MarkupMargin( frame, margin ) );
		}
		else if ( field( "shape.ellipse" ).toBool() )
		{
			model::Distance w( field( "ellipse.w" ).toDouble(), units );
			model::Distance h( field( "ellipse.h" ).toDouble(), units );
			model::Distance waste( field( "ellipse.waste" ).toDouble(), units );
			model::Distance margin( field( "ellipse.margin" ).toDouble(), units );

			frame = new model::FrameEllipse( w, h, waste );
			frame->addMarkup( new model::MarkupMargin( frame, margin ) );
		}
		else
		{
			model::Distance r1( field( "cd.r1" ).toDouble(), units );
			model::Distance r2( field( "cd.r2" ).toDouble(), units );
			model::Distance xClip( field( "cd.xClip" ).toDouble(), units );
			model::Distance yClip( field( "cd.yClip" ).toDouble(), units );
			model::Distance waste( field( "cd.waste" ).toDouble(), units );
			model::Distance margin( field( "cd.margin" ).toDouble(), units );

			frame = new model::FrameCd( r1, r2, xClip, yClip, waste );
			frame->addMarkup( new model::MarkupMargin( frame, margin ) );
		}
		t->addFrame( frame );

		if ( field( "nLayouts.one" ).toBool() )
		{
			int nx = field( "oneLayout.nx" ).toInt();
			int ny = field( "oneLayout.ny" ).toInt();
			model::Distance x0( field( "oneLayout.x0" ).toDouble(), units );
			model::Distance y0( field( "oneLayout.y0" ).toDouble(), units );
			model::Distance dx( field( "oneLayout.dx" ).toDouble(), units );
			model::Distance dy( field( "oneLayout.dy" ).toDouble(), units );

			frame->addLayout( new model::Layout( nx, ny, x0, y0, dx, dy ) );
		}
		else
		{
			int nx1 = field( "twoLayout.nx1" ).toInt();
			int ny1 = field( "twoLayout.ny1" ).toInt();
			model::Distance x01( field( "twoLayout.x01" ).toDouble(), units );
			model::Distance y01( field( "twoLayout.y01" ).toDouble(), units );
			model::Distance dx1( field( "twoLayout.dx1" ).toDouble(), units );
			model::Distance dy1( field( "twoLayout.dy1" ).toDouble(), units );

			int nx2 = field( "twoLayout.nx2" ).toInt();
			int ny2 = field( "twoLayout.ny2" ).toInt();
			model::Distance x02( field( "twoLayout.x02" ).toDouble(), units );
			model::Distance y02( field( "twoLayout.y02" ).toDouble(), units );
			model::Distance dx2( field( "twoLayout.dx2" ).toDouble(), units );
			model::Distance dy2( field( "twoLayout.dy2" ).toDouble(), units );

			frame->addLayout( new model::Layout( nx1, ny1, x01, y01, dx1, dy1 ) );
			frame->addLayout( new model::Layout( nx2, ny2, x02, y02, dx2, dy2 ) );
		}

		return t;
	}


	///
	/// Intro Page
	///
	TemplateDesignerIntroPage::TemplateDesignerIntroPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Welcome") );
		setSubTitle( tr("Welcome to the gLabels Product Template Designer.") );
		setPixmap( QWizard::WatermarkPixmap, QPixmap( ":images/TemplateDesigner/wizard-banner.png" ) );

		QWidget* widget = new QWidget;
		setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}


	///
	/// Name and Description Page
	///
	TemplateDesignerNamePage::TemplateDesignerNamePage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Name and Description") );
		setSubTitle( tr("Please enter the following identifying information about the product.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		registerField( "name.brand",       brandEntry );
		registerField( "name.part",        partEntry );
		registerField( "name.description", descriptionEntry );

		connect( brandEntry, &QLineEdit::textChanged, this, &TemplateDesignerNamePage::onChanged );
		connect( partEntry, &QLineEdit::textChanged, this, &TemplateDesignerNamePage::onChanged );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	bool TemplateDesignerNamePage::isComplete() const
	{
		return mCanContinue;
	}


	void TemplateDesignerNamePage::onChanged()
	{
		mCanContinue = !brandEntry->text().isEmpty() && !partEntry->text().isEmpty();
		emit completeChanged();
	}


	///
	/// Page Size Page
	///
	TemplateDesignerPageSizePage::TemplateDesignerPageSizePage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Page Size") );
		setSubTitle( tr("Please select the product page size.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		pageSizeCombo->insertItem( 0, tr("Other") );
		pageSizeCombo->insertItems( 1, model::Db::paperNames() );
		pageSizeCombo->setCurrentText( defaultPageSize[ model::Settings::preferedPageSizeFamily() ] );
		
		wSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wSpin->setSingleStep( model::Settings::units().resolution() );
		wSpin->setMaximum( maxPageSize[ model::Settings::units().toEnum() ] );
		wSpin->setEnabled( pageSizeCombo->currentText() == tr("Other") );
		
		hSpin->setSuffix( " " + model::Settings::units().toTrName() );
		hSpin->setDecimals( model::Settings::units().resolutionDigits() );
		hSpin->setSingleStep( model::Settings::units().resolution() );
		hSpin->setMaximum( maxPageSize[ model::Settings::units().toEnum() ] );
		hSpin->setEnabled( pageSizeCombo->currentText() == tr("Other") );

		if ( pageSizeCombo->currentText() != tr("Other") )
		{
			const model::Paper* paper = model::Db::lookupPaperFromName( pageSizeCombo->currentText() );
			wSpin->setValue( paper->width().inUnits( model::Settings::units() ) );
			hSpin->setValue( paper->height().inUnits( model::Settings::units() ) );
		}

		registerField( "pageSize.pageSize", pageSizeCombo, "currentText" );
		registerField( "pageSize.w",        wSpin,         "value" );
		registerField( "pageSize.h",        hSpin,         "value" );

		connect( pageSizeCombo, &QComboBox::currentTextChanged, this, &TemplateDesignerPageSizePage::onComboChanged );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerPageSizePage::onComboChanged()
	{
		if ( pageSizeCombo->currentText() != tr("Other") )
		{
			const model::Paper* paper = model::Db::lookupPaperFromName( pageSizeCombo->currentText() );
			wSpin->setValue( paper->width().inUnits( model::Settings::units() ) );
			hSpin->setValue( paper->height().inUnits( model::Settings::units() ) );
		}

		wSpin->setEnabled( pageSizeCombo->currentText() == tr("Other") );
		hSpin->setEnabled( pageSizeCombo->currentText() == tr("Other") );
	}


	///
	/// Shape Page
	///
	TemplateDesignerShapePage::TemplateDesignerShapePage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Product Shape") );
		setSubTitle( tr("Please select the basic product shape.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		registerField( "shape.rect",    rectRadio );
		registerField( "shape.round",   roundRadio );
		registerField( "shape.ellipse", ellipseRadio );
		registerField( "shape.cd",      cdRadio );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	///
	/// Rectangular Product Page
	///
	TemplateDesignerRectPage::TemplateDesignerRectPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Product Size") );
		setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		wSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wSpin->setSingleStep( model::Settings::units().resolution() );

		hSpin->setSuffix( " " + model::Settings::units().toTrName() );
		hSpin->setDecimals( model::Settings::units().resolutionDigits() );
		hSpin->setSingleStep( model::Settings::units().resolution() );

		rSpin->setSuffix( " " + model::Settings::units().toTrName() );
		rSpin->setDecimals( model::Settings::units().resolutionDigits() );
		rSpin->setSingleStep( model::Settings::units().resolution() );

		xWasteSpin->setSuffix( " " + model::Settings::units().toTrName() );
		xWasteSpin->setDecimals( model::Settings::units().resolutionDigits() );
		xWasteSpin->setSingleStep( model::Settings::units().resolution() );

		yWasteSpin->setSuffix( " " + model::Settings::units().toTrName() );
		yWasteSpin->setDecimals( model::Settings::units().resolutionDigits() );
		yWasteSpin->setSingleStep( model::Settings::units().resolution() );

		marginSpin->setSuffix( " " + model::Settings::units().toTrName() );
		marginSpin->setDecimals( model::Settings::units().resolutionDigits() );
		marginSpin->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		wSpin->setValue( defaultRectW.inUnits( model::Settings::units() ) );
		hSpin->setValue( defaultRectH.inUnits( model::Settings::units() ) );
		rSpin->setValue( defaultRectR.inUnits( model::Settings::units() ) );
		xWasteSpin->setValue( defaultWaste.inUnits( model::Settings::units() ) );
		yWasteSpin->setValue( defaultWaste.inUnits( model::Settings::units() ) );
		marginSpin->setValue( defaultMargin.inUnits( model::Settings::units() ) );

		registerField( "rect.w",      wSpin,      "value" );
		registerField( "rect.h",      hSpin,      "value" );
		registerField( "rect.r",      rSpin,      "value" );
		registerField( "rect.xWaste", xWasteSpin, "value" );
		registerField( "rect.yWaste", yWasteSpin, "value" );
		registerField( "rect.margin", marginSpin, "value" );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerRectPage::initializePage()
	{
		// set realistic limits based on previously chosen page size
		double wMax = field("pageSize.w").toDouble();
		double hMax = field("pageSize.h").toDouble();

		wSpin->setMaximum( wMax );
		hSpin->setMaximum( hMax );
		rSpin->setMaximum( std::min(wMax,hMax)/2.0 );
		xWasteSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		yWasteSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		marginSpin->setMaximum( std::min(wMax,hMax)/4.0 );
	}


	///
	/// Round Product Page
	///
	TemplateDesignerRoundPage::TemplateDesignerRoundPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Product Size") );
		setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		rSpin->setSuffix( " " + model::Settings::units().toTrName() );
		rSpin->setDecimals( model::Settings::units().resolutionDigits() );
		rSpin->setSingleStep( model::Settings::units().resolution() );

		wasteSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wasteSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wasteSpin->setSingleStep( model::Settings::units().resolution() );

		marginSpin->setSuffix( " " + model::Settings::units().toTrName() );
		marginSpin->setDecimals( model::Settings::units().resolutionDigits() );
		marginSpin->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		rSpin->setValue( defaultRoundR.inUnits( model::Settings::units() ) );
		wasteSpin->setValue( defaultWaste.inUnits( model::Settings::units() ) );
		marginSpin->setValue( defaultMargin.inUnits( model::Settings::units() ) );

		registerField( "round.r",      rSpin,      "value" );
		registerField( "round.waste",  wasteSpin,  "value" );
		registerField( "round.margin", marginSpin, "value" );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerRoundPage::initializePage()
	{
		// set realistic limits based on previously chosen page size
		double wMax = field("pageSize.w").toDouble();
		double hMax = field("pageSize.h").toDouble();

		rSpin->setMaximum( std::min(wMax,hMax)/2.0 );
		wasteSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		marginSpin->setMaximum( std::min(wMax,hMax)/4.0 );
	}


	///
	/// Elliptical Product Page
	///
	TemplateDesignerEllipsePage::TemplateDesignerEllipsePage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Product Size") );
		setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		wSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wSpin->setSingleStep( model::Settings::units().resolution() );

		hSpin->setSuffix( " " + model::Settings::units().toTrName() );
		hSpin->setDecimals( model::Settings::units().resolutionDigits() );
		hSpin->setSingleStep( model::Settings::units().resolution() );

		wasteSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wasteSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wasteSpin->setSingleStep( model::Settings::units().resolution() );

		marginSpin->setSuffix( " " + model::Settings::units().toTrName() );
		marginSpin->setDecimals( model::Settings::units().resolutionDigits() );
		marginSpin->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		wSpin->setValue( defaultEllipseW.inUnits( model::Settings::units() ) );
		hSpin->setValue( defaultEllipseH.inUnits( model::Settings::units() ) );
		wasteSpin->setValue( defaultWaste.inUnits( model::Settings::units() ) );
		marginSpin->setValue( defaultMargin.inUnits( model::Settings::units() ) );

		registerField( "ellipse.w",      wSpin,      "value" );
		registerField( "ellipse.h",      hSpin,      "value" );
		registerField( "ellipse.waste",  wasteSpin,  "value" );
		registerField( "ellipse.margin", marginSpin, "value" );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerEllipsePage::initializePage()
	{
		// set realistic limits based on previously chosen page size
		double wMax = field("pageSize.w").toDouble();
		double hMax = field("pageSize.h").toDouble();

		wSpin->setMaximum( wMax );
		hSpin->setMaximum( hMax );
		wasteSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		marginSpin->setMaximum( std::min(wMax,hMax)/4.0 );
	}


	///
	/// CD/DVD Product Page
	///
	TemplateDesignerCdPage::TemplateDesignerCdPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Product Size") );
		setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		r1Spin->setSuffix( " " + model::Settings::units().toTrName() );
		r1Spin->setDecimals( model::Settings::units().resolutionDigits() );
		r1Spin->setSingleStep( model::Settings::units().resolution() );

		r2Spin->setSuffix( " " + model::Settings::units().toTrName() );
		r2Spin->setDecimals( model::Settings::units().resolutionDigits() );
		r2Spin->setSingleStep( model::Settings::units().resolution() );

		xClipSpin->setSuffix( " " + model::Settings::units().toTrName() );
		xClipSpin->setDecimals( model::Settings::units().resolutionDigits() );
		xClipSpin->setSingleStep( model::Settings::units().resolution() );

		yClipSpin->setSuffix( " " + model::Settings::units().toTrName() );
		yClipSpin->setDecimals( model::Settings::units().resolutionDigits() );
		yClipSpin->setSingleStep( model::Settings::units().resolution() );

		wasteSpin->setSuffix( " " + model::Settings::units().toTrName() );
		wasteSpin->setDecimals( model::Settings::units().resolutionDigits() );
		wasteSpin->setSingleStep( model::Settings::units().resolution() );

		marginSpin->setSuffix( " " + model::Settings::units().toTrName() );
		marginSpin->setDecimals( model::Settings::units().resolutionDigits() );
		marginSpin->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		r1Spin->setValue( defaultCdR1.inUnits( model::Settings::units() ) );
		r2Spin->setValue( defaultCdR2.inUnits( model::Settings::units() ) );
		xClipSpin->setValue( defaultCdClip.inUnits( model::Settings::units() ) );
		yClipSpin->setValue( defaultCdClip.inUnits( model::Settings::units() ) );
		wasteSpin->setValue( defaultWaste.inUnits( model::Settings::units() ) );
		marginSpin->setValue( defaultMargin.inUnits( model::Settings::units() ) );

		registerField( "cd.r1",     r1Spin,     "value" );
		registerField( "cd.r2",     r2Spin,     "value" );
		registerField( "cd.xClip",  xClipSpin,  "value" );
		registerField( "cd.yClip",  yClipSpin,  "value" );
		registerField( "cd.waste",  wasteSpin,  "value" );
		registerField( "cd.margin", marginSpin, "value" );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerCdPage::initializePage()
	{
		// set realistic limits based on previously chosen page size
		double wMax = field("pageSize.w").toDouble();
		double hMax = field("pageSize.h").toDouble();

		r1Spin->setMaximum( std::min(wMax,hMax)/2.0 );
		r2Spin->setMaximum( std::min(wMax,hMax)/4.0 );
		xClipSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		yClipSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		wasteSpin->setMaximum( std::min(wMax,hMax)/4.0 );
		marginSpin->setMaximum( std::min(wMax,hMax)/4.0 );
	}


	///
	/// Number of Layouts Page
	///
	TemplateDesignerNLayoutsPage::TemplateDesignerNLayoutsPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Number of Layouts") );
		setSubTitle( tr("Please select the number of layouts required.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		registerField( "nLayouts.one", oneLayoutRadio );
		registerField( "nLayouts.two", twoLayoutsRadio );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	///
	/// One Layout Page
	///
	TemplateDesignerOneLayoutPage::TemplateDesignerOneLayoutPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Layout") );
		setSubTitle( tr("Please enter parameters for your single layout.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		x0Spin->setSuffix( " " + model::Settings::units().toTrName() );
		x0Spin->setDecimals( model::Settings::units().resolutionDigits() );
		x0Spin->setSingleStep( model::Settings::units().resolution() );

		y0Spin->setSuffix( " " + model::Settings::units().toTrName() );
		y0Spin->setDecimals( model::Settings::units().resolutionDigits() );
		y0Spin->setSingleStep( model::Settings::units().resolution() );

		dxSpin->setSuffix( " " + model::Settings::units().toTrName() );
		dxSpin->setDecimals( model::Settings::units().resolutionDigits() );
		dxSpin->setSingleStep( model::Settings::units().resolution() );

		dySpin->setSuffix( " " + model::Settings::units().toTrName() );
		dySpin->setDecimals( model::Settings::units().resolutionDigits() );
		dySpin->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		nxSpin->setValue( 1 );
		nySpin->setValue( 1 );
		x0Spin->setValue( 0 );
		y0Spin->setValue( 0 );

		registerField( "oneLayout.nx", nxSpin );
		registerField( "oneLayout.ny", nySpin );
		registerField( "oneLayout.x0", x0Spin, "value" );
		registerField( "oneLayout.y0", y0Spin, "value" );
		registerField( "oneLayout.dx", dxSpin, "value" );
		registerField( "oneLayout.dy", dySpin, "value" );

		connect( nxSpin, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( nySpin, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( x0Spin, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( y0Spin, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dxSpin, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dySpin, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerOneLayoutPage::initializePage()
	{
		if ( auto td = dynamic_cast<TemplateDesigner*>( wizard() ) )
		{
			// set realistic limits based on previously chosen values
			double pageW = field("pageSize.w").toDouble();
			double pageH = field("pageSize.h").toDouble();
			double w = td->itemWidth();
			double h = td->itemHeight();
			double xWaste = td->itemXWaste();
			double yWaste = td->itemYWaste();

			int nxMax = std::max( pageW/(w + 2*xWaste), 1.0 );
			int nyMax = std::max( pageH/(h + 2*yWaste), 1.0 );

			nxSpin->setMaximum( nxMax );
			nySpin->setMaximum( nyMax );
			x0Spin->setRange( xWaste, pageW-w-xWaste );
			y0Spin->setRange( yWaste, pageH-h-yWaste );
			dxSpin->setRange( w+2*xWaste, pageW-w-2*xWaste );
			dySpin->setRange( h+2*yWaste, pageH-h-2*yWaste );

			preview->setTemplate( td->buildTemplate() );
		}
	}


	void TemplateDesignerOneLayoutPage::onChanged()
	{
		if ( auto td = dynamic_cast<TemplateDesigner*>( wizard() ) )
		{
			preview->setTemplate( td->buildTemplate() );
		}
	}

	
	///
	/// Two Layout Page
	///
	TemplateDesignerTwoLayoutPage::TemplateDesignerTwoLayoutPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Layouts") );
		setSubTitle( tr("Please enter parameters for your two layouts.") );

		QWidget* widget = new QWidget;
		setupUi( widget );

		x0Spin1->setSuffix( " " + model::Settings::units().toTrName() );
		x0Spin1->setDecimals( model::Settings::units().resolutionDigits() );
		x0Spin1->setSingleStep( model::Settings::units().resolution() );

		y0Spin1->setSuffix( " " + model::Settings::units().toTrName() );
		y0Spin1->setDecimals( model::Settings::units().resolutionDigits() );
		y0Spin1->setSingleStep( model::Settings::units().resolution() );

		dxSpin1->setSuffix( " " + model::Settings::units().toTrName() );
		dxSpin1->setDecimals( model::Settings::units().resolutionDigits() );
		dxSpin1->setSingleStep( model::Settings::units().resolution() );

		dySpin1->setSuffix( " " + model::Settings::units().toTrName() );
		dySpin1->setDecimals( model::Settings::units().resolutionDigits() );
		dySpin1->setSingleStep( model::Settings::units().resolution() );

		x0Spin2->setSuffix( " " + model::Settings::units().toTrName() );
		x0Spin2->setDecimals( model::Settings::units().resolutionDigits() );
		x0Spin2->setSingleStep( model::Settings::units().resolution() );

		y0Spin2->setSuffix( " " + model::Settings::units().toTrName() );
		y0Spin2->setDecimals( model::Settings::units().resolutionDigits() );
		y0Spin2->setSingleStep( model::Settings::units().resolution() );

		dxSpin2->setSuffix( " " + model::Settings::units().toTrName() );
		dxSpin2->setDecimals( model::Settings::units().resolutionDigits() );
		dxSpin2->setSingleStep( model::Settings::units().resolution() );

		dySpin2->setSuffix( " " + model::Settings::units().toTrName() );
		dySpin2->setDecimals( model::Settings::units().resolutionDigits() );
		dySpin2->setSingleStep( model::Settings::units().resolution() );

		// Set some realistic defaults
		nxSpin1->setValue( 1 );
		nySpin1->setValue( 1 );
		x0Spin1->setValue( 0 );
		y0Spin1->setValue( 0 );

		nxSpin2->setValue( 1 );
		nySpin2->setValue( 1 );
		x0Spin2->setValue( 0 );
		y0Spin2->setValue( 0 );

		registerField( "twoLayout.nx1", nxSpin1 );
		registerField( "twoLayout.ny1", nySpin1 );
		registerField( "twoLayout.x01", x0Spin1, "value" );
		registerField( "twoLayout.y01", y0Spin1, "value" );
		registerField( "twoLayout.dx1", dxSpin1, "value" );
		registerField( "twoLayout.dy1", dySpin1, "value" );

		registerField( "twoLayout.nx2", nxSpin2 );
		registerField( "twoLayout.ny2", nySpin2 );
		registerField( "twoLayout.x02", x0Spin2, "value" );
		registerField( "twoLayout.y02", y0Spin2, "value" );
		registerField( "twoLayout.dx2", dxSpin2, "value" );
		registerField( "twoLayout.dy2", dySpin2, "value" );

		connect( nxSpin1, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( nySpin1, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( x0Spin1, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( y0Spin1, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dxSpin1, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dySpin1, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );

		connect( nxSpin2, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( nySpin2, SIGNAL(valueChanged(int)), this, SLOT(onChanged()) );
		connect( x0Spin2, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( y0Spin2, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dxSpin2, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );
		connect( dySpin2, SIGNAL(valueChanged(double)), this, SLOT(onChanged()) );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

	void TemplateDesignerTwoLayoutPage::initializePage()
	{
		if ( auto td = dynamic_cast<TemplateDesigner*>( wizard() ) )
		{
			// set realistic limits based on previously chosen values
			double pageW = field("pageSize.w").toDouble();
			double pageH = field("pageSize.h").toDouble();
			double w = td->itemWidth();
			double h = td->itemHeight();
			double xWaste = td->itemXWaste();
			double yWaste = td->itemYWaste();

			int nxMax = std::max( pageW/(w + 2*xWaste), 1.0 );
			int nyMax = std::max( pageH/(h + 2*yWaste), 1.0 );

			nxSpin1->setMaximum( nxMax );
			nySpin1->setMaximum( nyMax );
			x0Spin1->setRange( xWaste, pageW-w-xWaste );
			y0Spin1->setRange( yWaste, pageH-h-yWaste );
			dxSpin1->setRange( w+2*xWaste, pageW-w-2*xWaste );
			dySpin1->setRange( h+2*yWaste, pageH-h-2*yWaste );

			nxSpin2->setMaximum( nxMax );
			nySpin2->setMaximum( nyMax );
			x0Spin2->setRange( xWaste, pageW-w-xWaste );
			y0Spin2->setRange( yWaste, pageH-h-yWaste );
			dxSpin2->setRange( w+2*xWaste, pageW-w-2*xWaste );
			dySpin2->setRange( h+2*yWaste, pageH-h-2*yWaste );

			preview->setTemplate( td->buildTemplate() );
		}
	}


	void TemplateDesignerTwoLayoutPage::onChanged()
	{
		if ( auto td = dynamic_cast<TemplateDesigner*>( wizard() ) )
		{
			preview->setTemplate( td->buildTemplate() );
		}
	}

	
	///
	/// Apply Page
	///
	TemplateDesignerApplyPage::TemplateDesignerApplyPage( QWidget* parent ) : QWizardPage(parent)
	{
		setTitle( tr("Save Product Template") );
		setSubTitle( tr("Click \"Save\" to save your custom product template!") );

		setFinalPage( true );
		setButtonText( QWizard::FinishButton, "Save" );

		QWidget* widget = new QWidget;
		setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
	}
	

} // namespace glabels
