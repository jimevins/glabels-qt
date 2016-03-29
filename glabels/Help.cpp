/*  Help.cpp
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

#include "Help.h"

#include <QMessageBox>

#include <iostream>


///
/// Display Help Contents
///
void Help::displayContents( QWidget *parent )
{
	std::cout << "TODO: Help::displayContents" << std::endl;
}


///
/// Display Help->About Dialog
///
void Help::displayAbout( QWidget *parent )
{
	QMessageBox aboutBox( QMessageBox::NoIcon,
			      QMessageBox::tr("About gLabels"),
			      QMessageBox::tr("<p><span style='font-size:24pt; font-weight:600;'>gLabels  </span><span style='font-size:16pt; color:#909090;'>Label Designer</span></p>"
					      "<p>x.x.x</p>"
					      "<p>A program to create labels and business cards.</p>"
					      "<font size=\"smaller\">"
					      "<p><a href=\"http://glabels.org\">Homepage</a></p>"
					      "<p>Copyright &copy; 2016 Jim Evins <evins@snaught.com></p>"
					      "</font>"),
			      QMessageBox::Ok,
			      parent );
	aboutBox.setIconPixmap( QPixmap( ":/images/glabels-logo.png" ) );

	aboutBox.exec();
}
