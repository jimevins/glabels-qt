/*  TemplatePicker.h
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

#ifndef glabels_TemplatePicker_h
#define glabels_TemplatePicker_h

#include <QListWidget>

#include <QList>

#include "libglabels/Template.h"


namespace glabels
{

	class TemplatePicker : public QListWidget
	{
		Q_OBJECT

	public:
		TemplatePicker( QWidget *parent = 0 );

		void setTemplates( const QList <libglabels::Template*> &tmplates );

		void applyFilter( const QString &searchString, bool isoMask, bool usMask, bool otherMask );

		const libglabels::Template *selectedTemplate();

	};

}

#endif // glabels_TemplatePicker_h
