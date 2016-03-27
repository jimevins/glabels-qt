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

#include <QIcon>

#include "TemplatePickerItem.h"


///
/// Constructor
///
TemplatePicker::TemplatePicker( QWidget *parent ) : QListWidget(parent)
{
	setViewMode( QListView::IconMode );
	setResizeMode( QListView::Adjust );
	setSpacing( 24 );
	setWordWrap( true );
	setUniformItemSizes( true );
	setIconSize( QSize(glabels::TEMPLATE_PREVIEW_SIZE, glabels::TEMPLATE_PREVIEW_SIZE) );
}


///
/// Set List of Templates to Pick From
///
void TemplatePicker::setTemplates( const QList <glabels::Template*> &tmplates )
{
	foreach (glabels::Template *tmplate, tmplates)
	{
		TemplatePickerItem *item = new TemplatePickerItem( tmplate, this );
	}
}


///
/// Apply Filter to Narrow Template Choices
///
void TemplatePicker::applyFilter( const QString &searchString,
				  bool isoMask, bool usMask, bool otherMask )
{
	foreach ( QListWidgetItem *item, findItems( "*", Qt::MatchWildcard ) )
	{
		TemplatePickerItem *tItem = dynamic_cast<TemplatePickerItem *>(item);

		bool sizeMask =
			(isoMask   && tItem->tmplate()->isSizeIso())   ||
			(usMask    && tItem->tmplate()->isSizeUs())    ||
			(otherMask && tItem->tmplate()->isSizeOther());

		if ( tItem->tmplate()->name().contains( searchString, Qt::CaseInsensitive ) && sizeMask )
		{
			item->setHidden( false );
		}
		else
		{
			item->setHidden( true );
			item->setSelected( false );
		}
	}
}


///
/// Get Currently Selected Template
///
const glabels::Template *TemplatePicker::selectedTemplate()
{
	QList<QListWidgetItem *> items = selectedItems();
	if ( items.isEmpty() )
	{
		return NULL;
	}
	else
	{
		TemplatePickerItem *tItem = dynamic_cast<TemplatePickerItem*>(items.first());
		return tItem->tmplate();
	}
}
