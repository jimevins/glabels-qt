/*  PageRenderer.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#ifndef glabels_PageRenderer_h
#define glabels_PageRenderer_h


#include "libglabels/Point.h"

#include <QVector>
#include <QRect>


class QPainter; // Forward reference


namespace glabels
{
	class LabelModel; // Forward reference
	class MergeRecord; // Forward reference


	///
	///  PageRenderer Widget
	///
	class PageRenderer
	{
		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		PageRenderer();


		/////////////////////////////////
		// Public Methods
		/////////////////////////////////
	public:
		void setModel( const LabelModel* model );
		void setNLabels( int nLabels );
		void setStartLabel( int startLabel );
		void setPrintOutlines( bool printOutlinesFlag );
		void setPrintCropMarks( bool printCropMarksFlag );
		void setPrintReverse( bool printReverseFlag );
		void setIPage( int iPage );
		int nPages() const;
		QRectF pageRect() const;
		void printPage( QPainter* painter ) const;
		void printPage( QPainter* painter, int iPage ) const;


		/////////////////////////////////
		// Internal Methods
		/////////////////////////////////
	private:
		void updateNPages();
		void printSimplePage( QPainter* painter, int iPage ) const;
		void printMergePage( QPainter* painter, int iPage ) const;
		void printCropMarks( QPainter* painter ) const;
		void printOutline( QPainter* painter ) const;
		void clipLabel( QPainter* painter ) const;
		void printLabel( QPainter* painter, MergeRecord* record ) const;


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		const LabelModel* mModel;
		int               mNLabels;
		int               mStartLabel;
		bool              mPrintOutlines;
		bool              mPrintCropMarks;
		bool              mPrintReverse;
		int               mIPage;

		int               mNPages;
		int               mNLabelsPerPage;

		QVector<libglabels::Point> mOrigins;
	};

}

#endif // glabels_PageRenderer_h
