/*  XmlUtil.cpp
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

#include "XmlUtil.h"


#include <QTextStream>
#include <QCoreApplication>
#include <QtDebug>


namespace glabels
{

	//
	// Static data
	//
	Units XmlUtil::mUnits;


	XmlUtil::XmlUtil()
	{
		mUnits = Units(Units::PT);
	}


	void XmlUtil::init()
	{
		static XmlUtil* xmlUtil = new XmlUtil();
	}


	Units XmlUtil::units()
	{
		init();

		return mUnits;
	}


	void XmlUtil::setUnits( const Units& units )
	{
		init();

		mUnits = units;
	}


	QString XmlUtil::getStringAttr( const QDomElement& node,
					const QString&     name,
					const QString&     default_value )
	{
		init();

		return node.attribute( name, default_value );
	}


	double XmlUtil::getDoubleAttr( const QDomElement& node,
				       const QString&     name,
				       double             default_value )
	{
		init();

		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			double value = valueString.toDouble(& ok );

			if ( !ok )
			{
				qWarning() << "Error: bad double value in attribute "
					   << node.tagName() << ":" << name << "=" << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	bool XmlUtil::getBoolAttr( const QDomElement& node,
				   const QString&     name,
				   bool               default_value )
	{
		init();

		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			int intValue = valueString.toInt();

			if ( (valueString == "True") ||
			     (valueString == "TRUE") ||
			     (valueString == "true") ||
			     (intValue == 1) )
			{
				return true;
			}

			if ( (valueString == "False") ||
			     (valueString == "FALSE") ||
			     (valueString == "false") ||
			     (intValue == 0) )
			{
				return false;
			}

			qWarning() << "Error: bad boolean value in attribute "
				   << node.tagName() << ":" << name << "=" << valueString;
			return default_value;
		}

		return default_value;
	}


	int XmlUtil::getIntAttr( const QDomElement& node,
				 const QString&     name,
				 int                default_value )
	{
		init();

		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			int value = valueString.toInt(& ok );

			if ( !ok )
			{
				qWarning() << "Error: bad integer value in attribute "
					   << node.tagName() << ":" << name << "=" << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	uint32_t XmlUtil::getUIntAttr( const QDomElement& node,
				       const QString&     name,
				       uint32_t           default_value )
	{
		init();

		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			uint32_t value = valueString.toUInt(& ok, 0 );

			if ( !ok )
			{
				qWarning() << "Error: bad unsigned integer value in attribute "
					   << node.tagName() << ":" << name << "=" << valueString;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	QString  XmlUtil::getI18nAttr( const QDomElement& node,
				       const QString&     name,
				       const QString&     default_value )
	{
		init();

		QString i18nString = node.attribute( QString("_").append(name), "" );

		if ( i18nString == "" )
		{
			return node.attribute( name, default_value );
		}

		return QCoreApplication::translate( "XmlStrings", i18nString.toUtf8().constData() );
	}


	Distance XmlUtil::getLengthAttr( const QDomElement& node,
					 const QString&     name,
					 const Distance&    default_value )
	{
		init();

		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			double value;
			QString unitsString;
			QTextStream valueStream( &valueString, QIODevice::ReadOnly );

			valueStream >> value >> unitsString;

			if ( !unitsString.isEmpty() && !Units::isIdValid( unitsString ) )
			{
				qWarning() << "Error: bad length value in attribute "
					   << node.tagName() << ":" <<  name << "=" << valueString;
			}

			return Distance( value, unitsString );
		}

		return default_value;
	}


	void XmlUtil::setStringAttr( QDomElement&   node,
				     const QString& name,
				     const QString& value )
	{
		init();

		node.setAttribute( name, value );
	}


	void XmlUtil::setDoubleAttr( QDomElement&   node,
				     const QString& name,
				     double         value )
	{
		init();

		node.setAttribute( name, QString::number(value) );
	}


	void XmlUtil::setBoolAttr( QDomElement&   node,
				   const QString& name,
				   bool           value )
	{
		init();

		node.setAttribute( name, value ? "true" : "false" );
	}


	void XmlUtil::setIntAttr( QDomElement&   node,
				  const QString& name,
				  int            value )
	{
		init();

		node.setAttribute( name, QString::number(value) );
	}


	void XmlUtil::setUIntAttr( QDomElement&   node,
				   const QString& name,
				   uint32_t       value )
	{
		init();

		node.setAttribute( name, "0x" + QString::number(value, 16) );
	}


	void XmlUtil::setLengthAttr( QDomElement&    node,
				     const QString&  name,
				     const Distance& value )
	{
		init();

		node.setAttribute( name, QString::number(value.inUnits(mUnits)) + mUnits.toIdString() );
	}

}
