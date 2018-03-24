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

		setPage( IntroPageId,     mIntroPage     = new TemplateDesignerIntroPage() );
		setPage( NamePageId,      mNamePage      = new TemplateDesignerNamePage() );
		setPage( PageSizePageId,  mPageSizePage  = new TemplateDesignerPageSizePage() );
		setPage( ShapePageId,     mShapePage     = new TemplateDesignerShapePage() );
		setPage( RectPageId,      mRectPage      = new TemplateDesignerRectPage() );
		setPage( RoundPageId,     mRoundPage     = new TemplateDesignerRoundPage() );
		setPage( EllipsePageId,   mEllipsePage   = new TemplateDesignerEllipsePage() );
		setPage( CdPageId,        mCdPage        = new TemplateDesignerCdPage() );
		setPage( NLayoutsPageId,  mNLayoutsPage  = new TemplateDesignerNLayoutsPage() );
		setPage( OneLayoutPageId, mOneLayoutPage = new TemplateDesignerOneLayoutPage() );
		setPage( TwoLayoutPageId, mTwoLayoutPage = new TemplateDesignerTwoLayoutPage() );
		setPage( ApplyPageId,     mApplyPage     = new TemplateDesignerApplyPage() );
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
	/// Build template from wizard pages
	///
	model::Template* TemplateDesigner::buildTemplate()
	{
		auto t = new model::Template( field( "name.brand" ).toString(),
		                              field( "name.part" ).toString(),
		                              field( "name.description" ).toString(),
		                              field( "pageSize.pageSize" ).toString(), // FIXME Id
		                              field( "pageSize.w" ).toDouble(), // FIXME Distance
		                              field( "pageSize.h" ).toDouble() );
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

		registerField( "pageSize.pageSize", pageSizeCombo );
		registerField( "pageSize.w",        wSpin, "value" );
		registerField( "pageSize.h",        hSpin, "value" );

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

		registerField( "cd.w",      r1Spin,     "value" );
		registerField( "cd.h",      r2Spin,     "value" );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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
