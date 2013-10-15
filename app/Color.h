/*  Color.h
 *
 *  Copyright (C) 2011  Jim Evins <evins@snaught.com>
 *
 *  This file is part of qtLabels.
 *
 *  qtLabels is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  qtLabels is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with qtLabels.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef qtlabels_Color_h
#define qtlabels_Color_h

#include <stdint.h>


namespace qtLabels
{

	class Color
	{

	public:
		/* double RGBA Constructor */
		Color( double r = 0, double g = 0, double b = 0, double a = 1 )
			: m_r(r), m_g(g), m_b(b), m_a(a)
		{
		}


		static Color from_byte_rgba( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255 )
		{
			return Color( r/255.0, g/255.0, b/255.0, a/255.0 );
		}


		static Color from_legacy_color( uint32_t c )
		{
			return Color( ((c>>24) & 0xff) / 255.0,
				      ((c>>16) & 0xff) / 255.0,
				      ((c>>8)  & 0xff) / 255.0,
				      ((c)     & 0xff) / 255.0 );
		}


		static Color none()
		{
			return Color( 0, 0, 0, 0 );
		}


		static Color black()
		{
			return Color( 0, 0, 0, 1 );
		}


		static Color white()
		{
			return Color( 1, 1, 1, 1 );
		}


		/* Muliply by opacity.  Create new color by applying opacity. */
		Color operator*( double opacity ) const
		{
			return Color( m_r, m_g, m_b, m_a * opacity );
		}


		uint32_t to_legacy_color()
		{
			uint32_t c = (((uint32_t)(m_r*255) & 0xff) << 24) |
				     (((uint32_t)(m_g*255) & 0xff) << 16) |
				     (((uint32_t)(m_b*255) & 0xff) << 8)  |
				     (((uint32_t)(m_a*255) & 0xff));
			return c;
		}


		bool operator==( const Color &c )
		{
			return ( (m_r == c.m_r) &&
				 (m_g == c.m_g) &&
				 (m_b == c.m_b) &&
				 (m_a == c.m_a) );
		}


		bool operator!=( const Color &c )
		{
			return ( (m_r != c.m_r) ||
				 (m_g != c.m_g) ||
				 (m_b != c.m_b) ||
				 (m_a != c.m_a) );
		}


		bool has_alpha()
		{
			return ( m_a != 0 );
		}


		/*
		 * Red (r) Property
		 */
		double r( void ) { return m_r; }
		void r( double value ) { m_r = value; }
		

		/*
		 * Green (g) Property
		 */
		double g( void ) { return m_g; }
		void g( double value ) { m_g = value; }
		

		/*
		 * Blue (b) Property
		 */
		double b( void ) { return m_b; }
		void b( double value ) { m_b = value; }
		

		/*
		 * Alpha (a) Property
		 */
		double a( void ) { return m_a; }
		void a( double value ) { m_a = value; }
		

	private:
		double m_r;
		double m_g;
		double m_b;
		double m_a;

	};
	
}

#endif // qtlabels_Color_h
