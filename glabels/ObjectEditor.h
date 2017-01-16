/*  ObjectEditor.h
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#ifndef ObjectEditor_h
#define ObjectEditor_h


#include <QButtonGroup>

#include "ui_ObjectEditor.h"

#include "Distance.h"


namespace glabels
{

	// Forward references
	class LabelModel;
	class LabelModelObject;
	class UndoRedoModel;
	

	///
	/// Object Editor Widget
	///
	class ObjectEditor : public QWidget, public Ui_ObjectEditor
	{
		Q_OBJECT

		
		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		ObjectEditor( QWidget *parent = 0 );


		/////////////////////////////////
		// Public methods
		/////////////////////////////////
		void setModel( LabelModel* model, UndoRedoModel* undoRedoModel );


		/////////////////////////////////
		// Private methods
		/////////////////////////////////
	private:
		void hidePages();
		void loadImagePage();
		void loadLineFillPage();
		void loadPositionPage();
		void loadRectSizePage();
		void loadLineSizePage();
		void loadTextPage();
		void loadShadowPage();


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onSettingsChanged();
		void onLabelSizeChanged();
		void onSelectionChanged();
		void onMergeSourceChanged();
		void onObjectChanged();
		void onObjectMoved();
		void onObjectDestroyed();
		void onLineControlsChanged();
		void onFillControlsChanged();
		void onImageFileButtonClicked();
		void onImageKeySelected( QString key );
		void onPositionControlsChanged();
		void onRectSizeControlsChanged();
		void onLineSizeControlsChanged();
		void onTextControlsChanged();
		void onTextInsertFieldKeySelected( QString key );
		void onResetImageSize();
		void onShadowControlsChanged();
		void onChanged();
		

		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		LabelModel*              mModel;
		LabelModelObject*        mObject;
		UndoRedoModel*           mUndoRedoModel;
	
		Units                    mUnits;
		int                      mSpinDigits;
		double                   mSpinStep;
	
		QButtonGroup*            textHAlignGroup;
		QButtonGroup*            textVAlignGroup;

		QString                  mImageCwd;

		bool                     mBlocked;

	};

}


#endif // ObjectEditor_h
