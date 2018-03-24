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
			if ( mShapePage->rectRadio->isChecked() )
			{
				return RectPageId;
			}
			else if ( mShapePage->roundRadio->isChecked() )
			{
				return RoundPageId;
			}
			else if ( mShapePage->ellipseRadio->isChecked() )
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
			if ( mNLayoutsPage->oneLayoutRadio->isChecked() )
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
		auto t = new model::Template( mNamePage->brandEntry->text(),
		                              mNamePage->partEntry->text(),
		                              mNamePage->descriptionEntry->text(),
		                              mPageSizePage->pageSizeCombo->currentText(), // FIXME
		                              mPageSizePage->wSpin->value(),
		                              mPageSizePage->hSpin->value() );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget( widget );
		setLayout( layout );
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
