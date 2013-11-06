/*  TemplatePicker.cpp
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

#include "TemplatePicker.h"

#include <QListWidgetItem>
#include <QIcon>


namespace gLabels
{

	TemplatePicker::TemplatePicker( QWidget *parent ) : QListWidget(parent)
	{
		setViewMode( QListView::IconMode );
		setResizeMode( QListView::Adjust );
		setSpacing( 24 );
		setWordWrap( true );
		setUniformItemSizes( true );
		setIconSize( QSize(libglabels::TEMPLATE_PREVIEW_SIZE, libglabels::TEMPLATE_PREVIEW_SIZE) );
	}


	void TemplatePicker::setTemplates( const QList <libglabels::Template*> &tmplates )
	{
		foreach (libglabels::Template *tmplate, tmplates)
		{
			QListWidgetItem *item = new QListWidgetItem( tmplate->name(), this );
			item->setIcon( QIcon(tmplate->preview()) );
		}
	}
}

