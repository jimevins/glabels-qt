/*  XmlUtil.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#ifndef glabels_XmlUtil_h
#define glabels_XmlUtil_h

#include <QString>
#include <QDomElement>
#include <stdint.h>

#include "Distance.h"


namespace glabels
{

	class XmlUtil
	{
	private:
		XmlUtil();

		
	public:

		static void init();

		static Distance::Units units();
		static void setUnits( Distance::Units units );

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

		static Distance getLengthAttr( const QDomElement& node,
		                               const QString&     name,
		                               const Distance&    default_value );

		static void     setStringAttr( QDomElement&   node,
		                               const QString& name,
		                               const QString& value );

		static void     setDoubleAttr( QDomElement&   node,
		                               const QString& name,
		                               double         value );

		static void     setBoolAttr( QDomElement&   node,
		                             const QString& name,
		                             bool           value );

		static void     setIntAttr( QDomElement&   node,
		                            const QString& name,
		                            int            value );

		static void     setUIntAttr( QDomElement&   node,
		                             const QString& name,
		                             uint32_t       value );

		static void     setLengthAttr( QDomElement&    node,
		                               const QString&  name,
		                               const Distance& value );

	private:
		static Distance::Units mUnits;

	};

}

#endif // glabels_XmlUtil_h
