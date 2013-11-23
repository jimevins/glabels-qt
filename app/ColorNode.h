/*  ColorNode.h
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

#ifndef glabels_ColorNode_h
#define glabels_ColorNode_h

#include <QString>
#include <QColor>


namespace glabels
{

	class ColorNode
	{

	public:
		ColorNode()
			: m_field_flag(false), m_color(QColor::fromRgba(0x00000000)), m_key("")
		{
		}


		ColorNode( bool field_flag, QColor &color, QString &key )
			: m_field_flag(field_flag), m_color(color), m_key(key)
		{
		}


		ColorNode( const QColor &color )
			: m_field_flag(false), m_color(color), m_key("")
		{
		}


		ColorNode( QString &key )
			: m_field_flag(true), m_color(QColor::fromRgba(0x00000000)), m_key(key)
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
		QColor expand( MergeRecord? record )
		{
			if ( field_flag )
			{
				if ( record == null )
				{
					return QColor.fromRgba(0x00000000);
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


		/*
		 * field flag property
		 */
		bool field_flag( void ) { return m_field_flag; }
		

		/*
		 * color property
		 */
		QColor color( void ) { return m_color; }
		

		/*
		 * key property
		 */
		QString key( void ) { return m_key; }
		

	private:
		bool    m_field_flag;
		QColor  m_color;
		QString m_key;

	};

}

#endif // glabels_ColorNode_h
