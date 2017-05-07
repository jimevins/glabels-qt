/*  RawText.cpp
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#include "RawText.h"

#include <QRegularExpression>

namespace glabels
{

	///
	/// Constructor from QString
	///
	RawText::RawText( const QString& string ) : mString(string)
	{
	}


	///
	/// Constructor from C string operator
	///
	RawText::RawText( const char* cString ) : mString(QString(cString))
	{
	}

	
	///
	/// Access as QString
	///
	QString RawText::toString() const
	{
		return mString;
	}
	

	///
	/// Access as std::string
	///
	std::string RawText::toStdString() const
	{
		return mString.toStdString();
	}
	

	///
	/// Expand all place holders
	///
	QString RawText::expand( merge::Record* record ) const
	{
		QString text = mString;
		
		if ( record )
		{
			foreach ( QString key, record->keys() )
			{
				// Special case: remove line when it contains only an empty field.
				// e.g. an optional ${ADDR2} line.  To bypass this case, include
				// whitespace at end of line.
				if ( record->value(key).isEmpty() )
				{
					QStringList v = text.split( '\n' );
					v.removeAll( "${"+key+"}" );
					text = v.join( '\n' );
				}

				// Nominal case: simple replacement
				text.replace( "${"+key+"}", record->value(key) );
			}
		}

		return text;
	}


	///
	/// Does raw text contain place holders?
	///
	bool RawText::hasPlaceHolders() const
	{
		QRegularExpression re("\\${\\w+}");
		return mString.contains( re );
	}


	///
	/// Is raw text empty?
	///
	bool RawText::isEmpty() const
	{
		return mString.isEmpty();
	}

} // namespace glabels
