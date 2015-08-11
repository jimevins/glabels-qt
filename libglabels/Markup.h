/*  Markup.h
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

#ifndef libglabels_Markup_h
#define libglabels_Markup_h

#include <QGraphicsItem>
#include <QPainterPath>

#include "Frame.h"


namespace libglabels
{

	class Markup
	{
	public:
		virtual Markup* dup() const = 0;
		virtual QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const = 0;
	};


	class MarkupMargin : public Markup
	{
	public:
		MarkupMargin( double size );

		double size() const;

		Markup* dup() const;

		QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const;

	private:
		double  mSize;
	};


	class MarkupLine : public Markup
	{
	public:
		MarkupLine( double x1, double y1, double x2, double y2 );

		double x1() const;
		double y1() const;
		double x2() const;
		double y2() const;

		Markup* dup() const;

		QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const;

	private:
		double  mX1;
		double  mY1;
		double  mX2;
		double  mY2;
	};


	class MarkupRect : public Markup
	{
	public:
		MarkupRect( double x1, double y1, double w, double h, double r );

		double x1() const;
		double y1() const;
		double w() const;
		double h() const;
		double r() const;

		Markup* dup() const;

		QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const;

	private:
		double  mX1;
		double  mY1;
		double  mW;
		double  mH;
		double  mR;
	};


	class MarkupEllipse : public Markup
	{
	public:
		MarkupEllipse( double x1, double y1, double w, double h );

		double x1() const;
		double y1() const;
		double w() const;
		double h() const;

		Markup* dup() const;

		QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const;

	private:
		double  mX1;
		double  mY1;
		double  mW;
		double  mH;
	};


	class MarkupCircle : public Markup
	{
	public:
		MarkupCircle( double x0, double y0, double r );

		double x0() const;
		double y0() const;
		double r() const;

		Markup* dup() const;

		QGraphicsItem* createGraphicsItem( const Frame* frame, const QPen& pen ) const;

	private:
		double  mX0;
		double  mY0;
		double  mR;
	};
	

}


#include "Markup.inl"


#endif // libglabels_Markup_h
