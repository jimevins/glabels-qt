/*  StrUtil.cpp
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

#include "StrUtil.h"

#include <cmath>


namespace
{
	const double FRAC_EPSILON = 0.00005;
	const double denom[]        = {  1.0,  2.0, 3.0,  4.0,  8.0,  16.0,  32.0,  0.0 };
	const char*  denom_string[] = { "1", "₂", "₃", "₄", "₈", "₁₆", "₃₂", NULL };
	const char*  num_string[]   = {  "⁰",  "¹",  "²",  "³",  "⁴",  "⁵",  "⁶",  "⁷",  "⁸",  "⁹",
					 "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹",
					 "²⁰", "²¹", "²²", "²³", "²⁴", "²⁵", "²⁶", "²⁷", "²⁸", "²⁹",
					 "³⁰", "³¹" };
}
namespace libglabels
{

	namespace StrUtil
	{

		QString &formatFraction( double x )
		{
                        int i;
                        double product, remainder;

                        for ( i=0; denom[i] != 0.0; i++ )
                        {
                                product = x * denom[i];
                                remainder = fabs(product - ((int)(product+0.5)));
                                if ( remainder < FRAC_EPSILON ) break;
                        }

                        if ( denom[i] == 0.0 )
                        {
                                /* None of our denominators work. */
                                return QString().sprintf( "%.5g", x );
                        }
                        if ( denom[i] == 1.0 )
                        {
                                /* Simple integer. */
                                return QString().sprintf( "%.0f", x );
                        }
                        int n = (int)( x * denom[i] + 0.5 );
                        int d = (int)denom[i];
                        if ( n > d )
                        {
                                return QString().sprintf( "%d%s/%s", (n/d), num_string[n%d], denom_string[i] );
                        }
                        else
                        {
                                return QString().sprintf( "%s/%s", num_string[n%d], denom_string[i] );
                        }
		}

	}

}

