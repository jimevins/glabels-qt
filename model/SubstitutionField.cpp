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
	namespace model
	{

		SubstitutionField::SubstitutionField()
			: mFormatType(0), mNewLine(false)
		{
		}


		SubstitutionField::SubstitutionField( const QString& string )
			: mFormatType(0), mNewLine(false)
		{
			QStringRef s(&string);
			parse( s, *this );
		}


		QString SubstitutionField::evaluate( const merge::Record* record,
		                                     const Variables* variables ) const
		{
			QString value = mDefaultValue;

			bool haveRecordField = record &&
				record->contains(mFieldName) &&
				!record->value(mFieldName).isEmpty();
			bool haveVariable = variables &&
				variables->contains(mFieldName) &&
				!(*variables)[mFieldName].value().isEmpty();

			if ( haveRecordField )
			{
				value = record->value(mFieldName);
			}
			else if ( haveVariable )
			{
				value = (*variables)[mFieldName].value();
			}

			if ( !mFormatType.isNull() )
			{
				value = formatValue( value );
			}

			if ( mNewLine && (haveRecordField || haveVariable) )
			{
				value = "\n" + value;
			}

			return value;
		}


		QString SubstitutionField::fieldName() const
		{
			return mFieldName;
		}


		QString SubstitutionField::defaultValue() const
		{
			return mDefaultValue;
		}


		QString SubstitutionField::format() const
		{
			return mFormat;
		}


		QChar SubstitutionField::formatType() const
		{
			return mFormatType;
		}


		bool SubstitutionField::newLine() const
		{
			return mNewLine;
		}


		bool SubstitutionField::parse( QStringRef& s, SubstitutionField& field )
		{
			QStringRef sTmp = s;
		
			if ( sTmp.startsWith( "${" ) )
			{
				sTmp = sTmp.mid(2);

				if ( parseFieldName( sTmp, field ) )
				{
					while ( sTmp.size() && sTmp[0] == ':' )
					{
						sTmp = sTmp.mid(1);
						if ( !parseModifier( sTmp, field ) )
						{
							return false;
						}
					}

					if ( sTmp.size() && sTmp[0] == '}' )
					{
						sTmp = sTmp.mid(1);

						// Success.  Update s.
						s = sTmp;
						return true;
					}
				}
			}

			return false;
		}


		bool SubstitutionField::parseFieldName( QStringRef& s, SubstitutionField& field )
		{
			bool success = false;
		
			while ( s.size() && (s[0].isDigit() || s[0].isLetter() || s[0] == '_' || s[0] == '-') )
			{
				field.mFieldName.append( s[0] );
				s = s.mid(1);

				success = true;
			}

			return success;
		}

	
		bool SubstitutionField::parseModifier( QStringRef& s, SubstitutionField& field )
		{
			bool success = false;
		
			if ( s.size() && s[0] == '%' )
			{
				s = s.mid(1);
				success = parseFormatModifier( s, field );
			}
			else if ( s.size() && s[0] == '=' )
			{
				s = s.mid(1);
				success = parseDefaultValueModifier( s, field );
			}
			else if ( s.size() && s[0] == 'n' )
			{
				s = s.mid(1);
				success = parseNewLineModifier( s, field );
			}

			return success;
		}

	
		bool SubstitutionField::parseDefaultValueModifier( QStringRef& s, SubstitutionField& field )
		{
			field.mDefaultValue.clear();

			while ( s.size() && !QString( ":}" ).contains( s[0] ) )
			{
				if ( s[0] == '\\' )
				{
					s = s.mid(1); // Skip escape
					if ( s.size() )
					{
						field.mDefaultValue.append( s[0] );
						s = s.mid(1);
					}
				}
				else
				{
					field.mDefaultValue.append( s[0] );
					s = s.mid(1);
				}
			}

			return true;
		}

	
		bool SubstitutionField::parseFormatModifier( QStringRef& s, SubstitutionField& field )
		{
			field.mFormat = "%";

			parseFormatFlags( s, field );
			parseFormatWidth( s, field );
		
			if ( s.size() && s[0] == '.' )
			{
				field.mFormat += ".";
				s = s.mid(1);
				parseFormatPrecision( s, field );
			}

			parseFormatType( s, field );

			return true; // Don't let invalid formats kill entire SubstitutionField
		}

	
		bool SubstitutionField::parseFormatFlags( QStringRef& s, SubstitutionField& field )
		{
			while ( s.size() && QString( "-+ 0" ).contains( s[0] ) )
			{
				field.mFormat += s[0];
				s = s.mid(1);
			}

			return true;
		}

	
		bool SubstitutionField::parseFormatWidth( QStringRef& s, SubstitutionField& field )
		{
			return parseNaturalInteger( s, field );
		}


		bool SubstitutionField::parseFormatPrecision( QStringRef& s, SubstitutionField& field )
		{
			return parseNaturalInteger( s, field );
		}

	
		bool SubstitutionField::parseFormatType( QStringRef& s, SubstitutionField& field )
		{
			bool success = false;

			if ( s.size() && QString( "diufFeEgGxXos" ).contains( s[0] ) )
			{
				field.mFormatType = s[0];
				field.mFormat += s[0];
				s = s.mid(1);
				success = true;
			}

			return success;
		}

	
		bool SubstitutionField::parseNaturalInteger( QStringRef& s, SubstitutionField& field )
		{
			bool success = false;

			if ( s.size() && s[0] >= '1' && s[0] <= '9' )
			{
				field.mFormat += s[0];
				s = s.mid(1);

				while ( s.size() && s[0].isDigit() )
				{
					field.mFormat += s[0];
					s = s.mid(1);
				}

				success = true;
			}
		
			return success;
		}
	

		bool SubstitutionField::parseNewLineModifier( QStringRef& s, SubstitutionField& field )
		{
			field.mNewLine = true;
			return true;
		}

	
		QString SubstitutionField::formatValue( const QString& value ) const
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
	

	}
}
