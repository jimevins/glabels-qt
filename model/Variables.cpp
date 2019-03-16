/*  Variables.cpp
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

#include "Variables.h"

#include <QtDebug>


namespace glabels
{
	namespace model
	{
		///
		/// Copy constructor
		///
		Variables::Variables( const Variables* variables )
			: QMap<QString,Variable>(*variables)
		{
		}


		///
		/// Clone
		///
		Variables* Variables::clone() const
		{
			return new Variables( this );
		}


		///
		/// Do we have variable?
		///
		bool Variables::hasVariable( const QString& name ) const
		{
			return contains(name);
		}


		///
		/// Add variable ( will replace if name is the same )
		///
		void Variables::addVariable( const Variable& variable )
		{
			insert( variable.name(), variable );
			emit changed();
		}


		///
		/// Delete variable
		///
		void Variables::deleteVariable( const QString& name )
		{
			remove( name );
			emit changed();
		}


		///
		/// Replace variable
		///
		void Variables::replaceVariable( const QString& origName, const Variable& variable )
		{
			remove( origName );
			insert( variable.name(), variable );
			emit changed();
		}


	} // namespace model

} // namespace glabels
