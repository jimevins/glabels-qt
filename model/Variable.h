/*  Variable.h
 *
 *  Copyright (C) 2019  Jim Evins <evins@snaught.com>
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

#ifndef model_Variable_h
#define model_Variable_h


#include <QCoreApplication>
#include <QString>


namespace glabels
{
	namespace model
	{

		class Variable
		{
			Q_DECLARE_TR_FUNCTIONS(Variable)
			
		public:
			enum class Type
			{
				NUMERIC,
				STRING
			};

			enum class Increment
			{
				NEVER,
				PER_COPY,
				PER_MERGE_RECORD,
				PER_PAGE
			};
			
				
		public:
			Variable() = default;

			Variable( Type            type,
			          const QString&  name,
			          const QString&  value,
			          Increment       increment = Increment::NEVER,
			          const QString&  stepSize = "0" );

			virtual ~Variable() = default;


			Type      type() const;
			QString   name() const;
			QString   value() const;
			Increment increment() const;
			QString   stepSize() const;


			static QString   typeToI18nString( Type type );
			static QString   typeToIdString( Type type );
			static Type      idStringToType( const QString& string );

			static QString   incrementToI18nString( Increment increment );
			static QString   incrementToIdString( Increment increment );
			static Increment idStringToIncrement( const QString& string );


		private:
			Type      mType;
			QString   mName;
			QString   mValue;
			Increment mIncrement;
			QString   mStepSize;

		};

	}
}


#endif // model_Variable_h
