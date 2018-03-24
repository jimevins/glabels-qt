/*  TemplateDesigner.h
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

#ifndef TemplateDesigner_h
#define TemplateDesigner_h


#include "ui_TemplateDesignerIntroPage.h"
#include "ui_TemplateDesignerNamePage.h"
#include "ui_TemplateDesignerPageSizePage.h"
#include "ui_TemplateDesignerShapePage.h"
#include "ui_TemplateDesignerRectPage.h"
#include "ui_TemplateDesignerRoundPage.h"
#include "ui_TemplateDesignerEllipsePage.h"
#include "ui_TemplateDesignerCdPage.h"
#include "ui_TemplateDesignerNLayoutsPage.h"
#include "ui_TemplateDesignerOneLayoutPage.h"
#include "ui_TemplateDesignerTwoLayoutPage.h"
#include "ui_TemplateDesignerApplyPage.h"

#include "model/Template.h"

#include <QWizard>
#include <QWizardPage>


namespace glabels
{
	// Forward references
	class TemplateDesignerIntroPage;
	class TemplateDesignerNamePage;
	class TemplateDesignerPageSizePage;
	class TemplateDesignerShapePage;
	class TemplateDesignerRectPage;
	class TemplateDesignerRoundPage;
	class TemplateDesignerEllipsePage;
	class TemplateDesignerCdPage;
	class TemplateDesignerNLayoutsPage;
	class TemplateDesignerOneLayoutPage;
	class TemplateDesignerTwoLayoutPage;
	class TemplateDesignerApplyPage;
	
	
	///
	/// About Dialog Widget
	///
	class TemplateDesigner : public QWizard
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		TemplateDesigner( QWidget *parent = nullptr );


		/////////////////////////////////
		// Private methods
		/////////////////////////////////
	private:
		int nextId() const override;
		
		model::Template* buildTemplate();


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:


		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		TemplateDesignerIntroPage*     mIntroPage;
		TemplateDesignerNamePage*      mNamePage;
		TemplateDesignerPageSizePage*  mPageSizePage;
		TemplateDesignerShapePage*     mShapePage;
		TemplateDesignerRectPage*      mRectPage;
		TemplateDesignerRoundPage*     mRoundPage;
		TemplateDesignerEllipsePage*   mEllipsePage;
		TemplateDesignerCdPage*        mCdPage;
		TemplateDesignerNLayoutsPage*  mNLayoutsPage;
		TemplateDesignerOneLayoutPage* mOneLayoutPage;
		TemplateDesignerTwoLayoutPage* mTwoLayoutPage;
		TemplateDesignerApplyPage*     mApplyPage;

	};


	//
	// Intro Page
	//
	class TemplateDesignerIntroPage : public QWizardPage, public Ui::TemplateDesignerIntroPage
	{
		Q_OBJECT
	public:
		TemplateDesignerIntroPage( QWidget* parent = nullptr );
	};


	//
	// Name Page
	//
	class TemplateDesignerNamePage : public QWizardPage, public Ui::TemplateDesignerNamePage
	{
		Q_OBJECT
	public:
		TemplateDesignerNamePage( QWidget* parent = nullptr );

		bool isComplete() const override;

	private slots:
		void onChanged();

	private:
		bool mCanContinue = false;
	};


	//
	// Page Size Page
	//
	class TemplateDesignerPageSizePage : public QWizardPage, public Ui::TemplateDesignerPageSizePage
	{
		Q_OBJECT
	public:
		TemplateDesignerPageSizePage( QWidget* parent = nullptr );

	private slots:
		void onComboChanged();

	};


	//
	// Shape Page
	//
	class TemplateDesignerShapePage : public QWizardPage, public Ui::TemplateDesignerShapePage
	{
		Q_OBJECT
	public:
		TemplateDesignerShapePage( QWidget* parent = nullptr );
	};


	//
	// Rect Page
	//
	class TemplateDesignerRectPage : public QWizardPage, public Ui::TemplateDesignerRectPage
	{
		Q_OBJECT
	public:
		TemplateDesignerRectPage( QWidget* parent = nullptr );

		void initializePage() override;
	};


	//
	// Round Page
	//
	class TemplateDesignerRoundPage : public QWizardPage, public Ui::TemplateDesignerRoundPage
	{
		Q_OBJECT
	public:
		TemplateDesignerRoundPage( QWidget* parent = nullptr );

		void initializePage() override;
	};


	//
	// Ellipse Page
	//
	class TemplateDesignerEllipsePage : public QWizardPage, public Ui::TemplateDesignerEllipsePage
	{
		Q_OBJECT
	public:
		TemplateDesignerEllipsePage( QWidget* parent = nullptr );

		void initializePage() override;
	};


	//
	// Cd Page
	//
	class TemplateDesignerCdPage : public QWizardPage, public Ui::TemplateDesignerCdPage
	{
		Q_OBJECT
	public:
		TemplateDesignerCdPage( QWidget* parent = nullptr );

		void initializePage() override;
	};


	//
	// NLayouts Page
	//
	class TemplateDesignerNLayoutsPage : public QWizardPage, public Ui::TemplateDesignerNLayoutsPage
	{
		Q_OBJECT
	public:
		TemplateDesignerNLayoutsPage( QWidget* parent = nullptr );
	};


	//
	// OneLayout Page
	//
	class TemplateDesignerOneLayoutPage : public QWizardPage, public Ui::TemplateDesignerOneLayoutPage
	{
		Q_OBJECT
	public:
		TemplateDesignerOneLayoutPage( QWidget* parent = nullptr );
	};


	//
	// TwoLayout Page
	//
	class TemplateDesignerTwoLayoutPage : public QWizardPage, public Ui::TemplateDesignerTwoLayoutPage
	{
		Q_OBJECT
	public:
		TemplateDesignerTwoLayoutPage( QWidget* parent = nullptr );
	};


	//
	// Apply Page
	//
	class TemplateDesignerApplyPage : public QWizardPage, public Ui::TemplateDesignerApplyPage
	{
		Q_OBJECT
	public:
		TemplateDesignerApplyPage( QWidget* parent = nullptr );
	};


}


#endif // TemplateDesigner_h
