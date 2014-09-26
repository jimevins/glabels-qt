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

		static void setDefaultUnits( Units *defaultUnits )
		{
			mDefaultUnits = defaultUnits;
		}

		static QString  getStringAttr( const QDomElement& node,
		                               const QString&     name,
		                               const QString&     default_value );

		static double   getDoubleAttr( const QDomElement& node,
		                               const QString&     name,
		                               double             default_value );

		static bool     getBoolAttr( const QDomElement& node,
		                             const QString&     name,
		                             bool               default_value );

		static int      getIntAttr( const QDomElement& node,
		                            const QString&     name,
		                            int                default_value );

		static uint32_t getUIntAttr( const QDomElement& node,
		                             const QString&     name,
		                             uint32_t           default_value );

		static QString  getI18nAttr( const QDomElement& node,
		                             const QString&     name,
		                             const QString&     default_value );

		static double   getLengthAttr( const QDomElement& node,
		                               const QString&     name,
		                               double             default_value );

		static void     setStringAttr( const QDomElement& node,
		                               const QString&     name,
		                               const QString&     value );

		static void     setDoubleAttr( const QDomElement& node,
		                               const QString&     name,
		                               double             value );

		static void     setBoolAttr( const QDomElement& node,
		                             const QString&     name,
		                             bool               value );

		static void     setIntAttr( const QDomElement& node,
		                            const QString&     name,
		                            int                value );

		static void     setUIntAttr( const QDomElement& node,
		                             const QString&     name,
		                             uint32_t           value );

		static void     setLengthAttr( const QDomElement& node,
		                               const QString& name,
		                               double value );

	private:
		static Units *mDefaultUnits;

	};

}

#endif // libglabels_XmlUtil_h
