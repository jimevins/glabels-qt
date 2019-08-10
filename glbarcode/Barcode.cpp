/*  Barcode.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of glbarcode++.
 *
 *  glbarcode++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  glbarcode++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with glbarcode++.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Barcode.h"

#include <list>

#include "DrawingPrimitives.h"


namespace glbarcode
{

	/*
	 * Barcode private data
	 */
	struct Barcode::PrivateData {

		bool                   mShowTextFlag;  /**< Display text flag */
		bool                   mChecksumFlag;  /**< Add checksum flag */

		double                 mW;             /**< Width of barcode (points) */
		double                 mH;             /**< Height of barcode (points) */

		bool                   mIsEmpty;       /**< Empty data flag */
		bool                   mIsDataValid;   /**< Valid data flag */

		std::list<DrawingPrimitive *> mPrimitives;      /**< List of drawing primitives */

	};


	Barcode::Barcode()
	{
		d = new Barcode::PrivateData;

		d->mShowTextFlag  = false;
		d->mChecksumFlag  = false;

		d->mW             = 0;
		d->mH             = 0;

		d->mIsEmpty       = true;
		d->mIsDataValid   = false;
	}


	Barcode::~Barcode()
	{
		clear(); /* Clear drawing primitives. */
		delete d;
	}


	Barcode& Barcode::setShowText( bool value )
	{
		d->mShowTextFlag = value;
		return *this;
	}


	bool Barcode::showText( ) const
	{
		return d->mShowTextFlag;
	}


	Barcode& Barcode::setChecksum( bool value )
	{
		d->mChecksumFlag = value;
		return *this;
	}


	bool Barcode::checksum( ) const
	{
		return d->mChecksumFlag;
	}


	void Barcode::render( Renderer& renderer )
	{
		renderer.render( d->mW, d->mH, d->mPrimitives );
	}


	bool Barcode::isEmpty( ) const
	{
		return d->mIsEmpty;
	}


	void Barcode::setIsEmpty( bool value )
	{
		d->mIsEmpty = value;
	}


	bool Barcode::isDataValid( ) const
	{
		return d->mIsDataValid;
	}


	void Barcode::setIsDataValid( bool value )
	{
		d->mIsDataValid = value;
	}


	double Barcode::width( ) const
	{
		return d->mW;
	}


	double Barcode::height( ) const
	{
		return d->mH;
	}


	void Barcode::setWidth( double w )
	{
		d->mW = w;
	}


	void Barcode::setHeight( double h )
	{
		d->mH = h;
	}


	void Barcode::clear( )
	{
		std::list<DrawingPrimitive*>::iterator primitive;

		for ( primitive = d->mPrimitives.begin(); primitive != d->mPrimitives.end(); primitive++ )
		{
			delete *primitive;
		}

		d->mPrimitives.clear();
	}


	void Barcode::addLine( double x, double y, double w, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveLine( x, y, w, h ) );
	}


	void Barcode::addBox( double x, double y, double w, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveBox( x, y, w, h ) );
	}


	void Barcode::addText( double x, double y, double size, const std::string& text )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveText( x, y, size, text ) );
	}


	void Barcode::addRing( double x, double y, double r, double w )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveRing( x, y, r, w ) );
	}


	void Barcode::addHexagon( double x, double y, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveHexagon( x, y, h ) );
	}


	uint32_t Barcode::decodeUTF8( uint32_t* state, uint32_t* codep, unsigned char byte )
	{
		/*
		 * Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
		 * See https://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
		 */

		static const uint8_t utf8d[] = {
			/* The first part of the table maps bytes to character classes that
			 * reduce the size of the transition table and create bitmasks. */
			 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
			 8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

			/* The second part is a transition table that maps a combination
			 * of a state of the automaton and a character class to a state. */
			 0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
			12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
			12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
			12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
			12,36,12,12,12,12,12,12,12,12,12,12,
		};

		uint32_t type = utf8d[byte];

		*codep = *state != 0 ? (byte & 0x3fu) | (*codep << 6) : (0xff >> type) & byte;

		*state = utf8d[256 + *state + type];

		return *state;
	}


	bool Barcode::isISO8859_1( const std::string& rawData )
	{
		uint32_t codepoint;
		uint32_t state = 0;

		for ( unsigned char c : rawData )
		{
			Barcode::decodeUTF8( &state, &codepoint, c );
			if ( state == 12 || (state == 0 && codepoint >= 0x80 && (codepoint < 0xa0 || codepoint > 0xFF)) )
			{
				return false;
			}
		}

		if ( state != 0 )
		{
			return false;
		}

		return true;
	}


	std::string Barcode::toISO8859_1( const std::string& rawData )
	{
		std::string cookedData;

		uint32_t codepoint;
		uint32_t state = 0;

		for ( unsigned char c : rawData )
		{
			if ( Barcode::decodeUTF8( &state, &codepoint, c ) == 0 )
			{
				if ( codepoint < 0x80 )
				{
					cookedData += c;
				}
				else if (codepoint >= 0xA0 && codepoint <= 0xFF )
				{
					cookedData += (unsigned char)codepoint;
				}
			}
		}

		return cookedData;
	}

}
