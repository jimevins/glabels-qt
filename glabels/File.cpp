/*  File.cpp
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

#include "File.h"

#include "MainWindow.h"
#include "LabelModel.h"
#include "NewLabelDialog.h"
#include "XmlLabelParser.h"
#include "XmlLabelCreator.h"
#include "FileUtil.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>


namespace glabels
{
	/// @TODO keep track of cwd between open/save dialogs

	///
	/// New Label Dialog
	///
	void File::newLabel( MainWindow *window )
	{
		NewLabelDialog newDialog( window );
		newDialog.exec();

		const libglabels::Template* tmplate = newDialog.tmplate();
		if ( tmplate )
		{
			LabelModel* label = new LabelModel();
			label->setTmplate( tmplate );
			label->setRotate( newDialog.rotate() );

			if ( window->isEmpty() )
			{
				window->setModel( label );
			}
			else
			{
				MainWindow *newWindow = new MainWindow();
				newWindow->setModel( label );
				newWindow->show();
			}
		}
	}


	///
	/// Open File Dialog
	///
	void File::open( MainWindow *window )
	{
		QString fileName =
			QFileDialog::getOpenFileName( window,
						      tr("Open label"),
						      ".",
						      tr("glabels files (*.glabels);;All files (*)")
				                    );
		if ( !fileName.isEmpty() )
		{
			LabelModel *label = XmlLabelParser::readFile( fileName );
			if ( label )
			{
				label->setFileName( fileName );
				
				if ( window->isEmpty() )
				{
					window->setModel( label );
				}
				else
				{
					MainWindow *newWindow = new MainWindow();
					newWindow->setModel( label );
					newWindow->show();
				}
			}
			else
			{
				QMessageBox msgBox;
				msgBox.setText( tr("Unable to open \"") + fileName + tr("\".") );
				msgBox.setStandardButtons( QMessageBox::Ok );
				msgBox.setDefaultButton( QMessageBox::Ok );
				msgBox.exec();
			}
		}
	}


	///
	/// Save file
	///
	bool File::save( MainWindow *window )
	{
		if ( window->model()->fileName().isEmpty() )
		{
			return saveAs( window );
		}

		if ( !window->model()->isModified() )
		{
			return true;
		}

		XmlLabelCreator::writeFile( window->model(), window->model()->fileName() );
		return true;
	}


	///
	/// Save file as
	///
	bool File::saveAs( MainWindow *window )
	{
		QString rawFileName =
			QFileDialog::getSaveFileName( window,
						      tr("Save Label As"),
						      ".",
						      tr("glabels files (*.glabels);;All files (*)"),
						      0,
						      QFileDialog::DontConfirmOverwrite
				                    );
		if ( !rawFileName.isEmpty() )
		{
			QString fileName = FileUtil::addExtension( rawFileName, ".glabels" );
			
			
			if ( QFileInfo(fileName).exists() )
			{
				QMessageBox msgBox( window );
				msgBox.setWindowTitle( tr("Save Label As") );
				msgBox.setIcon( QMessageBox::Warning );
				msgBox.setText( tr("%1 already exists.").arg(fileName) );
				msgBox.setInformativeText( tr("Do you want to replace it?") );
				msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
				msgBox.setDefaultButton( QMessageBox::No );

				if ( msgBox.exec() == QMessageBox::No )
				{
					return saveAs( window );
				}
			}
			
			XmlLabelCreator::writeFile( window->model(), fileName );
			window->model()->setFileName( fileName );
			return true;
		}

		return false;
	}


	///
	/// Print file
	///
	void File::print( MainWindow *window )
	{
		qDebug() << "ACTION: file->print";
	}


	///
	/// Close file
	///
	void File::close( MainWindow *window )
	{
		bool closeFlag = true;

		if ( !window->isEmpty() )
		{
			QMessageBox msgBox;
			msgBox.setText( tr("The document ") + window->model()->shortName() + tr(" has been modified.") );
			msgBox.setInformativeText( tr("Do you want to save your changes?") );
			msgBox.setStandardButtons( QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
			msgBox.setDefaultButton( QMessageBox::Save );

			int ret = msgBox.exec();

			switch (ret) {
			case QMessageBox::Save:
				// Save was clicked
				closeFlag = save( window );
				break;
			case QMessageBox::Discard:
				// Don't Save was clicked
				closeFlag = true;
				break;
			case QMessageBox::Cancel:
				// Cancel was clicked
				closeFlag = false;
				break;
			default:
				// should never be reached
				closeFlag = false;
				break;
			}
		}

		if ( closeFlag )
		{
			window->close();
		}
	}


	///
	/// Exit, closing all windows
	///
	void File::exit()
	{
		foreach ( MainWindow* window, MainWindow::windowList() )
		{
			close( window );
		}
	}


}

