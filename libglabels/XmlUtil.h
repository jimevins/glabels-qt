/*  XmlUtil.h
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

#ifndef libglabels_XmlUtil_h
#define libglabels_XmlUtil_h

#include <QString>
#include <QDomElement>
#include <stdint.h>

#include "Units.h"


namespace libglabels
{

	class XmlUtil
	{
	private:
		XmlUtil()
		{
			mDefaultUnits = Units::point();
		}

	public:

		static void init()
		{
			static XmlUtil *xmlUtil = new XmlUtil();
		}

		static const Units *defaultUnits() { return mDefaultUnits; }
		static void setDefaultUnits( Units *defaultUnits ) { mDefaultUnits = defaultUnits; }

		static QString  getAttr( const QDomElement &node, const QString &name, const char *default_value );
		static QString  getAttr( const QDomElement &node, const QString &name, const QString &default_value );
		static double   getAttr( const QDomElement &node, const QString &name, double default_value );
		static bool     getAttr( const QDomElement &node, const QString &name, bool default_value );
		static int      getAttr( const QDomElement &node, const QString &name, int default_value );
		static uint32_t getAttr( const QDomElement &node, const QString &name, uint32_t default_value );

		static QString  getAttrI18n( const QDomElement &node, const QString &name, const QString &default_value );
		static double   getAttrLength( const QDomElement &node, const QString &name, double default_value );

		static void     setAttr( const QDomElement &node, const QString &name, const char *value );
		static void     setAttr( const QDomElement &node, const QString &name, const QString &value );
		static void     setAttr( const QDomElement &node, const QString &name, double value );
		static void     setAttr( const QDomElement &node, const QString &name, bool value );
		static void     setAttr( const QDomElement &node, const QString &name, int value );
		static void     setAttr( const QDomElement &node, const QString &name, uint32_t value );

		static void     setAttrLength( const QDomElement &node, const QString &name, double value );

	private:
		static Units *mDefaultUnits;

	};

}

#endif // libglabels_XmlUtil_h
