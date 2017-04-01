/*  PrintView.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#ifndef PrintView_h
#define PrintView_h


#include "ui_PrintView.h"

#include "PageRenderer.h"

#include <QPrinter>


namespace glabels
{

	// Forward references
	class LabelModel;
	

	///
	/// Print View Widget
	///
	class PrintView : public QWidget, public Ui_PrintView
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		PrintView( QWidget *parent = nullptr );
		~PrintView() override;


		/////////////////////////////////
		// Public methods
		/////////////////////////////////
		void setModel( LabelModel* model );


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onModelChanged();
		void updateView();
		void onFormChanged();
		void onPrintButtonClicked();


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		LabelModel*  mModel;
		QPrinter*    mPrinter;
		PageRenderer mRenderer;

		bool         mBlocked;

	};

}


#endif // PrintView_h
