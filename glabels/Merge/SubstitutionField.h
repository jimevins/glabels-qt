/*  SubstitutionField.h
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

#ifndef glabels_SubstitutionField_h
#define glabels_SubstitutionField_h


#include "Record.h"

#include <QString>
#include <QStringRef>


namespace glabels
{

	namespace merge
	{

		class SubstitutionField
		{
		public:
			SubstitutionField() = default;
			SubstitutionField( const QString& string );

			QString evaluate( const merge::Record& record ) const;
		
			QString fieldName() const;
			QString defaultValue() const;
			QString format() const;
			QChar   formatType() const;

		private:
			QString formatValue( const QString& value ) const;
			void parseSubstitutionField( QStringRef& s );
			void parseFieldName( QStringRef& s );
			void parseModifier( QStringRef& s );
			void parseDefaultValueModifier( QStringRef& s );
			void parseFormatModifier( QStringRef& s );

			QString parseFormatFlags( QStringRef& s );
			QString parseFormatWidth( QStringRef& s );
			QString parseFormatPrecision( QStringRef& s );
			QChar   parseFormatType( QStringRef& s );
			QString parseNaturalInteger( QStringRef& s );
		
			QString mFieldName;

			QString mDefaultValue;

			QString      mFormat;
			QChar        mFormatType;
		};

	}
	
}


#endif // glabels_SubstitutionField_h
