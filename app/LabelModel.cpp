/*  LabelModel.cpp
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

#include "LabelModel.h"

namespace qtLabels
{

	/**
	 * Default constructor.
	 */
	LabelModel::LabelModel()
	{
	}


	/**
	 * Add item.
	 */
	void LabelModel::add_item( LabelModelItem &item )
	{
		m_item_list.push_back( &item );
	}


	/**
	 * Select item.
	 */
	void LabelModel::select_item( LabelModelItem &item )
	{
		item.select();

		emit selection_changed();
	}


	/**
	 * Unselect item.
	 */
	void LabelModel::unselect_item( LabelModelItem &item )
	{
		item.unselect();

		emit selection_changed();
	}


	/**
	 * Select all items.
	 */
	void LabelModel::select_all( void )
	{
		list<LabelModelItem*>::iterator i_item;

		for ( i_item = m_item_list.begin(); i_item != m_item_list.end(); i_item++ )
		{
			(*i_item)->select();
		}

		emit selection_changed();
	}


	/**
	 * Unselect item all items.
	 */
	void LabelModel::unselect_all( void )
	{
		list<LabelModelItem*>::iterator i_item;

		for ( i_item = m_item_list.begin(); i_item != m_item_list.end(); i_item++ )
		{
			(*i_item)->unselect();
		}

		emit selection_changed();
	}

}

///////////////////////////////////////////////////////////////////////////////
#if 0
#include "LabelModelObject.h"

using namespace std;

namespace qtLabels
{

	public class LabelModel : QObject
	{
	signals:
		void name_changed();
		void selection_changed();
		void modified_changed();
		void size_changed();
		void changed();
		void merge_changed();


	public:
		list<LabelModelObject>  object_list;

		//  PixbufCache        pixbuf_cache;
		//  SvgCache           svg_cache;


		/**
		 * Filename
		 */
		public string? filename
		{
			get { return _filename; }

			set
			{
				if ( _filename != value )
				{
					_filename = value;
					name_changed();
				}
			}
		}
		private string? _filename;


		/**
		 * Compression mode ( 0 = no compression, 9 = max compression )
		 */
		public int compression
		{
			get { return _compression; }

			set
			{
				if ( (value < 0) && (value > 9) )
				{
					warning( "Compression mode out of range." );
					_compression = 9;
				}
				else
				{
					_compression = value;
				}
			}
		}
		private int _compression = 9;


		/**
		 * Modified flag
		 */
		public bool modified
		{
			get { return _modified; }

			set
			{
				if ( _modified != value )
				{
					_modified = value;
					if ( !_modified )
					{
						time_stamp.get_current_time();
					}
					modified_changed();
				}
			}
		}
		private bool _modified;

		public TimeVal  time_stamp { get; private set; }


		/**
		 * Template
		 */
		public Template template
		{
			get { return _template; }

			set
			{
				if ( _template != value )
				{
					_template = value;
					changed();
					size_changed();
					template_history.add_name( template.name );
					modified = true;
				}
			}
		}
		private Template _template;


		/**
		 * Rotate
		 */
		public bool rotate
		{
			get { return _rotate; }

			set
			{
				if ( _rotate != value )
				{
					_rotate = value;
					changed();
					size_changed();
					modified = true;
				}
			}
		}
		private bool _rotate;


		/**
		 * Merge
		 */
		public Merge merge
		{
			get { return _merge; }

			set
			{
				if ( _merge != value )
				{
					_merge = value;
					_merge.source_changed.connect( on_merge_source_changed );
					changed();
					merge_changed();
					modified = true;
				}
			}
		}
		private Merge _merge;


		/* Default object text properties */
		public string             default_font_family       { get; set; }
		public double             default_font_size         { get; set; }
		public Pango.Weight       default_font_weight       { get; set; default=Pango.Weight.NORMAL; }
		public bool               default_font_italic_flag  { get; set; }
		public Color              default_text_color        { get; set; }
		public Pango.Alignment    default_text_alignment    { get; set; }
		public double             default_text_line_spacing { get; set; }

		/* Default object line properties */
		public double             default_line_width        { get; set; }
		public Color              default_line_color        { get; set; }
        
		/* Default object fill properties */
		public Color              default_fill_color        { get; set; }


		private TemplateHistory    template_history;

		private static int         untitled_count;
		private int                untitled_instance;

		private bool               selection_op_flag;
		private bool               delayed_change_flag;


		public Label()
		{
			_merge = MergeBackends.create_merge( "None" );

			template_history = new TemplateHistory( 5 );

			pixbuf_cache = new PixbufCache();
			svg_cache    = new SvgCache();

			// TODO: Set default properties from user prefs
		}



		public string get_short_name()
		{
			if ( filename == null )
			{

				if ( untitled_instance == 0 )
				{
					untitled_instance = ++untitled_count;
				}

				return "%s %d".printf( _("Untitled"), untitled_instance );

			}
			else
			{

				string base_name = Path.get_basename( filename );
				try
				{
					Regex ext_pattern = new Regex( "\\.glabels$" );
					string short_name = ext_pattern.replace( base_name, -1, 0, "" );
					return short_name;
				}
				catch ( RegexError e )
				{
					warning( "%s", e.message );
					return base_name;
				}


			}
		}


		public bool is_untitled()
		{
			return filename == null;
		}


		public void get_size( out double w,
		                      out double h )
		{
			if ( template == null )
			{
				w = 0;
				h = 0;
				return;
			}

			TemplateFrame frame = template.frames.first().data;

			if ( !rotate )
			{
				frame.get_size( out w, out h );
			}
			else
			{
				frame.get_size( out h, out w );
			}
		}


		public void add_object( LabelObject object )
		{
			object.parent = this;
			object_list.append( object );

			object.changed.connect( on_object_changed );
			object.moved.connect( on_object_moved );

			changed();
			modified = true;
		}


		public void delete_object( LabelObject object )
		{
			unselect_object( object );

			object_list.remove( object );

			object.changed.disconnect( on_object_changed );
			object.moved.disconnect( on_object_moved );

			changed();
			modified = true;
		}


		private void on_object_changed()
		{
			schedule_or_emit_changed_signal();
		}


		private void on_object_moved()
		{
			schedule_or_emit_changed_signal();
		}


		private void on_merge_source_changed()
		{
			changed();
		}


		public void draw( Cairo.Context cr,
		                  bool          in_editor,
		                  MergeRecord?  record )
		{
			foreach ( LabelObject object in object_list )
			{
				object.draw( cr, in_editor, record );
			}
		}


		public LabelObject? object_at( Cairo.Context cr,
		                               double        x_pixels,
		                               double        y_pixels )
		{
			for ( unowned List<LabelObject>? p = object_list.last(); p != null; p = p.prev ) 
			{
				LabelObject object = p.data;

				if ( object.is_located_at( cr, x_pixels, y_pixels ) )
				{
					return object;
				}
			}

			return null;
		}


		public Handle? handle_at( Cairo.Context cr,
		                          double        x_pixels,
		                          double        y_pixels )
		{
			for ( unowned List<LabelObject>? p = object_list.last(); p != null; p = p.prev ) 
			{
				LabelObject object = p.data;

				if ( object.is_selected() )
				{
					Handle? handle = object.handle_at( cr, x_pixels, y_pixels );

					if ( handle != null )
					{
						return handle;
					}
				}
			}

			return null;
		}


		public void select_object( LabelObject object )
		{
			object.select();
			selection_changed();
		}


		public void unselect_object( LabelObject object )
		{
			object.unselect();
			selection_changed();
		}


		public void select_all()
		{
			foreach ( LabelObject object in object_list )
			{
				object.select();
			}
			selection_changed();
		}


		public void unselect_all()
		{
			foreach ( LabelObject object in object_list )
			{
				object.unselect();
			}
			selection_changed();
		}


		public void select_region( LabelRegion region )
		{
			double r_x1 = double.min( region.x1, region.x2 );
			double r_y1 = double.min( region.y1, region.y2 );
			double r_x2 = double.max( region.x1, region.x2 );
			double r_y2 = double.max( region.y1, region.y2 );

			foreach ( LabelObject object in object_list )
			{
				LabelRegion obj_extent = object.get_extent();

				if ( (obj_extent.x1 >= r_x1) &&
				     (obj_extent.x2 <= r_x2) &&
				     (obj_extent.y1 >= r_y1) &&
				     (obj_extent.y2 <= r_y2) )
				{
					object.select();
				}
			}
			selection_changed();
		}


		public bool is_selection_empty()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					return false;
				}
			}
			return true;
		}


		public bool is_selection_atomic()
		{
			int n_selected = 0;

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					n_selected++;
					if ( n_selected > 1 )
					{
						return false;
					}
				}
			}
			return (n_selected == 1);
		}


		public LabelObject? get_1st_selected_object()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					return object;
				}
			}
			return null;
		}


		public List<LabelObject> get_selection_list()
		{
			List<LabelObject> selection_list = null;

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					selection_list.append( object );
				}
			}
			return selection_list;
		}


		public bool can_selection_text()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() && object.can_text() )
				{
					return true;
				}
			}
			return false;
		}


		public bool can_selection_fill()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() && object.can_fill() )
				{
					return true;
				}
			}
			return false;
		}


		public bool can_selection_line_color()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() && object.can_line_color() )
				{
					return true;
				}
			}
			return false;
		}


		public bool can_selection_line_width()
		{
			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() && object.can_line_width() )
				{
					return true;
				}
			}
			return false;
		}


		private void schedule_or_emit_changed_signal()
		{
			if ( selection_op_flag )
			{
				delayed_change_flag = true;
			}
			else
			{
				modified = true;
				changed();
			}
		}


		private void begin_selection_op()
		{
			selection_op_flag = true;
		}


		private void end_selection_op()
		{
			selection_op_flag = false;
			if ( delayed_change_flag )
			{
				delayed_change_flag = false;
				changed();
				modified = true;
			}
		}


		public void delete_selection()
		{
			List<LabelObject> selection_list = get_selection_list();

			foreach ( LabelObject object in selection_list )
			{
				delete_object( object );
			}

			changed();
			modified = true;
		}


		public void raise_selection_to_top()
		{
			List<LabelObject> selection_list = get_selection_list();

			foreach ( LabelObject object in selection_list )
			{
				object_list.remove( object );
			}

			/* Move to end of list, representing front most object */
			foreach ( LabelObject object in selection_list )
			{
				object_list.append( object );
			}

			changed();
			modified = true;
		}


		public void lower_selection_to_bottom()
		{
			List<LabelObject> selection_list = get_selection_list();

			foreach ( LabelObject object in selection_list )
			{
				object_list.remove( object );
			}

			/* Move to front of list, representing rear most object */
			selection_list.reverse();
			foreach ( LabelObject object in selection_list )
			{
				object_list.prepend( object );
			}

			changed();
			modified = true;
		}


		public void rotate_selection( double theta_degs )
		{
			begin_selection_op();

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.rotate( theta_degs );
				}
			}

			end_selection_op();
		}


		public void rotate_selection_left()
		{
			begin_selection_op();

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.rotate( -90.0 );
				}
			}

			end_selection_op();
		}


		public void rotate_selection_right()
		{
			begin_selection_op();

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.rotate( 90.0 );
				}
			}

			end_selection_op();
		}


		public void flip_selection_horiz()
		{
			begin_selection_op();

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.flip_horiz();
				}
			}

			end_selection_op();
		}


		public void flip_selection_vert()
		{
			begin_selection_op();

			foreach ( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.flip_vert();
				}
			}

			end_selection_op();
		}


		public void align_selection_left()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();

			/* Find left most edge. */
			LabelRegion obj_extent = selection_list.first().data.get_extent();
			double x1_min = obj_extent.x1;
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				if ( obj_extent.x1 < x1_min ) x1_min = obj_extent.x1;
			}

			/* Now adjust the object positions to line up the left edges. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dx = x1_min - obj_extent.x1;
				object.set_position_relative( dx, 0 );
			}

			end_selection_op();
		}


		public void align_selection_right()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();

			/* Find right most edge. */
			LabelRegion obj_extent = selection_list.first().data.get_extent();
			double x2_max = obj_extent.x2;
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				if ( obj_extent.x2 > x2_max ) x2_max = obj_extent.x2;
			}

			/* Now adjust the object positions to line up the right edges. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dx = x2_max - obj_extent.x2;
				object.set_position_relative( dx, 0 );
			}

			end_selection_op();
		}


		public void align_selection_hcenter()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();
			LabelRegion obj_extent;

			/* Find average center of objects. */
			double xsum = 0;
			int    n = 0;
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				xsum += (obj_extent.x1 + obj_extent.x2) / 2.0;
				n++;
			}
			double xavg = xsum / n;

			/* find center of object closest to average center */
			obj_extent = selection_list.first().data.get_extent();
			double xcenter = (obj_extent.x1 + obj_extent.x2) / 2.0;
			double dxmin = Math.fabs( xavg - xcenter );
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				double dx = Math.fabs( xavg - (obj_extent.x1 + obj_extent.x2)/2.0 );
				if ( dx < dxmin )
				{
					dxmin = dx;
					xcenter = (obj_extent.x1 + obj_extent.x2) / 2.0;
				}
			}

			/* Now adjust the object positions to line up with this center. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dx = xcenter - (obj_extent.x1 + obj_extent.x2)/2.0;
				object.set_position_relative( dx, 0 );
			}

			end_selection_op();
		}


		public void align_selection_top()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();

			/* Find top most edge. */
			LabelRegion obj_extent = selection_list.first().data.get_extent();
			double y1_min = obj_extent.y1;
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				if ( obj_extent.y1 < y1_min ) y1_min = obj_extent.y1;
			}

			/* Now adjust the object positions to line up the top edges. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dy = y1_min - obj_extent.y1;
				object.set_position_relative( 0, dy );
			}

			end_selection_op();
		}


		public void align_selection_bottom()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();

			/* Find bottom most edge. */
			LabelRegion obj_extent = selection_list.first().data.get_extent();
			double y2_max = obj_extent.y2;
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				if ( obj_extent.y2 > y2_max ) y2_max = obj_extent.y2;
			}

			/* Now adjust the object positions to line up the bottom edges. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dy = y2_max - obj_extent.y2;
				object.set_position_relative( 0, dy );
			}

			end_selection_op();
		}


		public void align_selection_vcenter()
		{
			if ( is_selection_empty() || is_selection_atomic() )
			{
				return;
			}

			begin_selection_op();

			List<LabelObject> selection_list = get_selection_list();
			LabelRegion obj_extent;

			/* Find average center of objects. */
			double ysum = 0;
			int    n = 0;
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				ysum += (obj_extent.y1 + obj_extent.y2) / 2.0;
				n++;
			}
			double yavg = ysum / n;

			/* find center of object closest to average center */
			obj_extent = selection_list.first().data.get_extent();
			double ycenter = (obj_extent.y1 + obj_extent.y2) / 2.0;
			double dymin = Math.fabs( yavg - ycenter );
			foreach ( LabelObject object in selection_list.nth(1) )
			{
				obj_extent = object.get_extent();
				double dy = Math.fabs( yavg - (obj_extent.y1 + obj_extent.y2)/2.0 );
				if ( dy < dymin )
				{
					dymin = dy;
					ycenter = (obj_extent.y1 + obj_extent.y2) / 2.0;
				}
			}

			/* Now adjust the object positions to line up with this center. */
			foreach ( LabelObject object in selection_list )
			{
				obj_extent = object.get_extent();
				double dy = ycenter - (obj_extent.y1 + obj_extent.y2)/2.0;
				object.set_position_relative( 0, dy );
			}

			end_selection_op();
		}


		public void center_selection_horiz()
		{
			begin_selection_op();

			double w, h;
			get_size( out w, out h );
			double x_label_center = w / 2.0;

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					LabelRegion obj_extent = object.get_extent();
					double x_obj_center = (obj_extent.x1 + obj_extent.x2) / 2.0;
					double dx = x_label_center - x_obj_center;
					object.set_position_relative( dx, 0 );
				}
			}

			end_selection_op();
		}


		public void center_selection_vert()
		{
			begin_selection_op();

			double w, h;
			get_size( out w, out h );
			double y_label_center = h / 2.0;

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					LabelRegion obj_extent = object.get_extent();
					double y_obj_center = (obj_extent.y1 + obj_extent.y2) / 2.0;
					double dy = y_label_center - y_obj_center;
					object.set_position_relative( 0, dy );
				}
			}

			end_selection_op();
		}


		public void move_selection( double dx,
		                            double dy )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.set_position_relative( dx, dy );
				}
			}

			end_selection_op();
		}


		public void set_selection_font_family( string font_family )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.font_family = font_family;
				}
			}

			end_selection_op();
		}


		public void set_selection_font_size( double font_size )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.font_size = font_size;
				}
			}

			end_selection_op();
		}


		public void set_selection_font_weight( Pango.Weight font_weight )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.font_weight = font_weight;
				}
			}

			end_selection_op();
		}


		public void set_selection_font_italic_flag( bool font_italic_flag )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.font_italic_flag = font_italic_flag;
				}
			}

			end_selection_op();
		}


		public void set_selection_text_alignment( Pango.Alignment text_alignment )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.text_alignment = text_alignment;
				}
			}

			end_selection_op();
		}


		public void set_selection_text_line_spacing( double text_line_spacing )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.text_line_spacing = text_line_spacing;
				}
			}

			end_selection_op();
		}


		public void set_selection_text_color( ColorNode text_color_node )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.text_color_node = text_color_node;
				}
			}

			end_selection_op();
		}


		public void set_selection_line_width( double line_width )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.line_width = line_width;
				}
			}

			end_selection_op();
		}


		public void set_selection_line_color( ColorNode line_color_node )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.line_color_node = line_color_node;
				}
			}

			end_selection_op();
		}


		public void set_selection_fill_color( ColorNode fill_color_node )
		{
			begin_selection_op();

			foreach( LabelObject object in object_list )
			{
				if ( object.is_selected() )
				{
					object.fill_color_node = fill_color_node;
				}
			}

			end_selection_op();
		}


	}

}
#endif
