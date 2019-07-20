/*  TestColorNode.cpp
 *
 *  Copyright (C) 2019  Jim Evins <evins@snaught.com>
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

#include "TestColorNode.h"

#include "model/ColorNode.h"

#include "merge/Record.h"

#include <QtDebug>


QTEST_MAIN(TestColorNode)

using namespace glabels::model;
using namespace glabels::merge;


void TestColorNode::colorNode()
{
	uint32_t rgbaBlackTransparent = 0;
	uint32_t rgbaWhite = 0xFFFFFFFF;
	uint32_t rgbaRed = 0xFF0000FF; // ColorNode uses RGBA. QColor set alpha to opaque 0xFF by default
	uint32_t qRgbaRed = 0xFFFF0000; // QColor uses ARGB, ie alpha at top
	uint32_t qRgbaGreen80 = 0x8000FF00;

	QColor blackTransparent = QColor::fromRgba( rgbaBlackTransparent );
	QColor white = QColor::fromRgba( rgbaWhite );
	QColor red = QColor::fromRgba( qRgbaRed );
	QColor green80 = QColor::fromRgba( qRgbaGreen80 );

	Record record;

	ColorNode colorNode;
	QVERIFY( !colorNode.isField() );
	QCOMPARE( colorNode.color(), blackTransparent );
	QCOMPARE( colorNode.key(), QString( "" ) );
	QCOMPARE( colorNode.rgba(), rgbaBlackTransparent );
	QCOMPARE( colorNode.color( nullptr ), blackTransparent );
	QCOMPARE( colorNode.color( &record ), blackTransparent );

	colorNode.setField( true );
	QVERIFY( colorNode.isField() );
	colorNode.setField( false );
	QVERIFY( !colorNode.isField() );

	colorNode.setColor( white );
	QCOMPARE( colorNode.color(), white );
	QCOMPARE( colorNode.rgba(), rgbaWhite );
	QCOMPARE( colorNode.color( nullptr ), white );
	QCOMPARE( colorNode.color( &record ), white );

	colorNode.setKey( "key1" );
	QCOMPARE( colorNode.key(), QString( "key1" ) );

	///
	/// Constructors
	///
	ColorNode colorNode2( true, white, QString( "key2" ) );
	QVERIFY( colorNode2.isField() );
	QCOMPARE( colorNode2.key(), QString( "key2" ) );
	QCOMPARE( colorNode2.color(), white );

	QVERIFY( colorNode2 != colorNode );
	colorNode.setField( true );
	QVERIFY( colorNode2 != colorNode );
	colorNode.setKey( "key2" );
	QVERIFY( colorNode2 == colorNode );

	ColorNode colorNode3( red );
	QVERIFY( !colorNode3.isField() );
	QCOMPARE( colorNode3.key(), QString( "" ) );
	QCOMPARE( colorNode3.color(), red );
	QCOMPARE( colorNode3.rgba(), rgbaRed );

	QVERIFY( colorNode3 != colorNode );
	colorNode.setField( false );
	QVERIFY( colorNode3 != colorNode );
	colorNode.setKey( "" );
	QVERIFY( colorNode3 != colorNode );
	colorNode.setColor( red );
	QVERIFY( colorNode3 == colorNode );

	colorNode = ColorNode( QString( "key1" ) );
	QVERIFY( colorNode.isField() ); // Defaults to true if given key only
	QCOMPARE( colorNode.key(), QString( "key1" ) );
	QCOMPARE( colorNode.color(), blackTransparent );
	QCOMPARE( colorNode.color( &record ), blackTransparent );

	///
	/// Record
	///
	record["key1"] = "white";
	QCOMPARE( colorNode.color( &record ), white );

	record["key1"] = "red";
	QCOMPARE( colorNode.color( &record ), red );

	record["key1"] = "#FF0000";
	QCOMPARE( colorNode.color( &record ), red );

	record["key1"] = "#FFFF0000"; // ARGB
	QCOMPARE( colorNode.color( &record ), red );

	record["key1"] = "#8000FF00";
	QCOMPARE( colorNode.color( &record ), green80 );

	colorNode.setKey( "key2" );
	QCOMPARE( colorNode.color( &record ), blackTransparent );
	record["key2"] = "#8000FF00";
	QCOMPARE( colorNode.color( &record ), green80 );
}
