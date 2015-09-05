/*  ColorNode.cpp
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

#include "ColorNode.h"


namespace glabels
{

	///
	/// Default Constructor
	///
	ColorNode::ColorNode()
		: mFieldFlag(false), mColor(QColor::fromRgba(0x00000000)), mKey("")
	{
	}


	///
	/// Constructor From Data
	///
	ColorNode::ColorNode( bool fieldFlag, const QColor& color, const QString& key )
		: mFieldFlag(fieldFlag), mColor(color), mKey(key)
	{
	}


	///
	/// Constructor From Data
	///
	ColorNode::ColorNode( bool fieldFlag, uint32_t rgba, const QString& key )
		: mFieldFlag(fieldFlag), mKey(key)
	{
		mColor = QColor( (rgba >> 24) & 0xFF,
				 (rgba >> 16) & 0xFF,
				 (rgba >>  8) & 0xFF,
				 (rgba      ) & 0xFF );
	}


	///
	/// Constructor From Color
	///
	ColorNode::ColorNode( const QColor& color )
		: mFieldFlag(false), mColor(color), mKey("")
	{
	}


	///
	/// Constructor From Key
	///
	ColorNode::ColorNode( const QString& key )
		: mFieldFlag(true), mColor(QColor::fromRgba(0x00000000)), mKey(key)
	{
	}


	///
	/// == Operator
	///
	bool ColorNode::operator==( const ColorNode& cn )
	{
		return ( (mFieldFlag == cn.mFieldFlag) &&
			 (mColor     == cn.mColor)     &&
			 (mKey       == cn.mKey) );
	}


	///
	/// != Operator
	///
	bool ColorNode::operator!=( const ColorNode& cn )
	{
		return ( (mFieldFlag != cn.mFieldFlag) ||
			 (mColor     != cn.mColor)     ||
			 (mKey       != cn.mKey) );
	}


	///
	/// Field Flag Property Getter
	///
	bool ColorNode::fieldFlag( void ) const
	{
		return mFieldFlag;
	}
		

	///
	/// Field Flag Property Setter
	///
	void ColorNode::setFieldFlag( bool fieldFlag )
	{
		mFieldFlag = fieldFlag;
	}


	///
	/// Color Property Getter
	///
	const QColor& ColorNode::color( void ) const
	{
		return mColor;
	}


	///
	/// Color Property Setter
	///
	void ColorNode::setColor( const QColor& color )
	{
		mColor = color;
	}
		

	///
	/// Key Property Getter
	///
	const QString& ColorNode::key( void ) const
	{
		return mKey;
	}


	///
	/// Key Property Setter
	///
	void ColorNode::setKey( const QString& key )
	{
		mKey = key;
	}
		

	uint32_t ColorNode::rgba( void ) const
	{
		uint32_t c =
			mColor.red()   << 24 |
			mColor.green() << 16 |
			mColor.blue()  <<  8 |
			mColor.alpha();

		return c;
	}

	
#if TODO
	QColor ColorNode::expand( MergeRecord? record )
	{
		if ( fieldFlag )
		{
			if ( record == null )
			{
				return QColor.fromRgba(0x00000000);
			}
			else
			{
				string? text = record.evalKey( key );
				if ( text != null )
				{
					Gdk.Color gdkColor = Gdk.Color();
					if ( Gdk.Color.parse( text, out gdkColor ) )
					{
						Color color = Color.from_gdkColor( gdkColor );
						return color;
					}
					else
					{
						return Color.fromRgba(0x00000000);
					}
				}
				else
				{
					return Color.fromRgba(0x00000000);
				}
			}
		}
		else
		{
			return color;
		}
	}
#endif

}

