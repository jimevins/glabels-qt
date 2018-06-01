/*  MainWindow.cpp
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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

#include "MainWindow.h"

#include "File.h"
#include "Help.h"
#include "Icons.h"
#include "LabelEditor.h"
#include "MergeView.h"
#include "ObjectEditor.h"
#include "PreferencesDialog.h"
#include "PrintView.h"
#include "PropertiesView.h"
#include "StartupView.h"
#include "UndoRedoModel.h"

#include "model/Db.h"
#include "model/Model.h"

#include <QClipboard>
#include <QFrame>
#include <QMessageBox>
#include <QSettings>
#include <QStatusBar>
#include <QtDebug>


namespace glabels
{

	///
	/// Constructor
	///
	MainWindow::MainWindow()
		: mModel(nullptr)
	{
		setWindowIcon( Icons::Glabels() );

		createActions();
		createMenus();
		createToolBars();
		createStatusBar();

		// Build pages
		QWidget* welcomePage = createWelcomePage();
		QWidget* editorPage = createEditorPage();
		QWidget* propertiesPage = createPropertiesPage();
		QWidget* mergePage = createMergePage();
		QWidget* printPage = createPrintPage();

		// Table of contents widget
		mContents = new QListWidget();
		mContents->setViewMode(QListView::ListMode);
		mContents->setMovement(QListView::Static);
		mContents->setSpacing(6);
	
		// Pages widget
		mPages = new QStackedWidget();

		// Add "Welcome" page
		mPages->addWidget( welcomePage );
		mWelcomeButton = new QListWidgetItem(mContents);
		mWelcomeButton->setText(tr("Welcome"));
		mWelcomeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		// Add "Editor" page
		mPages->addWidget( editorPage );
		mEditorButton = new QListWidgetItem(mContents);
		mEditorButton->setText(tr("Edit"));
		mEditorButton->setToolTip( tr("Select <b>Edit</b> mode") );
		mEditorButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		// Add "Properties" page
		mPages->addWidget( propertiesPage );
		mPropertiesButton = new QListWidgetItem(mContents);
		mPropertiesButton->setText(tr("Properties"));
		mPropertiesButton->setToolTip( tr("Select <b>Properties</b> mode") );
		mPropertiesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		// Add "Merge" page
		mPages->addWidget( mergePage );
		mMergeButton = new QListWidgetItem(mContents);
		mMergeButton->setText(tr("Merge"));
		mMergeButton->setToolTip( tr("Select <b>Merge</b> mode") );
		mMergeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		// Add "Print" page
		mPages->addWidget( printPage );
		mPrintButton = new QListWidgetItem(mContents);
		mPrintButton->setText(tr("Print"));
		mPrintButton->setToolTip( tr("Select <b>Print</b> mode") );
		mPrintButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		// Adjust width of list view based on its contents
		mContents->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
		mContents->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
		mContents->setMinimumWidth( mContents->sizeHintForColumn(0) + 24 );
		mContents->setMaximumWidth( mContents->sizeHintForColumn(0) + 24 );

		// Set initial page selection
		mWelcomeButton->setSelected( true );
		mPages->setCurrentIndex(mContents->row(mWelcomeButton));

		// Create central widget
		QWidget *centralWidget = new QWidget();
		auto *hLayout = new QHBoxLayout();
		hLayout->setContentsMargins( 0, 0, 0, 0 );
		hLayout->addWidget( mContents );
		hLayout->addWidget( mPages );
		centralWidget->setLayout( hLayout );
		setCentralWidget( centralWidget );

		setDocVerbsEnabled( false );
		setPasteVerbsEnabled( false );
		setWelcomeMode( true );
		setTitle();

		// Connect
		connect( mContents, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
		         this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
		connect( mLabelEditor, SIGNAL(zoomChanged()), this, SLOT(onZoomChanged()) );
		connect( QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardChanged()) );
#if 0
		connect( mLabelEditor, SIGNAL(pointerMoved(double, double)),
		         this, SLOT(onPointerMoved(double, double)) );
		connect( mLabelEditor, SIGNAL(pointerExited()), this, SLOT(onPointerExit()) );
#endif

		readSettings();
	}


	///
	/// Destructor
	///
	MainWindow::~MainWindow()
	{
		// empty
	}


	///
	/// Get model accessor
	///
	model::Model* MainWindow::model() const
	{
		return mModel;
	}


	///
	/// Set model accessor
	///
	void MainWindow::setModel( model::Model* model )
	{
		mModel = model;
		mUndoRedoModel = new UndoRedoModel( mModel );
	
		mPropertiesView->setModel( mModel, mUndoRedoModel );
		mLabelEditor->setModel( mModel, mUndoRedoModel );
		mObjectEditor->setModel( mModel, mUndoRedoModel );
		mMergeView->setModel( mModel , mUndoRedoModel );
		mPrintView->setModel( mModel );

		mContents->setCurrentItem( mEditorButton );
		mPages->setCurrentIndex(mContents->row(mEditorButton));
	
		setDocVerbsEnabled( true );
		setSelectionVerbsEnabled( false );
		setMultiSelectionVerbsEnabled( false );
		setWelcomeMode( false );
		setTitle();

		connect( mLabelEditor, SIGNAL(contextMenuActivate()), this, SLOT(onContextMenuActivate()) );
		connect( mModel, SIGNAL(nameChanged()), this, SLOT(onNameChanged()) );
		connect( mModel, SIGNAL(modifiedChanged()), this, SLOT(onModifiedChanged()) );
		connect( mModel, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()) );
		connect( mModel, SIGNAL(changed()), this, SLOT(onLabelChanged()) );
		connect( mUndoRedoModel, SIGNAL(changed()), this, SLOT(onUndoRedoChanged()) );
	}


	///
	/// Is window empty?
	///
	bool MainWindow::isEmpty() const
	{
		return mModel == nullptr;
	}


	///
	/// Close Event Handler
	///
	void MainWindow::closeEvent( QCloseEvent *event )
	{
		if ( isOkToClose() )
		{
			writeSettings();
			event->accept();
		}
		else
		{
			event->ignore();
		}
	}


	///
	/// Create Actions
	///
	void MainWindow::createActions()
	{
		/* File actions */
		fileNewAction = new QAction( tr("&New..."), this );
		fileNewAction->setIcon( Icons::FileNew() );
		fileNewAction->setShortcut( QKeySequence::New );
		fileNewAction->setStatusTip( tr("Create a new gLabels project") );
		connect( fileNewAction, SIGNAL(triggered()), this, SLOT(fileNew()) );

		fileOpenAction = new QAction( tr("&Open..."), this );
		fileOpenAction->setIcon( Icons::FileOpen() );
		fileOpenAction->setShortcut( QKeySequence::Open );
		fileOpenAction->setStatusTip( tr("Open an existing gLabels project") );
		connect( fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()) );

		fileSaveAction = new QAction( tr("&Save"), this );
		fileSaveAction->setIcon( Icons::FileSave() );
		fileSaveAction->setShortcut( QKeySequence::Save );
		fileSaveAction->setStatusTip( tr("Save current gLabels project") );
		connect( fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()) );

		fileSaveAsAction = new QAction( tr("Save &As..."), this );
		fileSaveAsAction->setIcon( Icons::FileSaveAs() );
		fileSaveAsAction->setShortcut( QKeySequence::SaveAs );
		fileSaveAsAction->setStatusTip( tr("Save current gLabels project to a different name") );
		connect( fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()) );

		fileShowEditorPageAction = new QAction( tr("&Edit") , this );
		fileShowEditorPageAction->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_1 ) );
		fileShowEditorPageAction->setStatusTip( tr("Select project Edit mode") );
		connect( fileShowEditorPageAction, SIGNAL(triggered()), this, SLOT(fileShowEditorPage()) );

		fileShowPropertiesPageAction = new QAction( tr("P&roperties") , this );
		fileShowPropertiesPageAction->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_2 ) );
		fileShowPropertiesPageAction->setStatusTip( tr("Select project Properties mode") );
		connect( fileShowPropertiesPageAction, SIGNAL(triggered()), this, SLOT(fileShowPropertiesPage()) );

		fileShowMergePageAction = new QAction( tr("&Merge") , this );
		fileShowMergePageAction->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_3 ) );
		fileShowMergePageAction->setStatusTip( tr("Select project Merge mode") );
		connect( fileShowMergePageAction, SIGNAL(triggered()), this, SLOT(fileShowMergePage()) );

		fileShowPrintPageAction = new QAction( tr("&Print") , this );
		fileShowPrintPageAction->setShortcut( QKeySequence::Print );
		fileShowPrintPageAction->setStatusTip( tr("Select project Print mode") );
		connect( fileShowPrintPageAction, SIGNAL(triggered()), this, SLOT(fileShowPrintPage()) );

		fileTemplateDesignerAction = new QAction( tr("Product Template &Designer..."), this );
		fileTemplateDesignerAction->setStatusTip( tr("Create custom templates") );
		connect( fileTemplateDesignerAction, SIGNAL(triggered()), this, SLOT(fileTemplateDesigner()) );

		fileCloseAction = new QAction( tr("&Close"), this );
		fileCloseAction->setIcon( QIcon::fromTheme( "window-close" ) );
		fileCloseAction->setShortcut( QKeySequence::Close );
		fileCloseAction->setStatusTip( tr("Close the current window") );
		connect( fileCloseAction, SIGNAL(triggered()), this, SLOT(fileClose()) );

		fileExitAction = new QAction( tr("E&xit"), this );
		fileExitAction->setIcon( QIcon::fromTheme( "application-exit" ) );
		fileExitAction->setShortcut( QKeySequence::Quit );
		fileExitAction->setStatusTip( tr("Exit glabels") );
		connect( fileExitAction, SIGNAL(triggered()), this, SLOT(fileExit()) );


		/* Edit actions */
		editUndoAction = new QAction( tr("Undo"), this );
		editUndoAction->setIcon( QIcon::fromTheme( "edit-undo" ) );
		editUndoAction->setShortcut( QKeySequence::Undo );
		editUndoAction->setStatusTip( tr("Undo") );
		connect( editUndoAction, SIGNAL(triggered()), this, SLOT(editUndo()) );

		editRedoAction = new QAction( tr("Redo"), this );
		editRedoAction->setIcon( QIcon::fromTheme( "edit-redo" ) );
		editRedoAction->setShortcut( QKeySequence::Redo );
		editRedoAction->setStatusTip( tr("Redo") );
		connect( editRedoAction, SIGNAL(triggered()), this, SLOT(editRedo()) );

		editCutAction = new QAction( tr("Cut"), this );
		editCutAction->setIcon( Icons::EditCut() );
		editCutAction->setShortcut( QKeySequence::Cut );
		editCutAction->setStatusTip( tr("Cut the selection") );
		connect( editCutAction, SIGNAL(triggered()), this, SLOT(editCut()) );

		editCopyAction = new QAction( tr("&Copy"), this );
		editCopyAction->setIcon( Icons::EditCopy() );
		editCopyAction->setShortcut( QKeySequence::Copy );
		editCopyAction->setStatusTip( tr("Copy the selection") );
		connect( editCopyAction, SIGNAL(triggered()), this, SLOT(editCopy()) );

		editPasteAction = new QAction( tr("&Paste"), this );
		editPasteAction->setIcon( Icons::EditPaste() );
		editPasteAction->setShortcut( QKeySequence::Paste );
		editPasteAction->setStatusTip( tr("Paste the clipboard") );
		connect( editPasteAction, SIGNAL(triggered()), this, SLOT(editPaste()) );

		editDeleteAction = new QAction( tr("&Delete"), this );
		editDeleteAction->setIcon( QIcon::fromTheme( "edit-delete" ) );
		editDeleteAction->setShortcut( QKeySequence::Delete );
		editDeleteAction->setStatusTip( tr("Delete the selected objects") );
		connect( editDeleteAction, SIGNAL(triggered()), this, SLOT(editDelete()) );

		editSelectAllAction = new QAction( tr("Select &All"), this );
		editSelectAllAction->setIcon( QIcon::fromTheme( "edit-select-all" ) );
		editSelectAllAction->setShortcut( QKeySequence::SelectAll );
		editSelectAllAction->setStatusTip( tr("Select all objects") );
		connect( editSelectAllAction, SIGNAL(triggered()), this, SLOT(editSelectAll()) );

		editUnSelectAllAction = new QAction( tr("Un-select All"), this );
		editUnSelectAllAction->setIcon( QIcon::fromTheme( "edit-unselect-all" ) );
		editUnSelectAllAction->setStatusTip( tr("Remove all selections") );
		connect( editUnSelectAllAction, SIGNAL(triggered()), this, SLOT(editUnSelectAll()) );

		editPreferencesAction = new QAction( tr("Preferences"), this );
		editPreferencesAction->setIcon( QIcon::fromTheme( "edit-preferences" ) );
		editPreferencesAction->setShortcut( QKeySequence::Preferences );
		editPreferencesAction->setStatusTip( tr("Configure the application") );
		connect( editPreferencesAction, SIGNAL(triggered()), this, SLOT(editPreferences()) );


		/* View actions */
		viewFileToolBarAction = new QAction( tr("File"), this );
		viewFileToolBarAction->setCheckable( true );
		viewFileToolBarAction->setStatusTip( tr("Change visibility of file toolbar in current window") );
		connect( viewFileToolBarAction, SIGNAL(toggled(bool)), this, SLOT(viewFileToolBar(bool)) );

		viewEditorToolBarAction = new QAction( tr("Editor"), this );
		viewEditorToolBarAction->setCheckable( true );
		viewEditorToolBarAction->setStatusTip( tr("Change visibility of editor toolbar in current window") );
		connect( viewEditorToolBarAction, SIGNAL(toggled(bool)), this, SLOT(viewEditorToolBar(bool)) );


		viewGridAction = new QAction( tr("Grid"), this );
		viewGridAction->setCheckable( true );
		viewGridAction->setStatusTip( tr("Change visibility of the grid in current window") );
		connect( viewGridAction, SIGNAL(toggled(bool)), this, SLOT(viewGrid(bool)) );

		viewMarkupAction = new QAction( tr("Markup"), this );
		viewMarkupAction->setCheckable( true );
		viewMarkupAction->setStatusTip( tr("Change visibility of markup lines in current window") );
		connect( viewMarkupAction, SIGNAL(toggled(bool)), this, SLOT(viewMarkup(bool)) );

		viewZoomInAction = new QAction( tr("Zoom &In"), this );
		viewZoomInAction->setIcon( Icons::ZoomIn() );
		viewZoomInAction->setShortcut( QKeySequence::ZoomIn );
		viewZoomInAction->setStatusTip( tr("Increase magnification") );
		connect( viewZoomInAction, SIGNAL(triggered()), this, SLOT(viewZoomIn()) );

		viewZoomOutAction = new QAction( tr("Zoom &Out"), this );
		viewZoomOutAction->setIcon( Icons::ZoomOut() );
		viewZoomOutAction->setShortcut( QKeySequence::ZoomOut );
		viewZoomOutAction->setStatusTip( tr("Decrease magnification") );
		connect( viewZoomOutAction, SIGNAL(triggered()), this, SLOT(viewZoomOut()) );

		viewZoom1To1Action = new QAction( tr("Zoom &1 to 1"), this );
		viewZoom1To1Action->setIcon( Icons::ZoomOriginal() );
		viewZoom1To1Action->setStatusTip( tr("Restore scale to 100%") );
		connect( viewZoom1To1Action, SIGNAL(triggered()), this, SLOT(viewZoom1To1()) );

		viewZoomToFitAction = new QAction( tr("Zoom to &Fit"), this );
		viewZoomToFitAction->setIcon( Icons::ZoomBestFit() );
		viewZoomToFitAction->setStatusTip( tr("Set scale to fit window") );
		connect( viewZoomToFitAction, SIGNAL(triggered()), this, SLOT(viewZoomToFit()) );


		/* Object actions */
		objectsArrowModeAction = new QAction( tr("Select Mode"), this );
		objectsArrowModeAction->setIcon( Icons::Arrow() );
		objectsArrowModeAction->setStatusTip( tr("Select, move and modify objects") );
		connect( objectsArrowModeAction, SIGNAL(triggered()), this, SLOT(objectsArrowMode()) );

		objectsCreateTextAction = new QAction( tr("Text"), this );
		objectsCreateTextAction->setIcon( Icons::Text() );
		objectsCreateTextAction->setStatusTip( tr("Create text object") );
		connect( objectsCreateTextAction, SIGNAL(triggered()), this, SLOT(objectsCreateText()) );

		objectsCreateBoxAction = new QAction( tr("Box"), this );
		objectsCreateBoxAction->setIcon( Icons::Box() );
		objectsCreateBoxAction->setStatusTip( tr("Create box object") );
		connect( objectsCreateBoxAction, SIGNAL(triggered()), this, SLOT(objectsCreateBox()) );

		objectsCreateLineAction = new QAction( tr("Line"), this );
		objectsCreateLineAction->setIcon( Icons::Line() );
		objectsCreateLineAction->setStatusTip( tr("Create line object") );
		connect( objectsCreateLineAction, SIGNAL(triggered()), this, SLOT(objectsCreateLine()) );

		objectsCreateEllipseAction = new QAction( tr("Ellipse"), this );
		objectsCreateEllipseAction->setIcon( Icons::Ellipse() );
		objectsCreateEllipseAction->setStatusTip( tr("Create ellipse/circle object") );
		connect( objectsCreateEllipseAction, SIGNAL(triggered()), this, SLOT(objectsCreateEllipse()) );

		objectsCreateImageAction = new QAction( tr("Image"), this );
		objectsCreateImageAction->setIcon( Icons::Image() );
		objectsCreateImageAction->setStatusTip( tr("Create image object") );
		connect( objectsCreateImageAction, SIGNAL(triggered()), this, SLOT(objectsCreateImage()) );

		objectsCreateBarcodeAction = new QAction( tr("Barcode"), this );
		objectsCreateBarcodeAction->setIcon( Icons::Barcode() );
		objectsCreateBarcodeAction->setStatusTip( tr("Create barcode object") );
		connect( objectsCreateBarcodeAction, SIGNAL(triggered()), this, SLOT(objectsCreateBarcode()) );

		objectsOrderRaiseAction = new QAction( tr("Bring To Front"), this );
		objectsOrderRaiseAction->setIcon( Icons::OrderTop() );
		objectsOrderRaiseAction->setStatusTip( tr("Raise selection to top") );
		connect( objectsOrderRaiseAction, SIGNAL(triggered()), this, SLOT(objectsOrderRaise()) );

		objectsOrderLowerAction = new QAction( tr("Send To Back"), this );
		objectsOrderLowerAction->setIcon( Icons::OrderBottom() );
		objectsOrderLowerAction->setStatusTip( tr("Lower selection to bottom") );
		connect( objectsOrderLowerAction, SIGNAL(triggered()), this, SLOT(objectsOrderLower()) );

		objectsXformRotateLeftAction = new QAction( tr("Rotate Left"), this );
		objectsXformRotateLeftAction->setIcon( Icons::RotateLeft() );
		objectsXformRotateLeftAction->setStatusTip( tr("Rotate object(s) 90 degrees counter-clockwise") );
		connect( objectsXformRotateLeftAction, SIGNAL(triggered()), this, SLOT(objectsXformRotateLeft()) );

		objectsXformRotateRightAction = new QAction( tr("Rotate Right"), this );
		objectsXformRotateRightAction->setIcon( Icons::RotateRight() );
		objectsXformRotateRightAction->setStatusTip( tr("Rotate object(s) 90 degrees clockwise") );
		connect( objectsXformRotateRightAction, SIGNAL(triggered()), this, SLOT(objectsXformRotateRight()) );

		objectsXformFlipHorizAction = new QAction( tr("Flip Horizontally"), this );
		objectsXformFlipHorizAction->setIcon( Icons::FlipHoriz() );
		objectsXformFlipHorizAction->setStatusTip( tr("Flip object(s) horizontally") );
		connect( objectsXformFlipHorizAction, SIGNAL(triggered()), this, SLOT(objectsXformFlipHoriz()) );

		objectsXformFlipVertAction = new QAction( tr("Flip Vertically"), this );
		objectsXformFlipVertAction->setIcon( Icons::FlipVert() );
		objectsXformFlipVertAction->setStatusTip( tr("Flip object(s) vertically") );
		connect( objectsXformFlipVertAction, SIGNAL(triggered()), this, SLOT(objectsXformFlipVert()) );

		objectsAlignLeftAction = new QAction( tr("Align Left"), this );
		objectsAlignLeftAction->setIcon( Icons::AlignLeft() );
		objectsAlignLeftAction->setStatusTip( tr("Align objects to left edges") );
		connect( objectsAlignLeftAction, SIGNAL(triggered()), this, SLOT(objectsAlignLeft()) );

		objectsAlignHCenterAction = new QAction( tr("Align Center"), this );
		objectsAlignHCenterAction->setIcon( Icons::AlignHCenter() );
		objectsAlignHCenterAction->setStatusTip( tr("Align objects to horizontal centers") );
		connect( objectsAlignHCenterAction, SIGNAL(triggered()), this, SLOT(objectsAlignHCenter()) );

		objectsAlignRightAction = new QAction( tr("Align Right"), this );
		objectsAlignRightAction->setIcon( Icons::AlignRight() );
		objectsAlignRightAction->setStatusTip( tr("Align objects to right edges") );
		connect( objectsAlignRightAction, SIGNAL(triggered()), this, SLOT(objectsAlignRight()) );

		objectsAlignTopAction = new QAction( tr("Align Top"), this );
		objectsAlignTopAction->setIcon( Icons::AlignTop() );
		objectsAlignTopAction->setStatusTip( tr("Align objects to top edges") );
		connect( objectsAlignTopAction, SIGNAL(triggered()), this, SLOT(objectsAlignTop()) );

		objectsAlignVCenterAction = new QAction( tr("Align Middle"), this );
		objectsAlignVCenterAction->setIcon( Icons::AlignVCenter() );
		objectsAlignVCenterAction->setStatusTip( tr("Align objects to vertical centers") );
		connect( objectsAlignVCenterAction, SIGNAL(triggered()), this, SLOT(objectsAlignVCenter()) );

		objectsAlignBottomAction = new QAction( tr("Align Bottom"), this );
		objectsAlignBottomAction->setIcon( Icons::AlignBottom() );
		objectsAlignBottomAction->setStatusTip( tr("Align objects to bottom edges") );
		connect( objectsAlignBottomAction, SIGNAL(triggered()), this, SLOT(objectsAlignBottom()) );

		objectsCenterHorizAction = new QAction( tr("Center Horizontally"), this );
		objectsCenterHorizAction->setIcon( Icons::CenterHoriz() );
		objectsCenterHorizAction->setStatusTip( tr("Horizontally center objects in label") );
		connect( objectsCenterHorizAction, SIGNAL(triggered()), this, SLOT(objectsCenterHoriz()) );

		objectsCenterVertAction = new QAction( tr("Center Vertically"), this );
		objectsCenterVertAction->setIcon( Icons::CenterVert() );
		objectsCenterVertAction->setStatusTip( tr("Vertically center objects in label") );
		connect( objectsCenterVertAction, SIGNAL(triggered()), this, SLOT(objectsCenterVert()) );


		/* Help actions */
		helpContentsAction = new QAction( tr("&Contents..."), this );
		helpContentsAction->setIcon( QIcon::fromTheme( "help-contents" ) );
		helpContentsAction->setShortcut( QKeySequence::HelpContents );
		helpContentsAction->setStatusTip( tr("Open gLabels manual") );
		connect( helpContentsAction, SIGNAL(triggered()), this, SLOT(helpContents()) );

		helpAboutAction = new QAction( tr("&About..."), this );
		helpAboutAction->setIcon( QIcon::fromTheme( "help-about" ) );
		helpAboutAction->setStatusTip( tr("About gLabels") );
		connect( helpAboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()) );


		/* Context menu version of edit actions */
		contextCutAction = new QAction( tr("Cut"), this );
		contextCutAction->setIcon( Icons::EditCut() );
		contextCutAction->setStatusTip( tr("Cut the selection") );
		connect( contextCutAction, SIGNAL(triggered()), this, SLOT(editCut()) );

		contextCopyAction = new QAction( tr("&Copy"), this );
		contextCopyAction->setIcon( Icons::EditCopy() );
		contextCopyAction->setStatusTip( tr("Copy the selection") );
		connect( contextCopyAction, SIGNAL(triggered()), this, SLOT(editCopy()) );

		contextPasteAction = new QAction( tr("&Paste"), this );
		contextPasteAction->setIcon( Icons::EditPaste() );
		contextPasteAction->setStatusTip( tr("Paste the clipboard") );
		connect( contextPasteAction, SIGNAL(triggered()), this, SLOT(editPaste()) );

		contextDeleteAction = new QAction( tr("&Delete"), this );
		contextDeleteAction->setIcon( QIcon::fromTheme( "edit-delete" ) );
		contextDeleteAction->setStatusTip( tr("Delete the selected objects") );
		connect( contextDeleteAction, SIGNAL(triggered()), this, SLOT(editDelete()) );
	}


	///
	/// Create Menus
	///
	void MainWindow::createMenus()
	{
		fileMenu = menuBar()->addMenu( tr("&File") );
		fileMenu->addAction( fileNewAction );
		fileMenu->addAction( fileOpenAction );
		fileMenu->addAction( fileSaveAction );
		fileMenu->addAction( fileSaveAsAction );
		fileMenu->addSeparator();
		fileMenu->addAction( fileShowEditorPageAction );
		fileMenu->addAction( fileShowPropertiesPageAction );
		fileMenu->addAction( fileShowMergePageAction );
		fileMenu->addAction( fileShowPrintPageAction );
		fileMenu->addSeparator();
		fileMenu->addAction( fileTemplateDesignerAction );
		fileMenu->addSeparator();
		fileMenu->addAction( fileCloseAction );
		fileMenu->addAction( fileExitAction );

		editMenu = menuBar()->addMenu( tr("&Edit") );
		editMenu->addAction( editUndoAction );
		editMenu->addAction( editRedoAction );
		editMenu->addSeparator();
		editMenu->addAction( editCutAction );
		editMenu->addAction( editCopyAction );
		editMenu->addAction( editPasteAction );
		editMenu->addAction( editDeleteAction );
		editMenu->addSeparator();
		editMenu->addAction( editSelectAllAction );
		editMenu->addAction( editUnSelectAllAction );
		editMenu->addSeparator();
		editMenu->addAction( editPreferencesAction );

		viewMenu = menuBar()->addMenu( tr("&View") );
		viewToolBarsMenu = viewMenu->addMenu( tr("Toolbars") );
		viewToolBarsMenu->addAction( viewFileToolBarAction );
		viewToolBarsMenu->addAction( viewEditorToolBarAction );
		viewMenu->addSeparator();
		viewMenu->addAction( viewGridAction );
		viewMenu->addAction( viewMarkupAction );
		viewMenu->addSeparator();
		viewMenu->addAction( viewZoomInAction );
		viewMenu->addAction( viewZoomOutAction );
		viewMenu->addAction( viewZoom1To1Action );
		viewMenu->addAction( viewZoomToFitAction );

		objectsMenu = menuBar()->addMenu( tr("&Objects") );
		objectsMenu->addAction( objectsArrowModeAction );
		objectsCreateMenu = objectsMenu->addMenu( tr("&Create") );
		objectsCreateMenu->addAction( objectsCreateTextAction );
		objectsCreateMenu->addAction( objectsCreateBoxAction );
		objectsCreateMenu->addAction( objectsCreateLineAction );
		objectsCreateMenu->addAction( objectsCreateEllipseAction );
		objectsCreateMenu->addAction( objectsCreateImageAction );
		objectsCreateMenu->addAction( objectsCreateBarcodeAction );
		objectsMenu->addSeparator();
		objectsOrderMenu = objectsMenu->addMenu( tr("&Order") );
		objectsOrderMenu->addAction( objectsOrderRaiseAction );
		objectsOrderMenu->addAction( objectsOrderLowerAction );
		objectsXformMenu = objectsMenu->addMenu( tr("&Rotate/Flip") );
		objectsXformMenu->addAction( objectsXformRotateLeftAction );
		objectsXformMenu->addAction( objectsXformRotateRightAction );
		objectsXformMenu->addAction( objectsXformFlipHorizAction );
		objectsXformMenu->addAction( objectsXformFlipVertAction );
		objectsAlignMenu = objectsMenu->addMenu( tr("&Alignment") );
		objectsAlignMenu->addAction( objectsAlignLeftAction );
		objectsAlignMenu->addAction( objectsAlignHCenterAction );
		objectsAlignMenu->addAction( objectsAlignRightAction );
		objectsAlignMenu->addSeparator();
		objectsAlignMenu->addAction( objectsAlignTopAction );
		objectsAlignMenu->addAction( objectsAlignVCenterAction );
		objectsAlignMenu->addAction( objectsAlignBottomAction );
		objectsCenterMenu = objectsMenu->addMenu( tr("Center") );
		objectsCenterMenu->addAction( objectsCenterHorizAction );
		objectsCenterMenu->addAction( objectsCenterVertAction );

		helpMenu = menuBar()->addMenu( tr("&Help") );
		helpMenu->addAction( helpContentsAction );
		helpMenu->addAction( helpAboutAction );

		contextMenu = new QMenu();
		contextOrderMenu = contextMenu->addMenu( tr("&Order") );
		contextOrderMenu->addAction( objectsOrderRaiseAction );
		contextOrderMenu->addAction( objectsOrderLowerAction );
		contextXformMenu = contextMenu->addMenu( tr("&Rotate/Flip") );
		contextXformMenu->addAction( objectsXformRotateLeftAction );
		contextXformMenu->addAction( objectsXformRotateRightAction );
		contextXformMenu->addAction( objectsXformFlipHorizAction );
		contextXformMenu->addAction( objectsXformFlipVertAction );
		contextAlignMenu = contextMenu->addMenu( tr("&Alignment") );
		contextAlignMenu->addAction( objectsAlignLeftAction );
		contextAlignMenu->addAction( objectsAlignHCenterAction );
		contextAlignMenu->addAction( objectsAlignRightAction );
		contextAlignMenu->addSeparator();
		contextAlignMenu->addAction( objectsAlignTopAction );
		contextAlignMenu->addAction( objectsAlignVCenterAction );
		contextAlignMenu->addAction( objectsAlignBottomAction );
		contextCenterMenu = contextMenu->addMenu( tr("Center") );
		contextCenterMenu->addAction( objectsCenterHorizAction );
		contextCenterMenu->addAction( objectsCenterVertAction );
		contextMenu->addSeparator();
		contextMenu->addAction( contextCutAction );
		contextMenu->addAction( contextCopyAction );
		contextMenu->addAction( contextPasteAction );
		contextMenu->addAction( contextDeleteAction );

		noSelectionContextMenu = new QMenu();
		noSelectionContextMenu->addAction( contextPasteAction );
	}


	///
	/// Create Tool Bars
	///
	void MainWindow::createToolBars()
	{
		fileToolBar = addToolBar( tr("&File") );
		fileToolBar->addAction( fileNewAction );
		fileToolBar->addAction( fileOpenAction );
		fileToolBar->addAction( fileSaveAction );

		zoomInfoLabel = new QLabel( " 999% " );
		zoomInfoLabel->setAlignment( Qt::AlignHCenter|Qt::AlignVCenter );
		zoomInfoLabel->setMinimumSize( zoomInfoLabel->sizeHint() );

		editorToolBar = new QToolBar( tr("&Editor") );
		editorToolBar->addAction( objectsArrowModeAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( objectsCreateTextAction );
		editorToolBar->addAction( objectsCreateBoxAction );
		editorToolBar->addAction( objectsCreateLineAction );
		editorToolBar->addAction( objectsCreateEllipseAction );
		editorToolBar->addAction( objectsCreateImageAction );
		editorToolBar->addAction( objectsCreateBarcodeAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( editCutAction );
		editorToolBar->addAction( editCopyAction );
		editorToolBar->addAction( editPasteAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( viewZoomInAction );
		editorToolBar->addAction( viewZoomOutAction );
		editorToolBar->addAction( viewZoom1To1Action );
		editorToolBar->addAction( viewZoomToFitAction );
		editorToolBar->addWidget( zoomInfoLabel );
		editorToolBar->addSeparator();
	}


	///
	/// Create Status Bar
	///
	void MainWindow::createStatusBar()
	{
		statusBar();
	}


	///
	/// Create Welcome Page
	///
	QWidget* MainWindow::createWelcomePage()
	{
		mWelcomeView = new StartupView( this );

		return mWelcomeView;
	}


	///
	/// Create Properties Page
	///
	QWidget* MainWindow::createPropertiesPage()
	{
		mPropertiesView = new PropertiesView();

		return mPropertiesView;
	}


	///
	/// Create Editor Page
	///
	QWidget* MainWindow::createEditorPage()
	{
		QWidget* page = new QWidget;

		mLabelEditorScrollArea = new QScrollArea();
		mLabelEditorScrollArea->setMinimumSize( 640, 450 );
		mLabelEditorScrollArea->setWidgetResizable( true );

		mLabelEditor = new LabelEditor( mLabelEditorScrollArea );
		mObjectEditor = new ObjectEditor();

		mLabelEditorScrollArea->setWidget( mLabelEditor );

		auto* editorVLayout = new QVBoxLayout;
		editorVLayout->setContentsMargins( 0, 0, 0, 0 );
		editorVLayout->addWidget( editorToolBar );
		editorVLayout->addWidget( mLabelEditorScrollArea );

		auto* editorHLayout = new QHBoxLayout;
		editorHLayout->setContentsMargins( 0, 0, 0, 0 );
		editorHLayout->addLayout( editorVLayout );
		editorHLayout->addWidget( mObjectEditor );

		page->setLayout( editorHLayout );

		return page;
	}


	///
	/// Create Merge Page
	///
	QWidget* MainWindow::createMergePage()
	{
		mMergeView = new MergeView();

		return mMergeView;
	}


	///
	/// Create Print Page
	///
	QWidget* MainWindow::createPrintPage()
	{
		mPrintView = new PrintView();

		return mPrintView;
	}


	///
	/// Set enabled state of TOC buttons based on Welcome mode
	///
	void MainWindow::setWelcomeMode( bool enabled )
	{
		mWelcomeButton->setHidden( !enabled );
		mPropertiesButton->setHidden( enabled );
		mEditorButton->setHidden( enabled );
		mMergeButton->setHidden( enabled );
		mPrintButton->setHidden( enabled );
	}


	///
	/// Set enabled state of actions associated with a document.
	///
	void MainWindow::setDocVerbsEnabled( bool enabled )
	{
		fileSaveAction->setEnabled( mModel && mModel->isModified() );
		fileSaveAsAction->setEnabled( mModel );
		editUndoAction->setEnabled( enabled && mUndoRedoModel->canUndo() );
		editRedoAction->setEnabled( enabled && mUndoRedoModel->canRedo() );
		editDeleteAction->setEnabled( enabled );
		editSelectAllAction->setEnabled( enabled );
		editUnSelectAllAction->setEnabled( enabled );
		viewZoomInAction->setEnabled( enabled );
		viewZoomOutAction->setEnabled( enabled );
		viewZoom1To1Action->setEnabled( enabled );
		viewZoomToFitAction->setEnabled( enabled );
		viewGridAction->setEnabled( enabled );
		viewMarkupAction->setEnabled( enabled );
		objectsArrowModeAction->setEnabled( enabled );
		objectsCreateMenu->setEnabled( enabled );
		objectsCreateTextAction->setEnabled( enabled );
		objectsCreateLineAction->setEnabled( enabled );
		objectsCreateBoxAction->setEnabled( enabled );
		objectsCreateEllipseAction->setEnabled( enabled );
		objectsCreateImageAction->setEnabled( enabled );
		objectsCreateBarcodeAction->setEnabled( enabled );
		objectsOrderMenu->setEnabled( enabled );
		objectsOrderRaiseAction->setEnabled( enabled );
		objectsOrderLowerAction->setEnabled( enabled );
		objectsXformMenu->setEnabled( enabled );
		objectsXformRotateLeftAction->setEnabled( enabled );
		objectsXformRotateRightAction->setEnabled( enabled );
		objectsXformFlipHorizAction->setEnabled( enabled );
		objectsXformFlipVertAction->setEnabled( enabled );
		objectsAlignMenu->setEnabled( enabled );
		objectsAlignLeftAction->setEnabled( enabled );
		objectsAlignRightAction->setEnabled( enabled );
		objectsAlignHCenterAction->setEnabled( enabled );
		objectsAlignTopAction->setEnabled( enabled );
		objectsAlignBottomAction->setEnabled( enabled );
		objectsAlignVCenterAction->setEnabled( enabled );
		objectsCenterMenu->setEnabled( enabled );
		objectsCenterHorizAction->setEnabled( enabled );
		objectsCenterVertAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a document being modified since last save.
	///
	void MainWindow::setDocModifiedVerbsEnabled( bool enabled )
	{
		fileSaveAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with data being available on clipboard.
	///
	void MainWindow::setPasteVerbsEnabled( bool enabled )
	{
		editPasteAction->setEnabled( enabled );
		contextPasteAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a non-empty selection.
	///
	void MainWindow::setSelectionVerbsEnabled( bool enabled )
	{
		editCutAction->setEnabled( enabled );
		editCopyAction->setEnabled( enabled );
		editDeleteAction->setEnabled( enabled );
		editUnSelectAllAction->setEnabled( enabled );
		objectsOrderMenu->setEnabled( enabled );
		objectsOrderRaiseAction->setEnabled( enabled );
		objectsOrderLowerAction->setEnabled( enabled );
		objectsXformMenu->setEnabled( enabled );
		objectsXformRotateLeftAction->setEnabled( enabled );
		objectsXformRotateRightAction->setEnabled( enabled );
		objectsXformFlipHorizAction->setEnabled( enabled );
		objectsXformFlipVertAction->setEnabled( enabled );
		objectsCenterMenu->setEnabled( enabled );
		objectsCenterHorizAction->setEnabled( enabled );
		objectsCenterVertAction->setEnabled( enabled );

		contextOrderMenu->setEnabled( enabled );
		contextXformMenu->setEnabled( enabled );
		contextCenterMenu->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a non-atomic selection.
	///
	void MainWindow::setMultiSelectionVerbsEnabled( bool enabled )
	{
		objectsAlignMenu->setEnabled( enabled );
		objectsAlignLeftAction->setEnabled( enabled );
		objectsAlignRightAction->setEnabled( enabled );
		objectsAlignHCenterAction->setEnabled( enabled );
		objectsAlignTopAction->setEnabled( enabled );
		objectsAlignBottomAction->setEnabled( enabled );
		objectsAlignVCenterAction->setEnabled( enabled );

		contextAlignMenu->setEnabled( enabled );
	}


	///
	/// Set window title
	///
	void MainWindow::setTitle()
	{
		if ( mModel == nullptr )
		{
			setWindowTitle( "gLabels" );
		}
		else
		{
			if ( mModel->isModified() )
			{
				setWindowTitle( "gLabels - " + mModel->shortName() + " " + tr("(modified)") );
			}
			else
			{
				setWindowTitle( "gLabels - " + mModel->shortName()  );
			}
		}
	}


	///
	/// Read MainWindow Settings
	///
	void MainWindow::readSettings()
	{
		QSettings settings;

		settings.beginGroup( "MainWindow" );
		bool showFileToolBar    = settings.value( "showFileToolBar",    true ).toBool();
		bool showEditorToolBar  = settings.value( "showEditToolBar",    true ).toBool();
		bool showGrid           = settings.value( "showGrid",           true ).toBool();
		bool showMarkup         = settings.value( "showMarkup",         true ).toBool();
		settings.endGroup();

		viewFileToolBarAction   ->setChecked( showFileToolBar );
		viewEditorToolBarAction ->setChecked( showEditorToolBar );
		viewGridAction          ->setChecked( showGrid );
		viewMarkupAction        ->setChecked( showMarkup );

		fileToolBar   ->setVisible(       showFileToolBar );
		editorToolBar ->setVisible(       showEditorToolBar );
		mLabelEditor  ->setGridVisible(   showGrid );
		mLabelEditor  ->setMarkupVisible( showMarkup );
	}


	///
	/// Write MainWindow Settings
	///
	void MainWindow::writeSettings()
	{
		QSettings settings;

		settings.beginGroup( "MainWindow" );
		settings.setValue( "showFileToolBar",    viewFileToolBarAction->isChecked() );
		settings.setValue( "showEditorToolBar",  viewEditorToolBarAction->isChecked() );
		settings.setValue( "showGrid",           viewGridAction->isChecked() );
		settings.setValue( "showMarkup",         viewMarkupAction->isChecked() );
		settings.endGroup();
	}


	///
	/// Is it ok to close window?
	///
	bool MainWindow::isOkToClose()
	{
		bool ok = true;

		if ( !this->isEmpty() )
		{
			if ( mModel->isModified() )
			{
				QString msg = tr("Save changes to project \"%1\" before closing?").arg( mModel->shortName() );
				QString info = tr("Your changes will be lost if you don't save them.");

				int ret = QMessageBox::warning( this,
				                                tr( "Save project?" ),
				                                "<b>" + msg + "</b><p>" + info + "</p>",
				                                (QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel),
				                                QMessageBox::Save );

				switch (ret) {
				case QMessageBox::Save:
					// Save was clicked
					ok = File::save( this );
					break;
				case QMessageBox::Discard:
					// Don't Save was clicked
					ok = true;
					break;
				case QMessageBox::Cancel:
					// Cancel was clicked
					ok = false;
					break;
				default:
					// should never be reached
					ok = false;
					break;
				}
			}
		}

		return ok;
	}


	///
	/// Change page
	///
	void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous)
	{
		if (!current)
		{
			current = previous;
		}

		int row = mContents->row(current);
    
		mPages->setCurrentIndex(row);
		bool isEditorPage = ( row == mContents->row(mEditorButton) );

		setDocVerbsEnabled( isEditorPage );
		setSelectionVerbsEnabled( isEditorPage && !mModel->isSelectionEmpty() );
		setMultiSelectionVerbsEnabled( isEditorPage && !mModel->isSelectionEmpty() && !mModel->isSelectionAtomic() );
		setPasteVerbsEnabled( isEditorPage && mModel->canPaste() );

		bool isWelcome = ( current == mWelcomeButton );
		fileShowEditorPageAction->setEnabled( !isWelcome && (current != mEditorButton) );
		fileShowPropertiesPageAction->setEnabled( !isWelcome && (current != mPropertiesButton) );
		fileShowMergePageAction->setEnabled( !isWelcome && (current != mMergeButton) );
		fileShowPrintPageAction->setEnabled( !isWelcome && (current != mPrintButton) );
	}


	///
	/// Clipboard contents changed
	///
	void MainWindow::clipboardChanged()
	{
		setPasteVerbsEnabled( mModel->canPaste() );
	}


	///
	/// File->New Action
	///
	void MainWindow::fileNew()
	{
		File::newLabel( this );
	}


	///
	/// File->Open Action
	///
	void MainWindow::fileOpen()
	{
		File::open( this );
	}


	///
	/// File->Save Action
	///
	void MainWindow::fileSave()
	{
		File::save( this );
	}


	///
	/// File->Save As Action
	///
	void MainWindow::fileSaveAs()
	{
		File::saveAs( this );
	}


	///
	/// File->Show Editor Page
	///
	void MainWindow::fileShowEditorPage()
	{
		mContents->setCurrentItem( mEditorButton );
	}


	///
	/// File->Show Properties Page
	///
	void MainWindow::fileShowPropertiesPage()
	{
		mContents->setCurrentItem( mPropertiesButton );
	}


	///
	/// File->Show Merge Page
	///
	void MainWindow::fileShowMergePage()
	{
		mContents->setCurrentItem( mMergeButton );
	}


	///
	/// File->Show Print Page
	///
	void MainWindow::fileShowPrintPage()
	{
		mContents->setCurrentItem( mPrintButton );
	}


	///
	/// File->Template Designer Action
	///
	void MainWindow::fileTemplateDesigner()
	{
		File::templateDesigner( this );
	}


	///
	/// File->Close Action
	///
	void MainWindow::fileClose()
	{
		File::close( this );
	}


	///
	/// File->Exit Action
	///
	void MainWindow::fileExit()
	{
		File::exit();
	}


	///
	/// Edit->Undo Action
	///
	void MainWindow::editUndo()
	{
		mUndoRedoModel->undo();
	}


	///
	/// Edit->Redo Action
	///
	void MainWindow::editRedo()
	{
		mUndoRedoModel->redo();
	}


	///
	/// Edit->Cut Action
	///
	void MainWindow::editCut()
	{
		mUndoRedoModel->checkpoint( tr("Cut") );
		mModel->cutSelection();
	}


	///
	/// Edit->Copy Action
	///
	void MainWindow::editCopy()
	{
		// Non-destructive -- do not checkpoint.
		mModel->copySelection();
	}


	///
	/// Edit->Paste Action
	///
	void MainWindow::editPaste()
	{
		mUndoRedoModel->checkpoint( tr("Paste") );
		mModel->paste();
	}


	///
	/// Edit->Delete Action
	///
	void MainWindow::editDelete()
	{
		mUndoRedoModel->checkpoint( tr("Delete") );
		mModel->deleteSelection();
	}


	///
	/// Edit->Select All Action
	///
	void MainWindow::editSelectAll()
	{
		mModel->selectAll();
	}


	///
	/// Edit->Unselect All Action
	///
	void MainWindow::editUnSelectAll()
	{
		mModel->unselectAll();
	}


	///
	/// Edit->Preferences Action
	///
	void MainWindow::editPreferences()
	{
		PreferencesDialog dialog( this );
		dialog.exec();
	}


	///
	/// View->File Tool Bar Toggle Action
	///
	void MainWindow::viewFileToolBar( bool state )
	{
		fileToolBar->setVisible( state );
	}


	///
	/// View->Objects Tool Bar Toggle Action
	///
	void MainWindow::viewEditorToolBar( bool state )
	{
		editorToolBar->setVisible( state );
	}


	///
	/// View->Grid Toggle Action
	///
	void MainWindow::viewGrid( bool state )
	{
		mLabelEditor->setGridVisible( state );
	}


	///
	/// View->Markup Toggle Action
	///
	void MainWindow::viewMarkup( bool state )
	{
		mLabelEditor->setMarkupVisible( state );
	}


	///
	/// View->Zoom In Action
	///
	void MainWindow::viewZoomIn()
	{
		mLabelEditor->zoomIn();
	}


	///
	/// View->Zoom Out Action
	///
	void MainWindow::viewZoomOut()
	{
		mLabelEditor->zoomOut();
	}


	///
	/// View->Zoom 1:1 Action
	///
	void MainWindow::viewZoom1To1()
	{
		mLabelEditor->zoom1To1();
	}


	///
	/// View->Zoom To Fit Action
	///
	void MainWindow::viewZoomToFit()
	{
		mLabelEditor->zoomToFit();
	}


	///
	/// Objects->Arrow Mode Action
	///
	void MainWindow::objectsArrowMode()
	{
		mLabelEditor->arrowMode();
	}


	///
	/// Objects->Create Text Mode Action
	///
	void MainWindow::objectsCreateText()
	{
		mUndoRedoModel->checkpoint( tr("Create Text") );
		mLabelEditor->createTextMode();
	}


	///
	/// Objects->Create Box Mode Action
	///
	void MainWindow::objectsCreateBox()
	{
		mUndoRedoModel->checkpoint( tr("Create Box") );
		mLabelEditor->createBoxMode();
	}


	///
	/// Objects->Create Line Mode Action
	///
	void MainWindow::objectsCreateLine()
	{
		mUndoRedoModel->checkpoint( tr("Create Line") );
		mLabelEditor->createLineMode();
	}


	///
	/// Objects->Create Ellipse Mode Action
	///
	void MainWindow::objectsCreateEllipse()
	{
		mUndoRedoModel->checkpoint( tr("Create Ellipse") );
		mLabelEditor->createEllipseMode();
	}


	///
	/// Objects->Create Image Mode Action
	///
	void MainWindow::objectsCreateImage()
	{
		mUndoRedoModel->checkpoint( tr("Create Image") );
		mLabelEditor->createImageMode();
	}


	///
	/// Objects->Create Barcode Mode Action
	///
	void MainWindow::objectsCreateBarcode()
	{
		mUndoRedoModel->checkpoint( tr("Create Barcode") );
		mLabelEditor->createBarcodeMode();
	}


	///
	/// Objects->Order->Bring To Front Action
	///
	void MainWindow::objectsOrderRaise()
	{
		mUndoRedoModel->checkpoint( tr("Bring To Front") );
		mModel->raiseSelectionToTop();
	}


	///
	/// Objects->Order->Send To Back Action
	///
	void MainWindow::objectsOrderLower()
	{
		mUndoRedoModel->checkpoint( tr("Send To Back") );
		mModel->lowerSelectionToBottom();
	}


	///
	/// Objects->Rotate/Flip->Rotate Left Action
	///
	void MainWindow::objectsXformRotateLeft()
	{
		mUndoRedoModel->checkpoint( tr("Rotate Left") );
		mModel->rotateSelectionLeft();
	}


	///
	/// Objects->Rotate/Flip->Rotate Right Action
	///
	void MainWindow::objectsXformRotateRight()
	{
		mUndoRedoModel->checkpoint( tr("Rotate Right") );
		mModel->rotateSelectionRight();
	}


	///
	/// Objects->Rotate/Flip->Flip Horizontally Action
	///
	void MainWindow::objectsXformFlipHoriz()
	{
		mUndoRedoModel->checkpoint( tr("Flip Horizontally") );
		mModel->flipSelectionHoriz();
	}


	///
	/// Objects->Rotate/Flip->Flip Vertically Action
	///
	void MainWindow::objectsXformFlipVert()
	{
		mUndoRedoModel->checkpoint( tr("Flip Vertically") );
		mModel->flipSelectionVert();
	}


	///
	/// Objects->Align->Left Action
	///
	void MainWindow::objectsAlignLeft()
	{
		mUndoRedoModel->checkpoint( tr("Align Left") );
		mModel->alignSelectionLeft();
	}


	///
	/// Objects->Align->Center Horizontally Action
	///
	void MainWindow::objectsAlignHCenter()
	{
		mUndoRedoModel->checkpoint( tr("Align Center") );
		mModel->alignSelectionHCenter();
	}


	///
	/// Objects->Align->Right Action
	///
	void MainWindow::objectsAlignRight()
	{
		mUndoRedoModel->checkpoint( tr("Align Right") );
		mModel->alignSelectionRight();
	}


	///
	/// Objects->Align->Top Action
	///
	void MainWindow::objectsAlignTop()
	{
		mUndoRedoModel->checkpoint( tr("Align Top") );
		mModel->alignSelectionTop();
	}


	///
	/// Objects->Align->Center Vertically Action
	///
	void MainWindow::objectsAlignVCenter()
	{
		mUndoRedoModel->checkpoint( tr("Align Middle") );
		mModel->alignSelectionVCenter();
	}


	///
	/// Objects->Align->Bottom Action
	///
	void MainWindow::objectsAlignBottom()
	{
		mUndoRedoModel->checkpoint( tr("Align Bottom") );
		mModel->alignSelectionBottom();
	}


	///
	/// Objects->Center->Horizontally Action
	///
	void MainWindow::objectsCenterHoriz()
	{
		mUndoRedoModel->checkpoint( tr("Center Horizontally") );
		mModel->centerSelectionHoriz();
	}


	///
	/// Objects->Center->Vertically Action
	///
	void MainWindow::objectsCenterVert()
	{
		mUndoRedoModel->checkpoint( tr("Center Vertically") );
		mModel->centerSelectionVert();
	}


	///
	/// Help->Contents Action
	///
	void MainWindow::helpContents()
	{
		Help::displayContents( this );
	}


	///
	/// Help->About Action
	///
	void MainWindow::helpAbout()
	{
		Help::displayAbout( this );
	}


	///
	/// Context Menu Activation
	///
	void MainWindow::onContextMenuActivate()
	{
		if ( mModel->isSelectionEmpty() )
		{
			noSelectionContextMenu->popup( QCursor::pos() );
		}
		else
		{
			contextMenu->popup( QCursor::pos() );
		}
	}


	///
	/// Zoom changed: update Zoom Information in Status Bar
	///
	void MainWindow::onZoomChanged()
	{
		zoomInfoLabel->setText( QString( " %1% " ).arg(100*mLabelEditor->zoom(), 0, 'f', 0) );

		viewZoomInAction->setEnabled( !mLabelEditor->isZoomMax() );
		viewZoomOutAction->setEnabled( !mLabelEditor->isZoomMin() );
	}


	///
	/// Pointer moved: update Cursor Information in Status Bar
	///
	void MainWindow::onPointerMoved( double x, double y )
	{
		/* TODO: convert x,y to locale units and set precision accordingly. */
		cursorInfoLabel->setText( QString( "%1, %2" ).arg(x).arg(y) );
	}


	///
	/// Pointer exited view: update Zoom Information in Status Bar (Clears information)
	///
	void MainWindow::onPointerExit()
	{
		cursorInfoLabel->setText( "" );
	}


	///
	/// Name changed handler
	///
	void MainWindow::onNameChanged()
	{
		setTitle();
	}


	///
	/// Modified changed handler
	///
	void MainWindow::onModifiedChanged()
	{
		setTitle();
		setDocModifiedVerbsEnabled( mModel->isModified() );
	}


	///
	/// Selection changed handler
	///
	void MainWindow::onSelectionChanged()
	{
		setSelectionVerbsEnabled( !mModel->isSelectionEmpty() );
		setMultiSelectionVerbsEnabled( !mModel->isSelectionEmpty() && !mModel->isSelectionAtomic() );
	}


	///
	/// Label changed handler
	///
	void MainWindow::onLabelChanged()
	{
		// TODO
	}


	///
	/// Undo/Redo changed handler
	///
	void MainWindow::onUndoRedoChanged()
	{
		editUndoAction->setEnabled( mUndoRedoModel->canUndo() );
		editRedoAction->setEnabled( mUndoRedoModel->canRedo() );
	}

} // namespace glabels
