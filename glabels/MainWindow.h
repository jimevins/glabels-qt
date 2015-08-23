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

#ifndef glabels_MainWindow_h
#define glabels_MainWindow_h

#include <QMainWindow>

class QAction;
class QCloseEvent;
class QMenuBar;
class QMenu;
class QToolBar;
class QLabel;
class QScrollArea;


namespace glabels
{
	// Forward References
	class LabelModel;
	class View;
	class ObjectEditor;
	class PrintView;


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
		virtual ~MainWindow();


		/////////////////////////////////////
		// Public Methods
		/////////////////////////////////////
	public:
		LabelModel* model() const;
		void setModel( LabelModel* label );
		bool isEmpty() const;

		static QList<MainWindow *> windowList();


		/////////////////////////////////////
		// Events
		/////////////////////////////////////
	protected:
		void closeEvent( QCloseEvent *event );


		/////////////////////////////////////
		// Slots
		/////////////////////////////////////
	private slots:
		void fileNew();
		void fileOpen();
		void fileSave();
		void fileSaveAs();
		void fileProperties();
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

		void onZoomChanged();
		void onPointerMoved( double, double );
		void onPointerExit();

		void onNameChanged();
		void onModifiedChanged();
		void onSelectionChanged();
		void onLabelChanged();


		/////////////////////////////////////
		// Internal Private Methods
		/////////////////////////////////////
	private:
		void createActions();
		void createMenus();
		void createToolBars();
		void createStatusBar();

		QWidget* createEditorPage();
		QWidget* createMergePage();
		QWidget* createPrintPage();

		void setDocVerbsEnabled( bool );
		void setDocModifiedVerbsEnabled( bool );
		void setPasteVerbsEnabled( bool );
		void setSelectionVerbsEnabled( bool );
		void setMultiSelectionVerbsEnabled( bool );

		void setTitle();

		void readSettings();
		void writeSettings();


		/////////////////////////////////////
		// Private Data
		/////////////////////////////////////
	private:
		static    QList<MainWindow*> smWindowList;

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

		QToolBar* fileToolBar;
		QToolBar* editorToolBar;

		QTabWidget*   mNotebook;
		LabelModel*   mModel;
		QScrollArea*  mViewScrollArea;
		View*         mView;
		ObjectEditor* mObjectEditor;
		PrintView*    mPrintView;

		QLabel*   zoomInfoLabel;
		QLabel*   cursorInfoLabel;

		QAction*  fileNewAction;
		QAction*  fileOpenAction;
		QAction*  fileSaveAction;
		QAction*  fileSaveAsAction;
		QAction*  filePropertiesAction;
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

	};

}

#endif // glabels_MainWindow_h
