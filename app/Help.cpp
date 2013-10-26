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


namespace gLabels
{

	namespace Help
	{

		void displayContents( QWidget *parent )
		{
			std::cout << "TODO: Help::displayContents" << std::endl;
		}


		void displayAbout( QWidget *parent )
		{
			QMessageBox aboutBox( QMessageBox::NoIcon,
					      QMessageBox::tr("About gLabels"),
					      QMessageBox::tr("<h2>gLabels-qt</h2>"
							      "<p>x.x.x</p>"
							      "<p>A label and business card creation program.</p>"
							      "<font size=\"smaller\">"
							      "<p><a href=\"http://glabels.org\">Homepage</a></p>"
							      "<p>Copyright &copy; 2013 Jim Evins <evins@snaught.com></p>"
							      "</font>"),
					      QMessageBox::Ok,
					      parent );
			aboutBox.setIconPixmap( QPixmap( ":/images/glabels-logo.png" ) );

			aboutBox.exec();
		}

	}

}

