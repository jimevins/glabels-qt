/*  SubstitutionField.cpp
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

#include "SubstitutionField.h"

#include <QTextStream>


namespace glabels
{

	merge::SubstitutionField::SubstitutionField( const QString& string )
	{
		QStringRef s(&string);
		parseSubstitutionField( s );
	}


	QString merge::SubstitutionField::evaluate( const merge::Record& record ) const
	{
		QString value = mDefaultValue;

		if ( record.contains(mFieldName) )
		{
			value = record[mFieldName];
		}

		if ( mFormatType.isNull() )
		{
			return value;
		}
		else
		{
			return formatValue( value );
		}
	}


	QString merge::SubstitutionField::fieldName() const
	{
		return mFieldName;
	}


	QString merge::SubstitutionField::defaultValue() const
	{
		return mDefaultValue;
	}


	QString merge::SubstitutionField::format() const
	{
		return mFormat;
	}


	QChar merge::SubstitutionField::formatType() const
	{
		return mFormatType;
	}


	QString merge::SubstitutionField::formatValue( const QString& value ) const
	{
			switch (mFormatType.unicode())
			{
				
			case 'd':
			case 'i':
				return QString::asprintf( mFormat.toStdString().c_str(),
				                          value.toLongLong(nullptr,0) );
				break;
				

			case 'u':
			case 'x':
			case 'X':
			case 'o':
				return QString::asprintf( mFormat.toStdString().c_str(),
				                          value.toULongLong(nullptr,0) );
				break;

			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
				return QString::asprintf( mFormat.toStdString().c_str(),
				                          value.toDouble() );
				break;

			case 's':
				return QString::asprintf( mFormat.toStdString().c_str(),
				                          value.toStdString().c_str() );
				break;

			default:
				// Invalid format
				return "";
				break;

			}
	}
	

	void merge::SubstitutionField::parseSubstitutionField( QStringRef& s )
	{
		if ( s.startsWith( "${" ) )
		{
			s = s.mid(2);
			parseFieldName( s );

			while ( s.size() && s[0] == ':' )
			{
				s = s.mid(1);
				parseModifier( s );
			}

			if ( s.size() && s[0] == '}' )
			{
				s = s.mid(1);

				if ( s.size() )
				{
					// Invalid -- extraneous input
				}
			}
			else
			{
				// Invalid -- expected '}'
			}

		}
		else
		{
			// Invalid -- expected '${'
		}
	}


	void merge::SubstitutionField::parseFieldName( QStringRef& s )
	{
		while ( s.size() && (s[0].isDigit() || s[0].isLetter() || s[0] == '_' || s[0] == '-') )
		{
			mFieldName.append( s[0] );
			s = s.mid(1);
		}
	}


	void merge::SubstitutionField::parseModifier( QStringRef& s )
	{
		if ( s.size() && s[0] == '%' )
		{
			s = s.mid(1);
			parseFormatModifier( s );
		}
		else if ( s.size() && s[0] == '=' )
		{
			s = s.mid(1);
			parseDefaultValueModifier( s );
		}
		else
		{
			// Invalid -- unrecognized modifier, expecting one of '%' or '='
		}
	}


	void merge::SubstitutionField::parseDefaultValueModifier( QStringRef& s )
	{
		while ( s.size() && s[0] != ':' && s[0] != '}' )
		{
			if ( s[0] == '\\' )
			{
				s = s.mid(1); // Skip escape
				if ( s.size() )
				{
					mDefaultValue.append( s[0] );
					s = s.mid(1);
				}
				{
					// Invalid -- end of string encountered during escape
				}
			}
			else
			{
				mDefaultValue.append( s[0] );
				s = s.mid(1);
			}
		}
	}


	void merge::SubstitutionField::parseFormatModifier( QStringRef& s )
	{
		mFormat = "%";

		mFormat += parseFormatFlags( s );
		mFormat += parseFormatWidth( s );
		
		if ( s.size() && s[0] == '.' )
		{
			s = s.mid(1);
			mFormat += "." + parseFormatPrecision( s );
		}

		mFormatType = parseFormatType( s );
		mFormat += mFormatType;
	}


	QString merge::SubstitutionField::parseFormatFlags( QStringRef& s )
	{
		QString flags;
		
		while ( s.size() && QString( "-+ 0" ).contains( s[0] ) )
		{
			flags.append( s[0] );
			s = s.mid(1);
		}

		return flags;
	}


	QString merge::SubstitutionField::parseFormatWidth( QStringRef& s )
	{
		return parseNaturalInteger( s );
	}


	QString merge::SubstitutionField::parseFormatPrecision( QStringRef& s )
	{
		return parseNaturalInteger( s );
	}


	QChar merge::SubstitutionField::parseFormatType( QStringRef& s )
	{
		QChar type = 0;

		if ( s.size() && QString( "diufFeEgGxXos" ).contains( s[0] ) )
		{
			type = s[0];
			s = s.mid(1);
		}

		return type;
	}


	QString merge::SubstitutionField::parseNaturalInteger( QStringRef& s )
	{
		QString value = "";
		
		if ( s.size() && s[0] >= '1' && s[0] <= '9' )
		{
			value += s[0];
			s = s.mid(1);

			while ( s.size() && s[0].isDigit() )
			{
				value += s[0];
				s = s.mid(1);
			}
		}
		
		return value;
	}


} // namespace glabels
