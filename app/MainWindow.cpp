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


	void MainWindow::about()
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


	void MainWindow::createActions()
	{
		aboutAction = new QAction( tr("&About..."), this );
		aboutAction->setStatusTip( tr("About gLabels") );
		connect( aboutAction, SIGNAL(triggered()), this, SLOT(about()) );
	}


	void MainWindow::createMenus()
	{
		helpMenu = menuBar()->addMenu( tr("&Help") );
		helpMenu->addAction( aboutAction );
	}

}
