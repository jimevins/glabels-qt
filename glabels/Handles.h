/*  Handles.h
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

#ifndef glabels_Handles_h
#define glabels_Handles_h


#include <QPainter>
#include <QPainterPath>


namespace glabels
{

	class LabelModelObject;


	///
	/// Handle Base Class
	///
	class Handle
	{
		////////////////////////////
		// Location enumeration
		////////////////////////////
	public:
		enum Location { NW, N, NE, E, SE, S, SW, W, P1, P2 };
		
		
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	protected:
		Handle( LabelModelObject* owner, Location location );
	public:
		virtual ~Handle();

		
		////////////////////////////
		// Attribue Methods
		////////////////////////////
		LabelModelObject* owner() const;
		Location location() const;
		

		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const = 0;
		virtual QPainterPath path( double scale ) const = 0;
	protected:
		void drawAt( QPainter* painter, double scale, double x, double y ) const;
		QPainterPath pathAt( double scale, double x, double y ) const;


		////////////////////////////
		// Protected Data
		////////////////////////////
	protected:
		LabelModelObject* mOwner;
		Location mLocation;

	};


	///
	/// HandleNorth Class
	///
	class HandleNorth : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleNorth( LabelModelObject* owner );
		virtual ~HandleNorth();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleNorthEast Class
	///
	class HandleNorthEast : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleNorthEast( LabelModelObject* owner );
		virtual ~HandleNorthEast();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleEast Class
	///
	class HandleEast : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleEast( LabelModelObject* owner );
		virtual ~HandleEast();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleSouthEast Class
	///
	class HandleSouthEast : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleSouthEast( LabelModelObject* owner );
		virtual ~HandleSouthEast();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleSouth Class
	///
	class HandleSouth : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleSouth( LabelModelObject* owner );
		virtual ~HandleSouth();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleSouthWest Class
	///
	class HandleSouthWest : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleSouthWest( LabelModelObject* owner );
		virtual ~HandleSouthWest();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleWest Class
	///
	class HandleWest : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleWest( LabelModelObject* owner );
		virtual ~HandleWest();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleNorthWest Class
	///
	class HandleNorthWest : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleNorthWest( LabelModelObject* owner );
		virtual ~HandleNorthWest();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleP1 Class
	///
	class HandleP1 : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleP1( LabelModelObject* owner );
		virtual ~HandleP1();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


	///
	/// HandleP2 Class
	///
	class HandleP2 : public Handle
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		HandleP2( LabelModelObject* owner );
		virtual ~HandleP2();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		virtual void  draw( QPainter* painter, double scale ) const;
		virtual QPainterPath path( double scale ) const;
	};


}

#endif // glabels_Handles_h
