/*  AboutDialog.cpp
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#include "AboutDialog.h"

#include <QUrl>
#include <QDesktopServices>
#include <QtDebug>


///
/// Constructor
///
AboutDialog::AboutDialog( QWidget *parent )
	: QDialog(parent)
{
	setupUi( this );

	QString subtitle = tr("Label Designer");
	QString version = "x.x.x";
	QString description = tr("A program to create labels and business cards.");

	QString markup = "<p><span style='font-size:24pt; font-weight:600;'>gLabels  </span><span style='font-size:16pt; color:#333333;'>"
		+ subtitle + "</span></p>"
		+ "<p>" + version + "</p>"
		+ "<p>" + description + "</p>"
		+ "<p>Copyright &copy; 2016 Jim Evins <evins@snaught.com></p>";

	aboutLabel->setText( markup );
}


///
/// "License" Button Clicked Slot
///
void AboutDialog::onLicenseButtonClicked()
{
	QDesktopServices::openUrl( QUrl("http://www.gnu.org/licenses/gpl-3.0.txt") );
}


///
/// "Website" Button Clicked Slot
///
void AboutDialog::onWebsiteButtonClicked()
{
	QDesktopServices::openUrl( QUrl("http://glabels.org/") );
}
