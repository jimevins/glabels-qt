/*  MainWindow.h
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

#ifndef glabels_MainWindow_h
#define glabels_MainWindow_h

#include <QMainWindow>
#include <QAction>
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>


namespace gLabels
{

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow();


	protected:
		void closeEvent( QCloseEvent *event );


	private slots:
		void fileNew();
		void fileOpen();
		void fileSave();
		void fileSaveAs();
		void filePrint();
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
		void viewObjectsToolBar( bool );
		void viewEditToolBar( bool );
		void viewViewToolBar( bool );
		void viewGrid();
		void viewMarkup();
		void viewZoomIn();
		void viewZoomOut();
		void viewZoom1to1();
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
		void objectsMergeProperties();

		void helpContents();
		void helpAbout();


	private:
		void createActions();
		void createMenus();
		void createToolBars();

		void setDocVerbsEnabled( bool );
		void setDocModifiedVerbsEnabled( bool );
		void setPasteVerbsEnabled( bool );
		void setSelectionVerbsEnabled( bool );
		void setMultiSelectionVerbsEnabled( bool );

		void readSettings();
		void writeSettings();

		QMenu   *fileMenu;
		QMenu   *editMenu;
		QMenu   *viewMenu;
		QMenu   *viewToolBarsMenu;
		QMenu   *objectsMenu;
		QMenu   *objectsCreateMenu;
		QMenu   *objectsOrderMenu;
		QMenu   *objectsXformMenu;
		QMenu   *objectsAlignMenu;
		QMenu   *objectsCenterMenu;
		QMenu   *helpMenu;

		QToolBar *fileToolBar;
		QToolBar *objectsToolBar;
		QToolBar *editToolBar;
		QToolBar *viewToolBar;

		QAction *fileNewAction;
		QAction *fileOpenAction;
		QAction *fileSaveAction;
		QAction *fileSaveAsAction;
		QAction *filePrintAction;
		QAction *filePropertiesAction;
		QAction *fileTemplateDesignerAction;
		QAction *fileCloseAction;
		QAction *fileExitAction;

		QAction *editUndoAction;
		QAction *editRedoAction;
		QAction *editCutAction;
		QAction *editCopyAction;
		QAction *editPasteAction;
		QAction *editDeleteAction;
		QAction *editSelectAllAction;
		QAction *editUnSelectAllAction;
		QAction *editPreferencesAction;

		QAction *viewFileToolBarAction;
		QAction *viewObjectsToolBarAction;
		QAction *viewEditToolBarAction;
		QAction *viewViewToolBarAction;
		QAction *viewGridAction;
		QAction *viewMarkupAction;
		QAction *viewZoomInAction;
		QAction *viewZoomOutAction;
		QAction *viewZoom1to1Action;
		QAction *viewZoomToFitAction;

		QAction *objectsArrowModeAction;
		QAction *objectsCreateTextAction;
		QAction *objectsCreateBoxAction;
		QAction *objectsCreateLineAction;
		QAction *objectsCreateEllipseAction;
		QAction *objectsCreateImageAction;
		QAction *objectsCreateBarcodeAction;
		QAction *objectsOrderRaiseAction;
		QAction *objectsOrderLowerAction;
		QAction *objectsXformRotateLeftAction;
		QAction *objectsXformRotateRightAction;
		QAction *objectsXformFlipHorizAction;
		QAction *objectsXformFlipVertAction;
		QAction *objectsAlignLeftAction;
		QAction *objectsAlignHCenterAction;
		QAction *objectsAlignRightAction;
		QAction *objectsAlignTopAction;
		QAction *objectsAlignVCenterAction;
		QAction *objectsAlignBottomAction;
		QAction *objectsCenterHorizAction;
		QAction *objectsCenterVertAction;
		QAction *objectsMergePropertiesAction;

		QAction *helpContentsAction;
		QAction *helpAboutAction;

	};

}

#endif // glabels_MainWindow_h
