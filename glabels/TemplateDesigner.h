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
		
		QWizardPage* createIntroPage();
		QWizardPage* createNamePage();
		QWizardPage* createPageSizePage();
		QWizardPage* createShapePage();
		QWizardPage* createRectPage();
		QWizardPage* createRoundPage();
		QWizardPage* createEllipsePage();
		QWizardPage* createCdPage();
		QWizardPage* createNLayoutsPage();
		QWizardPage* createOneLayoutPage();
		QWizardPage* createTwoLayoutPage();
		QWizardPage* createApplyPage();

		model::Template* buildTemplate();


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onNamePageChanged();
		void onPageSizeComboChanged();


		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		Ui::TemplateDesignerIntroPage     mIntroPage;
		Ui::TemplateDesignerNamePage      mNamePage;
		Ui::TemplateDesignerPageSizePage  mPageSizePage;
		Ui::TemplateDesignerShapePage     mShapePage;
		Ui::TemplateDesignerRectPage      mRectPage;
		Ui::TemplateDesignerRoundPage     mRoundPage;
		Ui::TemplateDesignerEllipsePage   mEllipsePage;
		Ui::TemplateDesignerCdPage        mCdPage;
		Ui::TemplateDesignerNLayoutsPage  mNLayoutsPage;
		Ui::TemplateDesignerOneLayoutPage mOneLayoutPage;
		Ui::TemplateDesignerTwoLayoutPage mTwoLayoutPage;
		Ui::TemplateDesignerApplyPage     mApplyPage;
		
	};

}


#endif // TemplateDesigner_h
