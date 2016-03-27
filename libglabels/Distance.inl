/*  Distance.inl
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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


#include <cmath>


namespace glabels
{

	inline Distance::Distance() : mDPts(0)
	{
	}

	
	inline Distance Distance::pt( double dPts )
	{
		Distance d;
		d.mDPts = dPts;
		return d;
	}


	inline Distance Distance::in( double dInches )
	{
		Distance d;
		d.mDPts = dInches * PTS_PER_INCH;
		return d;
	}


	inline Distance Distance::mm( double dMm )
	{
		Distance d;
		d.mDPts = dMm * PTS_PER_MM;
		return d;
	}


	inline Distance Distance::cm( double dCm )
	{
		Distance d;
		d.mDPts = dCm * PTS_PER_CM;
		return d;
	}


	inline Distance Distance::pc( double dPicas )
	{
		Distance d;
		d.mDPts = dPicas * PTS_PER_PICA;
		return d;
	}


	inline double Distance::pt() const
	{
		return mDPts;
	}
	

	inline double Distance::in() const
	{
		return mDPts / PTS_PER_INCH;
	}
	

	inline double Distance::mm() const
	{
		return mDPts / PTS_PER_MM;
	}
	

	inline double Distance::cm() const
	{
		return mDPts / PTS_PER_CM;
	}
	

	inline double Distance::pc() const
	{
		return mDPts / PTS_PER_PICA;
	}


	inline Distance& Distance::operator+=( const Distance& d )
	{
		mDPts += d.mDPts;
		return *this;
	}

	
	inline Distance& Distance::operator-=( const Distance& d )
	{
		mDPts -= d.mDPts;
		return *this;
	}

	
	inline Distance Distance::operator-()
	{
		return Distance::pt( -mDPts );
	}

	
	inline Distance operator+( const Distance& d1, const Distance& d2 )
	{
		return Distance::pt( d1.mDPts + d2.mDPts );
	}
	

	inline Distance operator-( const Distance& d1, const Distance& d2 )
	{
		return Distance::pt( d1.mDPts - d2.mDPts );
	}
	

	inline Distance operator*( double x, const Distance& d )
	{
		return Distance::pt( x * d.mDPts );
	}


	inline Distance operator*( const Distance& d, double x )
	{
		return Distance::pt( d.mDPts * x );
	}

	
	inline double operator/( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts / d2.mDPts;
	}


	inline Distance operator/( const Distance& d, double x )
	{
		return Distance::pt( d.mDPts / x );
	}


	inline bool operator<( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts < d2.mDPts;
	}
	

	inline bool operator<=( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts <= d2.mDPts;
	}
	

	inline bool operator>( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts > d2.mDPts;
	}
	

	inline bool operator>=( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts >= d2.mDPts;
	}
	

	inline bool operator==( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts == d2.mDPts;
	}


	inline bool operator!=( const Distance& d1, const Distance& d2 )
	{
		return d1.mDPts != d2.mDPts;
	}


	inline Distance fabs( const Distance& d )
	{
		return Distance::pt( std::fabs( d.mDPts ) );
	}

	
	inline Distance min( const Distance& d1, const Distance& d2 )
	{
		return (d1.mDPts < d2.mDPts) ? d1 : d2;
	}

	
	inline Distance max( const Distance& d1, const Distance& d2 )
	{
		return (d1.mDPts > d2.mDPts) ? d1 : d2;
	}


	inline Distance fmod( const Distance& d1, const Distance& d2 )
	{
		return Distance::pt( std::fmod( d1.mDPts, d2.mDPts ) );
	}

}
