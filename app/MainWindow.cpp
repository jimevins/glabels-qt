/*  MainWindow.cpp
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

#include "MainWindow.h"

#include <QLabel>
#include <QMessageBox>

#include <iostream>


namespace gLabels
{

	MainWindow::MainWindow()
	{
		QLabel *tmp = new QLabel( "Coming Soon..." );
		setCentralWidget( tmp );

		createActions();
		createMenus();
	}


	void MainWindow::closeEvent( QCloseEvent *event )
	{
		std::cout << "CLOSE EVENT" << std::endl;
		event->accept();
	}


	void MainWindow::createActions()
	{
		/* File actions */
		fileNewAction = new QAction( tr("&New..."), this );
		fileNewAction->setIcon( QIcon::fromTheme( "document-new" ) );
		fileNewAction->setShortcut( QKeySequence::New );
		fileNewAction->setStatusTip( tr("Create a new file") );
		connect( fileNewAction, SIGNAL(triggered()), this, SLOT(fileNew()) );

		fileOpenAction = new QAction( tr("&Open..."), this );
		fileOpenAction->setIcon( QIcon::fromTheme( "document-open" ) );
		fileOpenAction->setShortcut( QKeySequence::Open );
		fileOpenAction->setStatusTip( tr("Open a file") );
		connect( fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()) );

		fileSaveAction = new QAction( tr("&Save"), this );
		fileSaveAction->setIcon( QIcon::fromTheme( "document-save" ) );
		fileSaveAction->setShortcut( QKeySequence::Save );
		fileSaveAction->setStatusTip( tr("Save current file") );
		connect( fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()) );

		fileSaveAsAction = new QAction( tr("Save &As..."), this );
		fileSaveAsAction->setIcon( QIcon::fromTheme( "document-save-as" ) );
		fileSaveAsAction->setShortcut( QKeySequence::SaveAs );
		fileSaveAsAction->setStatusTip( tr("Save current file to a different name") );
		connect( fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()) );

		filePrintAction = new QAction( tr("&Print..."), this );
		filePrintAction->setIcon( QIcon::fromTheme( "document-print" ) );
		filePrintAction->setShortcut( QKeySequence::Print );
		filePrintAction->setStatusTip( tr("Print the current file") );
		connect( filePrintAction, SIGNAL(triggered()), this, SLOT(filePrint()) );

		filePropertiesAction = new QAction( tr("Properties..."), this );
		filePropertiesAction->setIcon( QIcon::fromTheme( "document-properties" ) );
		filePropertiesAction->setStatusTip( tr("Modify document properties") );
		connect( filePropertiesAction, SIGNAL(triggered()), this, SLOT(fileProperties()) );

		fileTemplateDesignerAction = new QAction( tr("Template &Designer..."), this );
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
		editCutAction->setIcon( QIcon::fromTheme( "edit-cut" ) );
		editCutAction->setShortcut( QKeySequence::Cut );
		editCutAction->setStatusTip( tr("Cut the selection") );
		connect( editCutAction, SIGNAL(triggered()), this, SLOT(editCut()) );

		editCopyAction = new QAction( tr("&Copy"), this );
		editCopyAction->setIcon( QIcon::fromTheme( "edit-copy" ) );
		editCopyAction->setShortcut( QKeySequence::Copy );
		editCopyAction->setStatusTip( tr("Copy the selection") );
		connect( editCopyAction, SIGNAL(triggered()), this, SLOT(editCopy()) );

		editPasteAction = new QAction( tr("&Paste"), this );
		editPasteAction->setIcon( QIcon::fromTheme( "edit-paste" ) );
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
		viewZoomInAction = new QAction( tr("Zoom &In"), this );
		viewZoomInAction->setIcon( QIcon::fromTheme( "zoom-in" ) );
		viewZoomInAction->setShortcut( QKeySequence::ZoomIn );
		viewZoomInAction->setStatusTip( tr("Increase magnification") );
		connect( viewZoomInAction, SIGNAL(triggered()), this, SLOT(viewZoomIn()) );

		viewZoomOutAction = new QAction( tr("Zoom &Out"), this );
		viewZoomOutAction->setIcon( QIcon::fromTheme( "zoom-out" ) );
		viewZoomOutAction->setShortcut( QKeySequence::ZoomOut );
		viewZoomOutAction->setStatusTip( tr("Decrease magnification") );
		connect( viewZoomOutAction, SIGNAL(triggered()), this, SLOT(viewZoomOut()) );

		viewZoom1to1Action = new QAction( tr("Zoom &1 to 1"), this );
		viewZoom1to1Action->setIcon( QIcon::fromTheme( "zoom-original" ) );
		viewZoom1to1Action->setStatusTip( tr("Restore scale to 100%") );
		connect( viewZoom1to1Action, SIGNAL(triggered()), this, SLOT(viewZoom1to1()) );

		viewZoomToFitAction = new QAction( tr("Zoom to &Fit"), this );
		viewZoomToFitAction->setIcon( QIcon::fromTheme( "zoom-fit-best" ) );
		viewZoomToFitAction->setStatusTip( tr("Set scale to fit window") );
		connect( viewZoomToFitAction, SIGNAL(triggered()), this, SLOT(viewZoomToFit()) );


		/* Help actions */
		helpAboutAction = new QAction( tr("&About..."), this );
		helpAboutAction->setIcon( QIcon::fromTheme( "help-about" ) );
		helpAboutAction->setStatusTip( tr("About gLabels") );
		connect( helpAboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()) );
	}


	void MainWindow::createMenus()
	{
		fileMenu = menuBar()->addMenu( tr("&File") );
		fileMenu->addAction( fileNewAction );
		fileMenu->addAction( fileOpenAction );
		fileMenu->addAction( fileSaveAction );
		fileMenu->addAction( fileSaveAsAction );
		fileMenu->addSeparator();
		fileMenu->addAction( filePrintAction );
		fileMenu->addSeparator();
		fileMenu->addAction( filePropertiesAction );
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
		viewMenu->addAction( viewZoomInAction );
		viewMenu->addAction( viewZoomOutAction );
		viewMenu->addAction( viewZoom1to1Action );
		viewMenu->addAction( viewZoomToFitAction );

		helpMenu = menuBar()->addMenu( tr("&Help") );
		helpMenu->addAction( helpAboutAction );
	}


	void MainWindow::fileNew()
	{
		std::cout << "ACTION: file->New" << std::endl;
	}


	void MainWindow::fileOpen()
	{
		std::cout << "ACTION: file->Open" << std::endl;
	}


	void MainWindow::fileSave()
	{
		std::cout << "ACTION: file->Save" << std::endl;
	}


	void MainWindow::fileSaveAs()
	{
		std::cout << "ACTION: file->Save As" << std::endl;
	}


	void MainWindow::filePrint()
	{
		std::cout << "ACTION: file->Print" << std::endl;
	}


	void MainWindow::fileProperties()
	{
		std::cout << "ACTION: file->Properties" << std::endl;
	}


	void MainWindow::fileTemplateDesigner()
	{
		std::cout << "ACTION: file->Template Designer" << std::endl;
	}


	void MainWindow::fileClose()
	{
		std::cout << "ACTION: file->Close" << std::endl;
	}


	void MainWindow::fileExit()
	{
		std::cout << "ACTION: file->Exit" << std::endl;
	}


	void MainWindow::editUndo()
	{
		std::cout << "ACTION: edit->Undo" << std::endl;
	}


	void MainWindow::editRedo()
	{
		std::cout << "ACTION: edit->Redo" << std::endl;
	}


	void MainWindow::editCut()
	{
		std::cout << "ACTION: edit->Cut" << std::endl;
	}


	void MainWindow::editCopy()
	{
		std::cout << "ACTION: edit->Copy" << std::endl;
	}


	void MainWindow::editPaste()
	{
		std::cout << "ACTION: edit->Paste" << std::endl;
	}


	void MainWindow::editDelete()
	{
		std::cout << "ACTION: edit->Delete" << std::endl;
	}


	void MainWindow::editSelectAll()
	{
		std::cout << "ACTION: edit->Select All" << std::endl;
	}


	void MainWindow::editUnSelectAll()
	{
		std::cout << "ACTION: edit->Un-select All" << std::endl;
	}


	void MainWindow::editPreferences()
	{
		std::cout << "ACTION: edit->Preferences" << std::endl;
	}


	void MainWindow::viewZoomIn()
	{
		std::cout << "ACTION: edit->Zoom in" << std::endl;
	}


	void MainWindow::viewZoomOut()
	{
		std::cout << "ACTION: edit->Zoom out" << std::endl;
	}


	void MainWindow::viewZoom1to1()
	{
		std::cout << "ACTION: edit->Zoom 1 to 1" << std::endl;
	}


	void MainWindow::viewZoomToFit()
	{
		std::cout << "ACTION: edit->Zoom to fit" << std::endl;
	}


	void MainWindow::helpAbout()
	{
		QMessageBox aboutBox( QMessageBox::NoIcon,
				      tr("About gLabels"),
				      tr("<h2>gLabels-qt</h2>"
					 "<p>x.x.x</p>"
					 "<p>A label and business card creation program.</p>"
					 "<font size=\"smaller\">"
					 "<p><a href=\"http://glabels.org\">Homepage</a></p>"
					 "<p>Copyright &copy; 2013 Jim Evins <evins@snaught.com></p>"
					 "</font>"),
				      QMessageBox::Ok,
				      this );
		aboutBox.setIconPixmap( QPixmap( ":/images/glabels-logo.png" ) );

		aboutBox.exec();
	}

}
