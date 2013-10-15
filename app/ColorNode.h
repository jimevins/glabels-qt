/*  ColorNode.h
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#ifndef qtlabels_ColorNode_h
#define qtlabels_ColorNode_h

#include <QString>

#include "Color.h"


namespace qtLabels
{

	class ColorNode
	{

	public:
		ColorNode()
			: m_field_flag(false), m_color(Color::none()), m_key("")
		{
		}


		ColorNode( bool field_flag, Color &color, QString &key )
			: m_field_flag(field_flag), m_color(color), m_key(key)
		{
		}


		ColorNode( const Color &color )
			: m_field_flag(false), m_color(color), m_key("")
		{
		}


		ColorNode( QString &key )
			: m_field_flag(true), m_color(Color::none()), m_key(key)
		{
		}


		bool operator==( const ColorNode &cn )
		{
			return ( (m_field_flag == cn.m_field_flag) &&
				 (m_color      == cn.m_color)      &&
				 (m_key        == cn.m_key) );
		}


		bool operator!=( const ColorNode &cn )
		{
			return ( (m_field_flag != cn.m_field_flag) ||
				 (m_color      != cn.m_color)      ||
				 (m_key        != cn.m_key) );
		}


#if TODO
		Color expand( MergeRecord? record )
		{
			if ( field_flag )
			{
				if ( record == null )
				{
					return Color.none();
				}
				else
				{
					string? text = record.eval_key( key );
					if ( text != null )
					{
						Gdk.Color gdk_color = Gdk.Color();
						if ( Gdk.Color.parse( text, out gdk_color ) )
						{
							Color color = Color.from_gdk_color( gdk_color );
							return color;
						}
						else
						{
							return Color.none();
						}
					}
					else
					{
						return Color.none();
					}
				}
			}
			else
			{
				return color;
			}
		}
#endif


		/*
		 * field flag property
		 */
		bool field_flag( void ) { return m_field_flag; }
		

		/*
		 * color property
		 */
		Color color( void ) { return m_color; }
		

		/*
		 * key property
		 */
		QString key( void ) { return m_key; }
		

	private:
		bool    m_field_flag;
		Color   m_color;
		QString m_key;

	};

}

#endif // qtlabels_ColorNode_h
