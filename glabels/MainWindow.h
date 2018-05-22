/*  MainWindow.h
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

#ifndef MainWindow_h
#define MainWindow_h

#include <model/Model.h>

#include <QAction>
#include <QCloseEvent>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QStackedWidget>
#include <QToolBar>


namespace glabels
{

	// Forward References
	class LabelEditor;
	class MergeView;
	class ObjectEditor;
	class PrintView;
	class PropertiesView;
	class StartupView;
	class UndoRedoModel;


	///
	/// MainWindow Widget
	///
	class MainWindow : public QMainWindow
	{
		Q_OBJECT


		/////////////////////////////////////
		// Lifecycle
		/////////////////////////////////////
	public:
		MainWindow();
		~MainWindow() override;


		/////////////////////////////////////
		// Public Methods
		/////////////////////////////////////
	public:
		model::Model* model() const;
		void setModel( model::Model* model );
		bool isEmpty() const;


		/////////////////////////////////////
		// Events
		/////////////////////////////////////
	protected:
		void closeEvent( QCloseEvent *event ) override;


		/////////////////////////////////////
		// Slots
		/////////////////////////////////////
	private slots:
		void changePage(QListWidgetItem *current, QListWidgetItem *previous);

		void clipboardChanged();

		void fileNew();
		void fileOpen();
		void fileSave();
		void fileSaveAs();
		void fileShowEditorPage();
		void fileShowPropertiesPage();
		void fileShowMergePage();
		void fileShowPrintPage();
		void fileTemplateDesigner();
		void fileClose();
		void fileExit();

		void editUndo();
		void editRedo();
		void editCut();
		void editCopy();
		void editPaste();
		void editDelete();
		void editSelectAll();
		void editUnSelectAll();
		void editPreferences();

		void viewFileToolBar( bool );
		void viewEditorToolBar( bool );
		void viewGrid( bool );
		void viewMarkup( bool );
		void viewZoomIn();
		void viewZoomOut();
		void viewZoom1To1();
		void viewZoomToFit();

		void objectsArrowMode();
		void objectsCreateText();
		void objectsCreateBox();
		void objectsCreateLine();
		void objectsCreateEllipse();
		void objectsCreateImage();
		void objectsCreateBarcode();
		void objectsOrderRaise();
		void objectsOrderLower();
		void objectsXformRotateLeft();
		void objectsXformRotateRight();
		void objectsXformFlipHoriz();
		void objectsXformFlipVert();
		void objectsAlignLeft();
		void objectsAlignHCenter();
		void objectsAlignRight();
		void objectsAlignTop();
		void objectsAlignVCenter();
		void objectsAlignBottom();
		void objectsCenterHoriz();
		void objectsCenterVert();

		void helpContents();
		void helpAbout();

		void onContextMenuActivate();

		void onZoomChanged();
		void onPointerMoved( double, double );
		void onPointerExit();

		void onNameChanged();
		void onModifiedChanged();
		void onSelectionChanged();
		void onLabelChanged();
		void onUndoRedoChanged();


		/////////////////////////////////////
		// Internal Private Methods
		/////////////////////////////////////
	private:
		void createActions();
		void createMenus();
		void createToolBars();
		void createStatusBar();

		QWidget* createWelcomePage();
		QWidget* createPropertiesPage();
		QWidget* createEditorPage();
		QWidget* createMergePage();
		QWidget* createPrintPage();

		void setWelcomeMode( bool );
		void setDocVerbsEnabled( bool );
		void setDocModifiedVerbsEnabled( bool );
		void setPasteVerbsEnabled( bool );
		void setSelectionVerbsEnabled( bool );
		void setMultiSelectionVerbsEnabled( bool );

		void setTitle();

		void readSettings();
		void writeSettings();

		bool isOkToClose();
	

		/////////////////////////////////////
		// Private Data
		/////////////////////////////////////
	private:
		QMenu*    fileMenu;
		QMenu*    editMenu;
		QMenu*    viewMenu;
		QMenu*    viewToolBarsMenu;
		QMenu*    objectsMenu;
		QMenu*    objectsCreateMenu;
		QMenu*    objectsOrderMenu;
		QMenu*    objectsXformMenu;
		QMenu*    objectsAlignMenu;
		QMenu*    objectsCenterMenu;
		QMenu*    helpMenu;

		QMenu*    contextMenu;
		QMenu*    contextOrderMenu;
		QMenu*    contextXformMenu;
		QMenu*    contextAlignMenu;
		QMenu*    contextCenterMenu;
		QMenu*    noSelectionContextMenu;
		
		QToolBar* fileToolBar;
		QToolBar* editorToolBar;

		model::Model*        mModel;
		UndoRedoModel*       mUndoRedoModel;

		QListWidget*         mContents;
		QListWidgetItem*     mWelcomeButton;
		QListWidgetItem*     mPropertiesButton;
		QListWidgetItem*     mEditorButton;
		QListWidgetItem*     mMergeButton;
		QListWidgetItem*     mPrintButton;

		QStackedWidget*      mPages;
		StartupView*         mWelcomeView;
		PropertiesView*      mPropertiesView;
		QScrollArea*         mLabelEditorScrollArea;
		LabelEditor*         mLabelEditor;
		ObjectEditor*        mObjectEditor;
		MergeView*           mMergeView;
		PrintView*           mPrintView;

		QLabel*   zoomInfoLabel;
		QLabel*   cursorInfoLabel;

		QAction*  fileNewAction;
		QAction*  fileOpenAction;
		QAction*  fileSaveAction;
		QAction*  fileSaveAsAction;
		QAction*  fileShowEditorPageAction;
		QAction*  fileShowPropertiesPageAction;
		QAction*  fileShowMergePageAction;
		QAction*  fileShowPrintPageAction;
		QAction*  fileTemplateDesignerAction;
		QAction*  fileCloseAction;
		QAction*  fileExitAction;

		QAction*  editUndoAction;
		QAction*  editRedoAction;
		QAction*  editCutAction;
		QAction*  editCopyAction;
		QAction*  editPasteAction;
		QAction*  editDeleteAction;
		QAction*  editSelectAllAction;
		QAction*  editUnSelectAllAction;
		QAction*  editPreferencesAction;

		QAction*  viewFileToolBarAction;
		QAction*  viewEditorToolBarAction;
		QAction*  viewGridAction;
		QAction*  viewMarkupAction;
		QAction*  viewZoomInAction;
		QAction*  viewZoomOutAction;
		QAction*  viewZoom1To1Action;
		QAction*  viewZoomToFitAction;

		QAction*  objectsArrowModeAction;
		QAction*  objectsCreateTextAction;
		QAction*  objectsCreateBoxAction;
		QAction*  objectsCreateLineAction;
		QAction*  objectsCreateEllipseAction;
		QAction*  objectsCreateImageAction;
		QAction*  objectsCreateBarcodeAction;
		QAction*  objectsOrderRaiseAction;
		QAction*  objectsOrderLowerAction;
		QAction*  objectsXformRotateLeftAction;
		QAction*  objectsXformRotateRightAction;
		QAction*  objectsXformFlipHorizAction;
		QAction*  objectsXformFlipVertAction;
		QAction*  objectsAlignLeftAction;
		QAction*  objectsAlignHCenterAction;
		QAction*  objectsAlignRightAction;
		QAction*  objectsAlignTopAction;
		QAction*  objectsAlignVCenterAction;
		QAction*  objectsAlignBottomAction;
		QAction*  objectsCenterHorizAction;
		QAction*  objectsCenterVertAction;

		QAction*  helpContentsAction;
		QAction*  helpAboutAction;

		QAction*  contextCutAction;
		QAction*  contextCopyAction;
		QAction*  contextPasteAction;
		QAction*  contextDeleteAction;
	};


}


#endif // MainWindow_h
