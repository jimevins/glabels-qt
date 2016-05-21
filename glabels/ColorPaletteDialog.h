/*  ColorPaletteDialog.h
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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

#ifndef ColorPaletteDialog_h
#define ColorPaletteDialog_h

#include <QObject>
#include <QDialog>

#include "ColorNode.h"
#include "ColorHistory.h"
#include "ColorPaletteItem.h"
#include "ColorPaletteButtonItem.h"
#include "FieldMenu.h"

class QComboBox; // Forward reference


///
/// Color Palette Dialog
///
class ColorPaletteDialog : public QDialog
{
	Q_OBJECT


	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	ColorPaletteDialog( const QString& defaultLabel,
	                    const QColor&  defaultColor,
	                    const QColor&  color,
	                    QWidget*       parent = 0 );


	/////////////////////////////////
	// Signals
	/////////////////////////////////
signals:
	void colorChanged( ColorNode colorNode, bool isDefault );


	/////////////////////////////////
	// Public Methods
	/////////////////////////////////
public:
	void   setColorNode( const ColorNode& colorNode );
	void   setKeys( const QStringList& keyList );
	void   clearKeys();


	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onDefaultItemActivated();
	void onPaletteItemActivated( int id );
	void onHistoryItemActivated( int id );
	void onCustomColorItemActivated();
	void onColorHistoryChanged();
	void onComboIndexChanged( int index );

protected:
	void showEvent( QShowEvent* event );
	

	/////////////////////////////////
	// Private Methods
	/////////////////////////////////
private:
	void loadCustomColorHistory();


	/////////////////////////////////
	// Private Members
	/////////////////////////////////
private:
	QColor        mDefaultColor;
	ColorNode     mColorNode;

	static const int PALETTE_COLS = ColorHistory::MAX_COLORS;
	static const int PALETTE_ROWS = 4;

	typedef struct {
		QString colorSpec;
		QString name;
	} ColorTableEntry;

	static ColorTableEntry mColorTable[];

	ColorHistory* mColorHistory;
	ColorPaletteItem* mHistoryItem[PALETTE_COLS];

	QComboBox* mMergeFieldCombo;
	QStringList mKeys;

};


#endif // ColorPaletteDialog_h
