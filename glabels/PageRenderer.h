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

#ifndef PageRenderer_h
#define PageRenderer_h


#include "libglabels/Point.h"

#include "Merge/Merge.h"
#include "Merge/Record.h"

#include <QVector>
#include <QRect>

// Forward references
class QPainter;
class LabelModel;


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
	void setNCopies( int nCopies );
	void setStartLabel( int startLabel );
	void setPrintOutlines( bool printOutlinesFlag );
	void setPrintCropMarks( bool printCropMarksFlag );
	void setPrintReverse( bool printReverseFlag );
	void setIPage( int iPage );
	int nItems() const;
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
	void printLabel( QPainter* painter, merge::Record* record ) const;


	/////////////////////////////////
	// Private Data
	/////////////////////////////////
private:
	const LabelModel*   mModel;
	const merge::Merge* mMerge;
	
	int               mNCopies;
	int               mStartLabel;
	int               mLastLabel;
	bool              mPrintOutlines;
	bool              mPrintCropMarks;
	bool              mPrintReverse;
	int               mIPage;

	bool              mIsMerge;
	int               mNPages;
	int               mNLabelsPerPage;

	QVector<glabels::Point> mOrigins;
};


#endif // PageRenderer_h
