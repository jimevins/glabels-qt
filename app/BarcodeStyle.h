/*  BarcodeStyle.h
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

#ifndef glabels_BarcodeStyle_h
#define glabels_BarcodeStyle_h

#include <QString>
#include <algorithm>

namespace glabels
{

	class BarcodeStyle
	{

	public:
		BarcodeStyle ()
			: m_id( "" ),
			  m_name( "" ),
			  m_can_text( false ),
			  m_text_optional( false ),
			  m_can_checksum( false ),
			  m_checksum_optional( false ),
			  m_default_digits( "" ),
			  m_can_freeform( false ),
			  m_prefered_n( 0 )
		{
		}


		BarcodeStyle ( const QString &id,
			       const QString &name,
			       bool           can_text,
			       bool           text_optional,
			       bool           can_checksum,
			       bool           checksum_optional,
			       const QString &default_digits,
			       bool           can_freeform,
			       int            prefered_n )
			: m_id( id ),
			  m_name( name ),
			  m_can_text( can_text ),
			  m_text_optional( text_optional ),
			  m_can_checksum( can_checksum ),
			  m_checksum_optional( checksum_optional ),
			  m_default_digits( default_digits ),
			  m_can_freeform( can_freeform ),
			  m_prefered_n( prefered_n )
		{
		}


		QString id() { return m_id; }

		QString name() { return m_name; }

		bool can_text() { return m_can_text; }

		bool text_optional() { return m_text_optional; }

		bool can_checksum() { return m_can_checksum; }

		bool checksum_optional() { return m_checksum_optional; }

		QString default_digits() { return m_default_digits; }

		bool can_freeform() { return m_can_freeform; }

		int prefered_n() { return m_prefered_n; }


		QString example_digits( int n )
		{
			if ( m_can_freeform )
			{
				return QString( std::max( n, 1 ), QChar('0') );
			}
			else
			{
				return m_default_digits;
			}
		}

	private:
		QString m_id;
		QString m_name;
		bool    m_can_text;
		bool    m_text_optional;
		bool    m_can_checksum;
		bool    m_checksum_optional;
		QString m_default_digits;
		bool    m_can_freeform;
		int     m_prefered_n;

	};


}

#endif // glabels_BarcodeStyle_h
