/*  EnumUtil.cpp
 *
 *  Copyright (C) 2015  Jim Evins <evins@snaught.com>
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

#include "EnumUtil.h"


namespace EnumUtil
{

	QString weightToString( QFont::Weight weight )
	{
		switch (weight)
		{
		case QFont::Bold:
			return "bold";
			break;
		default:
			return "normal";
			break;
		}
	}


	QFont::Weight stringToWeight( const QString& string )
	{
		if ( string == "bold" )
		{
			return QFont::Bold;
		}
		else
		{
			return QFont::Normal;
		}
	}


	QString hAlignToString( Qt::Alignment align )
	{
		switch (align)
		{
		case Qt::AlignRight:
			return "right";
			break;
		case Qt::AlignHCenter:
			return "center";
			break;
		default:
			return "left";
			break;
		}
	}


	Qt::Alignment stringToHAlign( const QString& string )
	{
		if ( string == "right" )
		{
			return Qt::AlignRight;
		}
		else if ( string == "center" )
		{
			return Qt::AlignHCenter;
		}
		else
		{
			return Qt::AlignLeft;
		}
	}


	QString vAlignToString( Qt::Alignment align )
	{
		switch (align)
		{
		case Qt::AlignBottom:
			return "bottom";
			break;
		case Qt::AlignVCenter:
			return "center";
			break;
		default:
			return "top";
			break;
		}
	}


	Qt::Alignment stringToVAlign( const QString& string )
	{
		if ( string == "bottom" )
		{
			return Qt::AlignBottom;
		}
		else if ( string == "center" )
		{
			return Qt::AlignVCenter;
		}
		else
		{
			return Qt::AlignTop;
		}
	}

}
