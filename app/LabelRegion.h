/*  LabelRegion.h
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

#ifndef glabels_LabelRegion_h
#define glabels_LabelRegion_h


namespace glabels
{

	struct LabelRegion
	{
	public:
		inline double x1( void ) { return m_x1; }
		inline void x1( double value ) { m_x1 = value; }

		inline double y1( void ) { return m_y1; }
		inline void y1( double value ) { m_y1 = value; }

		inline double x2( void ) { return m_x2; }
		inline void x2( double value ) { m_x2 = value; }

		inline double y2( void ) { return m_y2; }
		inline void y2( double value ) { m_y2 = value; }


	private:
		double m_x1;
		double m_y1;
		double m_x2;
		double m_y2;
	};

}

#endif // glabels_LabelRegion_h
