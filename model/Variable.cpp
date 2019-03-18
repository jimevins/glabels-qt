/*  Variable.cpp
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

#include "Variable.h"


namespace glabels
{
	namespace model
	{

		Variable::Variable( Variable::Type      type,
		                    const QString&      name,
		                    const QString&      value,
		                    Variable::Increment increment,
		                    const QString&      stepSize )
			: mType(type),
			  mName(name),
			  mValue(value),
			  mIncrement(increment),
			  mStepSize(stepSize)
		{
			// empty
		}


		Variable::Type Variable::type() const
		{
			return mType;
		}

	
		QString Variable::name() const
		{
			return mName;
		}


		QString Variable::value() const
		{
			return mValue;
		}


		Variable::Increment Variable::increment() const
		{
			return mIncrement;
		}


		QString Variable::stepSize() const
		{
			return mStepSize;
		}


		QString Variable::typeToI18nString( Type type )
		{
			switch (type)
			{
			case Type::NUMERIC:
				return tr("Numeric");
			case Type::STRING:
				return tr("String");
			}
		}


		QString Variable::typeToIdString( Type type )
		{
			switch (type)
			{
			case Type::NUMERIC:
				return "numeric";
			case Type::STRING:
				return "string";
			}
		}
		

		Variable::Type Variable::idStringToType( const QString& string )
		{
			if ( string == "numeric" )
			{
				return Type::NUMERIC;
			}
			else if ( string == "string" )
			{
				return Type::STRING;
			}
			else
			{
				return Type::STRING; // Default
			}
		}
		

		QString Variable::incrementToI18nString( Increment increment )
		{
			switch (increment)
			{
			case Increment::NEVER:
				return tr("Never");
			case Increment::PER_COPY:
				return tr("Per copy");
			case Increment::PER_MERGE_RECORD:
				return tr("Per merge record");
			case Increment::PER_PAGE:
				return tr("Per page");
			}
		}

		
		QString Variable::incrementToIdString( Increment increment )
		{
			switch (increment)
			{
			case Increment::NEVER:
				return "never";
			case Increment::PER_COPY:
				return "per_copy";
			case Increment::PER_MERGE_RECORD:
				return "per_merge_record";
			case Increment::PER_PAGE:
				return "per_page";
			}
		}
		

		Variable::Increment Variable::idStringToIncrement( const QString& string )
		{
			if ( string == "never" )
			{
				return Increment::NEVER;
			}
			else if ( string == "per_copy" )
			{
				return Increment::PER_COPY;
			}
			else if ( string == "per_merge_record" )
			{
				return Increment::PER_MERGE_RECORD;
			}
			else if ( string == "per_page" )
			{
				return Increment::PER_PAGE;
			}
			else
			{
				return Increment::NEVER; // Default
			}
		}
		

	}
}
