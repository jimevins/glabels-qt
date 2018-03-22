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

#include <QVBoxLayout>
#include <QtDebug>

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
}


namespace glabels
{

	///
	/// Constructor
	///
	TemplateDesigner::TemplateDesigner( QWidget *parent )
		: QWizard(parent)
	{
		setWindowTitle( tr("Product Template Designer") );
		setPixmap( QWizard::LogoPixmap, QPixmap( ":icons/scalable/apps/glabels.svg" ) );
		setWizardStyle( QWizard::ModernStyle );

		setPage( IntroPageId,     createIntroPage() );
		setPage( NamePageId,      createNamePage() );
		setPage( PageSizePageId,  createPageSizePage() );
		setPage( ShapePageId,     createShapePage() );
		setPage( RectPageId,      createRectPage() );
		setPage( RoundPageId,     createRoundPage() );
		setPage( EllipsePageId,   createEllipsePage() );
		setPage( CdPageId,        createCdPage() );
		setPage( NLayoutsPageId,  createNLayoutsPage() );
		setPage( OneLayoutPageId, createOneLayoutPage() );
		setPage( TwoLayoutPageId, createTwoLayoutPage() );
		setPage( ApplyPageId,     createApplyPage() );
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
			if ( mShapePage.rectRadio->isChecked() )
			{
				return RectPageId;
			}
			else if ( mShapePage.roundRadio->isChecked() )
			{
				return RoundPageId;
			}
			else if ( mShapePage.ellipseRadio->isChecked() )
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
			if ( mNLayoutsPage.oneLayoutRadio->isChecked() )
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
	/// Intro Page
	///
	QWizardPage* TemplateDesigner::createIntroPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Welcome") );
		page->setSubTitle( tr("Welcome to the gLabels Product Template Designer.") );
		page->setPixmap( QWizard::WatermarkPixmap, QPixmap( ":images/TemplateDesigner/wizard-banner.png" ) );

		QWidget* widget = new QWidget;
		mIntroPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}


	///
	/// Name and Description Page
	///
	QWizardPage* TemplateDesigner::createNamePage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Name and Description") );
		page->setSubTitle( tr("Please enter the following identifying information about the product.") );

		QWidget* widget = new QWidget;
		mNamePage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Page Size Page
	///
	QWizardPage* TemplateDesigner::createPageSizePage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Page Size") );
		page->setSubTitle( tr("Please select the product page size.") );

		QWidget* widget = new QWidget;
		mPageSizePage.setupUi( widget );

		mPageSizePage.pageSizeCombo->insertItem( 0, tr("Other") );
		mPageSizePage.pageSizeCombo->insertItems( 1, model::Db::paperNames() );
		mPageSizePage.pageSizeCombo->setCurrentText( defaultPageSize[ model::Settings::preferedPageSizeFamily() ] );
		
		mPageSizePage.wSpin->setSuffix( " " + model::Settings::units().toTrName() );
		mPageSizePage.wSpin->setDecimals( model::Settings::units().resolutionDigits() );
		mPageSizePage.wSpin->setSingleStep( model::Settings::units().resolution() );
		mPageSizePage.wSpin->setMaximum( maxPageSize[ model::Settings::units().toEnum() ] );
		mPageSizePage.wSpin->setEnabled( mPageSizePage.pageSizeCombo->currentText() == tr("Other") );
		
		mPageSizePage.hSpin->setSuffix( " " + model::Settings::units().toTrName() );
		mPageSizePage.hSpin->setDecimals( model::Settings::units().resolutionDigits() );
		mPageSizePage.hSpin->setSingleStep( model::Settings::units().resolution() );
		mPageSizePage.hSpin->setMaximum( maxPageSize[ model::Settings::units().toEnum() ] );
		mPageSizePage.hSpin->setEnabled( mPageSizePage.pageSizeCombo->currentText() == tr("Other") );

		connect( mPageSizePage.pageSizeCombo, &QComboBox::currentTextChanged, this, &TemplateDesigner::onPageSizeComboChanged );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Shape Page
	///
	QWizardPage* TemplateDesigner::createShapePage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Product Shape") );
		page->setSubTitle( tr("Please select the basic product shape.") );

		QWidget* widget = new QWidget;
		mShapePage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Rectangular Product Page
	///
	QWizardPage* TemplateDesigner::createRectPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Product Size") );
		page->setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		mRectPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Round Product Page
	///
	QWizardPage* TemplateDesigner::createRoundPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Product Size") );
		page->setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		mRoundPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Elliptical Product Page
	///
	QWizardPage* TemplateDesigner::createEllipsePage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Product Size") );
		page->setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		mEllipsePage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// CD/DVD Product Page
	///
	QWizardPage* TemplateDesigner::createCdPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Product Size") );
		page->setSubTitle( tr("Please adjust the size parameters of a single product item.") );

		QWidget* widget = new QWidget;
		mCdPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Number of Layouts Page
	///
	QWizardPage* TemplateDesigner::createNLayoutsPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Number of Layouts") );
		page->setSubTitle( tr("Please select the number of layouts required.") );

		QWidget* widget = new QWidget;
		mNLayoutsPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// One Layout Page
	///
	QWizardPage* TemplateDesigner::createOneLayoutPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Layout") );
		page->setSubTitle( tr("Please enter parameters for your single layout.") );

		QWidget* widget = new QWidget;
		mOneLayoutPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Two Layout Page
	///
	QWizardPage* TemplateDesigner::createTwoLayoutPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Layouts") );
		page->setSubTitle( tr("Please enter parameters for your two layouts.") );

		QWidget* widget = new QWidget;
		mTwoLayoutPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Apply Page
	///
	QWizardPage* TemplateDesigner::createApplyPage()
	{
		QWizardPage* page = new QWizardPage;
		page->setTitle( tr("Save Product Template") );
		page->setSubTitle( tr("Click \"Save\" to save your custom product template!") );

		page->setFinalPage( true );
		page->setButtonText( QWizard::FinishButton, "Save" );

		QWidget* widget = new QWidget;
		mApplyPage.setupUi( widget );

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		page->setLayout( layout );

		return page;
	}
	

	///
	/// Build template from wizard pages
	///
	model::Template* TemplateDesigner::buildTemplate()
	{
		auto t = new model::Template( mNamePage.brandEntry->text(),
		                              mNamePage.partEntry->text(),
		                              mNamePage.descriptionEntry->text(),
		                              mPageSizePage.pageSizeCombo->currentText(), // FIXME
		                              mPageSizePage.wSpin->value(),
		                              mPageSizePage.hSpin->value() );
	}


	///
	/// Handle Page Size Combo Changed
	///
	void TemplateDesigner::onPageSizeComboChanged()
	{
		mPageSizePage.wSpin->setEnabled( mPageSizePage.pageSizeCombo->currentText() == tr("Other") );
		mPageSizePage.hSpin->setEnabled( mPageSizePage.pageSizeCombo->currentText() == tr("Other") );
	}


} // namespace glabels
