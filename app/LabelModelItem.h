/*  LabelModelItem.h
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

#ifndef glabels_LabelModelItem_h
#define glabels_LabelModelItem_h

#include <QObject>
#include <QTransform>
#include <QFont>
#include <QPainter>

#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"
#include "LabelRegion.h"
#include "MergeRecord.h"


namespace glabels
{

	class LabelModelItem : public QObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelItem();
		virtual ~LabelModelItem() {}


		///////////////////////////////////////////////////////////////
		// Signals
		///////////////////////////////////////////////////////////////
	signals:
		void moved();
		void changed();


		///////////////////////////////////////////////////////////////
		// Common Properties
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Selected Property.
		 */
		Q_PROPERTY( bool selected READ isSelected WRITE select RESET unselect )

		bool isSelected( void ) { return m_selected_flag; }
		void select( bool value = true ) { m_selected_flag = value; }
		void unselect( void ) { m_selected_flag = false; }


		/*
		 * x0 Property ( x coordinate of origin )
		 */
		Q_PROPERTY( double x0 READ x0 WRITE x0 );

		double x0( void ) { return m_x0; }
		void x0( double value )
		{
			if ( m_x0 != value ) { m_x0 = value; emit moved(); }
		}
		

		/*
		 * y0 Property ( y coordinate of origin )
		 */
		Q_PROPERTY( double y0 READ y0 WRITE y0 );

		double y0( void ) { return m_y0; }
		void y0( double value )
		{
			if ( m_y0 != value ) { m_y0 = value; emit moved(); }
		}
		

		/*
		 * w Property ( width of bounding box )
		 */
		Q_PROPERTY( double w  READ w  WRITE w );

		double w( void ) { return m_w; }
		void w( double value )
		{
			if ( m_w != value ) { m_w = value; emit moved(); }
		}
		

		/*
		 * h Property ( height of bounding box )
		 */
		Q_PROPERTY( double h  READ h  WRITE h );

		double h( void ) { return m_h; }
		void h( double value )
		{
			if ( m_h != value ) { m_h = value; emit moved(); }
		}


		/*
		 * Transformation Matrix Property
		 */
		Q_PROPERTY( QTransform matrix READ matrix WRITE matrix );

		QTransform matrix( void ) { return m_matrix; }
		void matrix( const QTransform &value )
		{
			if ( m_matrix != value ) { m_matrix = value; emit changed(); }
		}


		/*
		 * Shadow State Property
		 */
		Q_PROPERTY( bool shadow READ shadow WRITE shadow );

		bool shadow( void ) { return m_shadow_state; }
		void shadow( bool value )
		{
			if ( m_shadow_state != value ) { m_shadow_state = value; emit changed(); }
		}


		/*
		 * Shadow x Offset Property
		 */
		Q_PROPERTY( double shadow_x READ shadow_x WRITE shadow_x );

		double shadow_x( void ) { return m_shadow_x; }
		void shadow_x( double value )
		{
			if ( m_shadow_x != value ) { m_shadow_x = value; emit changed(); }
		}
		

		/*
		 * Shadow y Offset Property
		 */
		Q_PROPERTY( double shadow_y READ shadow_y WRITE shadow_y );

		double shadow_y( void ) { return m_shadow_y; }
		void shadow_y( double value )
		{
			if ( m_shadow_y != value ) { m_shadow_y = value; emit changed(); }
		}
		

		/*
		 * Shadow opacity Property
		 */
		Q_PROPERTY( double shadow_opacity READ shadow_opacity WRITE shadow_opacity );

		double shadow_opacity( void ) { return m_shadow_opacity; }
		void shadow_opacity( double value )
		{
			if ( m_shadow_opacity != value ) { m_shadow_opacity = value; emit changed(); }
		}
		

		/*
		 * Shadow Color Property
		 */
		Q_PROPERTY( ColorNode shadow_color_node READ shadow_color_node WRITE shadow_color_node );

		ColorNode shadow_color_node( void ) { return m_shadow_color_node; }
		void shadow_color_node( const ColorNode &value )
		{
			if ( m_shadow_color_node != value ) { m_shadow_color_node = value; emit changed(); }
		}
		

		///////////////////////////////////////////////////////////////
		// Text Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Text Property: font_family
		 */
		Q_PROPERTY( QString font_family READ font_family WRITE font_family );

		virtual QString font_family( void ) { return ""; }
		virtual void font_family( const QString &value ) { }


		/*
		 * Virtual Text Property: font_size
		 */
		Q_PROPERTY( double font_size READ font_size WRITE font_size );

		virtual double font_size( void ) { return 0; }
		virtual void font_size( double value ) { }


		/*
		 * Virtual Text Property: font_weight
		 */
		Q_PROPERTY( QFont::Weight font_weight READ font_weight WRITE font_weight );

		virtual QFont::Weight font_weight( void ) { return QFont::Normal; }
		virtual void font_weight( QFont::Weight value ) { }


		/*
		 * Virtual Text Property: font_italic_flag
		 */
		Q_PROPERTY( bool font_italic_flag READ font_italic_flag WRITE font_italic_flag );

		virtual bool font_italic_flag( void ) { return false; }
		virtual void font_italic_flag( bool value ) { }


		/*
		 * Virtual Text Property: font_underline_flag
		 */
		Q_PROPERTY( bool font_underline_flag READ font_underline_flag WRITE font_underline_flag );

		virtual bool font_underline_flag( void ) { return false; }
		virtual void font_underline_flag( bool value ) { }


		/*
		 * Virtual Text Property: font_color_node
		 */
		Q_PROPERTY( ColorNode font_color_node READ font_color_node WRITE font_color_node );

		virtual ColorNode font_color_node( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void font_color_node( const ColorNode &value ) { }
		

		/*
		 * Virtual Text Property: text_halign
		 */
		Q_PROPERTY( Qt::Alignment text_halign READ text_halign WRITE text_halign );

		virtual Qt::Alignment text_halign( void ) { return Qt::AlignLeft; }
		virtual void text_halign( Qt::Alignment value ) { }


		/*
		 * Virtual Text Property: text_valign
		 */
		Q_PROPERTY( Qt::Alignment text_valign READ text_valign WRITE text_valign );

		virtual Qt::Alignment text_valign( void ) { return Qt::AlignTop; }
		virtual void text_valign( Qt::Alignment value ) { }


		/*
		 * Virtual Text Property: text_line_spacing
		 */
		Q_PROPERTY( double text_line_spacing READ text_line_spacing WRITE text_line_spacing );

		virtual double text_line_spacing( void ) { return 0; }
		virtual void text_line_spacing( double value ) { }


		///////////////////////////////////////////////////////////////
		// Image Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Image Property: filename_node
		 */
		Q_PROPERTY( TextNode filename_node READ filename_node WRITE filename_node );

		virtual TextNode filename_node( void ) { return TextNode(); }
		virtual void filename_node( const TextNode &value ) { }
		

		///////////////////////////////////////////////////////////////
		// Shape Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Shape Property: line_width
		 */
		Q_PROPERTY( double line_width READ line_width WRITE line_width );

		virtual double line_width( void ) { return 0; }
		virtual void line_width( double value ) { }


		/*
		 * Virtual Shape Property: line_color_node
		 */
		Q_PROPERTY( ColorNode line_color_node READ line_color_node WRITE line_color_node );

		virtual ColorNode line_color_node( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void line_color_node( const ColorNode &value ) { }
		

		/*
		 * Virtual Shape Property: fill_color_node
		 */
		Q_PROPERTY( ColorNode fill_color_node READ fill_color_node WRITE fill_color_node );

		virtual ColorNode fill_color_node( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void fill_color_node( const ColorNode &value ) { }
		

		///////////////////////////////////////////////////////////////
		// Barcode Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Barcode Property: bc_data_node
		 */
		Q_PROPERTY( TextNode bc_data_node READ bc_data_node WRITE bc_data_node );

		virtual TextNode bc_data_node( void ) { return TextNode(); }
		virtual void bc_data_node( const TextNode &value ) { }
		

		/*
		 * Virtual Barcode Property: bc_text_flag
		 */
		Q_PROPERTY( bool bc_text_flag READ bc_text_flag WRITE bc_text_flag );

		virtual bool bc_text_flag( void ) { return false; }
		virtual void bc_text_flag( bool value ) { }


		/*
		 * Virtual Barcode Property: bc_checksum_flag
		 */
		Q_PROPERTY( bool bc_checksum_flag READ bc_checksum_flag WRITE bc_checksum_flag );

		virtual bool bc_checksum_flag( void ) { return false; }
		virtual void bc_checksum_flag( bool value ) { }


		/*
		 * Virtual Barcode Property: bc_color_node
		 */
		Q_PROPERTY( ColorNode bc_color_node READ bc_color_node WRITE bc_color_node );

		virtual ColorNode bc_color_node( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void bc_color_node( const ColorNode &value ) { }
		

		/*
		 * Virtual Barcode Property: bc_style
		 */
		Q_PROPERTY( BarcodeStyle bc_style READ bc_style WRITE bc_style );

		virtual BarcodeStyle bc_style( void ) { return BarcodeStyle(); }
		virtual void bc_style( const BarcodeStyle &value ) { }
		

		/*
		 * Virtual Barcode Property: bc_format_digits
		 */
		Q_PROPERTY( int bc_format_digits READ bc_format_digits WRITE bc_format_digits );

		virtual int bc_format_digits( void ) { return false; }
		virtual void bc_format_digits( int value ) { }


		///////////////////////////////////////////////////////////////
		// Capabilities (Overridden by concrete classes.)
		///////////////////////////////////////////////////////////////
	public:
		virtual bool can_text()	{ return false;	}

		virtual bool can_fill()	{ return false;	}

		virtual bool can_line_color() {	return false; }

		virtual bool can_line_width() {	return false; }


		///////////////////////////////////////////////////////////////
		// Position and Size methods
		///////////////////////////////////////////////////////////////
	public:
		void set_position( double x0,
				   double y0 );

		void set_position_relative( double dx,
					    double dy );

		void set_size( double w,
			       double h );

		void set_size_honor_aspect( double w,
					    double h );

		void set_w_honor_aspect( double w );

		void set_h_honor_aspect( double h );

		LabelRegion get_extent();

		void rotate( double theta_degs );

		void flip_horiz();

		void flip_vert();


		///////////////////////////////////////////////////////////////
		// Drawing Methods
		///////////////////////////////////////////////////////////////
	public:
		void draw( QPainter &qp, bool in_editor, const MergeRecord &record );

		void draw_selection_layer( QPainter &qp );

	protected:
		virtual void draw_object( QPainter &qp, bool in_editor, MergeRecord record ) = 0;

		virtual void draw_shadow( QPainter &qp, bool in_editor, MergeRecord record ) = 0;


		///////////////////////////////////////////////////////////////
		// Text location Methods
		///////////////////////////////////////////////////////////////
	public:
		bool is_located_at( QPainter &qp, double x_pixels, double y_pixels );

		//Handle* handle_at(  QPainter &qp, double x_pixels, double y_pixels );

	protected:
		virtual bool is_object_located_at( QPainter &qp, double x, double y ) = 0;


		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
		bool       m_selected_flag;

		double     m_x0;
		double     m_y0;
		double     m_w;
		double     m_h;

		QTransform m_matrix;

		bool       m_shadow_state;
		double     m_shadow_x;
		double     m_shadow_y;
		double     m_shadow_opacity;
		ColorNode  m_shadow_color_node;

	};

}

#endif // glabels_LabelModelItem_h

///////////////////////////////////////////////////////////////////////////////
#if 0
		protected List<Handle> handles;
		protected Outline?     outline;

		/**
		 * Parent label
		 */
		public weak Label parent { get; set; }

#endif
