/*  LabelModelItem.cpp
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

#include "LabelModelItem.h"


namespace qtLabels
{

	/*
	 * Default constructor.
	 */
	LabelModelItem::LabelModelItem()
	{
		m_x0 = 0;
		m_y0 = 0;
		m_w  = 0;
		m_h  = 0;
		m_matrix = QTransform();

		m_shadow_state      = false;
		m_shadow_x          = 1.3;
		m_shadow_y          = 1.3;
		m_shadow_color_node = ColorNode( Color::black() );
		m_shadow_opacity    = 0.5;

		m_selected_flag = false;
	}


	void LabelModelItem::set_position( double x0,
					   double y0 )
	{
		if ( ( m_x0 != x0 ) || ( m_y0 != y0 ) )
		{
			m_x0 = x0;
			m_y0 = y0;

			moved();
		}
	}


	void LabelModelItem::set_position_relative( double dx,
						    double dy )
	{
		if ( ( dx != 0 ) || ( dy != 0 ) )
		{
			m_x0 += dx;
			m_y0 += dy;

			moved();
		}
	}


	void LabelModelItem::set_size( double w,
				       double h )
	{
		m_w = w;
		m_h = h;
	}


	void LabelModelItem::set_size_honor_aspect( double w,
						    double h )
	{
		double aspect_ratio = m_h / m_w;

		if ( h > (w * aspect_ratio) )
		{
			h = w * aspect_ratio;
		}
		else
		{
			w = h / aspect_ratio;
		}

		if ( ( m_w != w ) || ( m_h != h ) )
		{
			m_w = w;
			m_h = h;

			changed();
		}
	}


	void LabelModelItem::set_w_honor_aspect( double w )
	{
		double aspect_ratio = m_h / m_w;
		double h = w * aspect_ratio;

		if ( ( m_w != w ) || ( m_h != h ) )
		{
			m_w = w;
			m_h = h;

			changed();
		}
	}


	void LabelModelItem::set_h_honor_aspect( double h )
	{
		double aspect_ratio = m_h / m_w;
		double w = h / aspect_ratio;

		if ( ( m_w != w ) || ( m_h != h ) )
		{
			m_w = w;
			m_h = h;

			changed();
		}
	}


	LabelRegion LabelModelItem::get_extent()
	{
		QPointF a1(     - line_width()/2,     - line_width()/2 );
		QPointF a2( m_w + line_width()/2,     - line_width()/2 );
		QPointF a3( m_w + line_width()/2, m_h + line_width()/2 );
		QPointF a4(     - line_width()/2, m_h + line_width()/2 );

		a1 = m_matrix.map( a1 );
		a2 = m_matrix.map( a2 );
		a3 = m_matrix.map( a3 );
		a4 = m_matrix.map( a4 );

		LabelRegion region;
		region.x1( std::min( a1.x(), std::min( a2.x(), std::min( a3.x(), a4.x() ) ) ) + m_x0 );
		region.y1( std::min( a1.y(), std::min( a2.y(), std::min( a3.y(), a4.y() ) ) ) + m_y0 );
		region.x2( std::max( a1.x(), std::max( a2.x(), std::max( a3.x(), a4.x() ) ) ) + m_x0 );
		region.y2( std::max( a1.y(), std::max( a2.y(), std::max( a3.y(), a4.y() ) ) ) + m_y0 );

		return region;
	}


	void LabelModelItem::rotate( double theta_degs )
	{
		if ( theta_degs != 0 )
		{
			m_matrix = m_matrix.rotate( theta_degs );
			changed();
		}
	}


	void LabelModelItem::flip_horiz()
	{
		m_matrix = m_matrix.scale( -1, 1 );
		changed();
	}


	void LabelModelItem::flip_vert()
	{
		m_matrix = m_matrix.scale( 1, -1 );
		changed();
	}


	void LabelModelItem::draw( QPainter &qp, bool in_editor, const MergeRecord &record )
	{
		qp.save();
		qp.translate( m_x0, m_y0 );

		if ( m_shadow_state )
		{
			qp.save();
			qp.translate( m_shadow_x, m_shadow_y );
			qp.setTransform( m_matrix, true );
			draw_shadow( qp, in_editor, record );
			qp.restore();
		}

		qp.setTransform( m_matrix, true );
		draw_object( qp, in_editor, record );

		qp.restore();
	}


	void LabelModelItem::draw_selection_layer( QPainter &qp )
	{
		if ( m_selected_flag )
		{
			qp.save();
			qp.translate( m_x0, m_y0 );
			qp.setTransform( m_matrix, true );

/* TODO:
			if ( outline != null )
			{
				outline.draw( qp );
			}

			foreach( Handle handle in handles )
			{
				handle.draw( qp );
			}
*/

			qp.restore();
		}
	}


	bool LabelModelItem::is_located_at( QPainter &qp, double x_pixels, double y_pixels )
	{
		bool ret_val = false;

		qp.save();
		qp.translate( m_x0, m_y0 );
		qp.setTransform( m_matrix, true );

/* TODO:
		double x = x_pixels;
		double y = y_pixels;
		qp.device_to_user( ref x, ref y );

		bool ret_val = is_object_located_at( qp, x, y );

		if ( (outline != null) && is_selected() )
		{
			if ( outline.in_stroke( qp, x, y ) )
			{
				ret_val = true;
			}
		}
*/

		qp.restore();

		return ret_val;
	}


/* TODO:
	Handle *LabelModelItem::handle_at( QPainter &qp, double x_pixels, double y_pixels )
	{
		Handle *ret_val = null;

		qp.save();
		qp.translate( x0, y0 );
		qp.transform( matrix );

		double x = x_pixels;
		double y = y_pixels;
		qp.device_to_user( ref x, ref y );

		foreach( Handle handle in handles )
		{
			handle.cairo_path( qp );

			if ( qp.in_fill( x, y ) )
			{
				ret_val = handle;
				break;
			}
		}

		qp.restore();

		return ret_val;
	}
*/

}


///////////////////////////////////////////////////////////////////////////////
#if 0

		protected List<Handle> handles;
		protected Outline?     outline;

		/**
		 * Parent label
		 */
		public weak Label parent { get; set; }

#endif
