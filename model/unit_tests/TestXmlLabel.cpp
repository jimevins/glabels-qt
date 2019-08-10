/*  TestXmlLabel.cpp
 *
 *  Copyright (C) 2018  Jim Evins <evins@snaught.com>
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

#include "TestXmlLabel.h"
#include "Test_Constants.h"

#include "model/XmlLabelCreator.h"
#include "model/XmlLabelParser.h"

#include "barcode/Backends.h"
#include "model/ColorNode.h"
#include "model/Size.h"

#include "model/ModelBarcodeObject.h"
#include "model/ModelBoxObject.h"
#include "model/ModelEllipseObject.h"
#include "model/ModelLineObject.h"
#include "model/ModelImageObject.h"
#include "model/ModelTextObject.h"

#include <QtDebug>


QTEST_MAIN(TestXmlLabel)


void TestXmlLabel::initTestCase()
{
	using namespace glabels::barcode;
	Backends::init();
}


void TestXmlLabel::serializeDeserialize()
{
	using namespace glabels::model;
	using namespace glabels::barcode;

	//
	// Empty object list
	//
	QList<ModelObject*> objects, outObjects;
	QByteArray buffer, outBuffer;

	QCOMPARE( objects.count(), 0 );
	XmlLabelCreator::serializeObjects( objects, buffer );
	outObjects = XmlLabelParser::deserializeObjects( buffer );
	QCOMPARE( objects.count(), outObjects.count() );
	QCOMPARE( objects, outObjects );
	XmlLabelCreator::serializeObjects( outObjects, outBuffer );
	QCOMPARE( buffer, outBuffer );

	//
	// All objects list
	//
	bool lock = true, noLock = false, shadow = true, noShadow = false;
	ColorNode black( Qt::black ), white( Qt::white ), red( Qt::red ), green( Qt::green ), blue( Qt::blue );
	QMatrix tMatrix( 1, 0, 0, 1, 50.0, 50.0 ), sMatrix( 0.5, 0, 0, 1.0, 0, 0 );
	QImage png;
	QVERIFY( png.loadFromData( QByteArray::fromBase64( glabels::test::blue_8x8_png ), "PNG" ) );
	QByteArray svg = glabels::test::red_8x8_svg;
	Style bcStyle = Backends::defaultStyle();

	objects << new ModelBoxObject( 0, 1, 10, 20, lock, 2, red, green, tMatrix, shadow, 1, 2, 0.7, black );
	objects << new ModelEllipseObject( 1, 2, 30, 40, noLock, 3, black, white, sMatrix, shadow, 2, 3, 0.8, blue );
	objects << new ModelImageObject( 2, 3, 50, 50, lock, TextNode( false, "" ), tMatrix, noShadow, 3, 4, 0.9, white );
	objects << new ModelImageObject( 3, 4, 60, 70, noLock, "image2.png", png, sMatrix, shadow, 6, 4, 0.9, black );
	objects << new ModelImageObject( 4, 5, 70, 80, lock, "image3.svg", svg );
	objects << new ModelImageObject( 5, 6, 80, 90, noLock, TextNode( true, "${key}" ), tMatrix, shadow );
	objects << new ModelImageObject( 6, 7, 90, 100, lock, TextNode( false, "image5.jpg" ) ); // Gives warning that embedded file missing
	objects << new ModelLineObject( 7, 8, 100, 110, 4, green, sMatrix, shadow, 5, 5, 0.5, red );
	objects << new ModelTextObject( 8, 9, 110, 120, lock, "text", "Serif", 12, QFont::Bold, true, true, red,
									Qt::AlignHCenter, Qt::AlignBottom, QTextOption::NoWrap, 1.3, false, sMatrix, shadow, 5, 5, 0.5, red );
	objects << new ModelBarcodeObject( 9, 10, 50, 50, noLock, bcStyle, true, true, QString("1234"), black, tMatrix );
	QCOMPARE( objects.count(), 10 );

	buffer.clear();
	XmlLabelCreator::serializeObjects( objects, buffer );
	outObjects = XmlLabelParser::deserializeObjects( buffer );
	QCOMPARE( objects.count(), outObjects.count() );

	for ( int i = 0; i < objects.count(); i++ )
	{
		qDebug() << "object" << i;
		QVERIFY( objects.at(i)->id() != outObjects.at(i)->id() ); // Ids are generated and unique
		QCOMPARE( objects.at(i)->x0(), outObjects.at(i)->x0() );
		QCOMPARE( objects.at(i)->x0().pt(), (double)i );
		QCOMPARE( objects.at(i)->y0(), outObjects.at(i)->y0() );
		QCOMPARE( objects.at(i)->y0().pt(), (double)(i + 1) );
		QCOMPARE( objects.at(i)->w().pt(), outObjects.at(i)->w().pt() ); // Use `pt()` so invoke `qFuzzyCompare(double, double)` otherwise get rounding difference for Barcode
		QCOMPARE( objects.at(i)->h().pt(), outObjects.at(i)->h().pt() ); // Fuzzy
		QCOMPARE( objects.at(i)->lockAspectRatio(), outObjects.at(i)->lockAspectRatio() );
		QCOMPARE( objects.at(i)->lockAspectRatio(), (bool)((i + 1) % 2) );
		QCOMPARE( objects.at(i)->matrix(), outObjects.at(i)->matrix() );
		QCOMPARE( objects.at(i)->shadow(), outObjects.at(i)->shadow() );
		QCOMPARE( objects.at(i)->shadowX(), outObjects.at(i)->shadowX() );
		QCOMPARE( objects.at(i)->shadowY(), outObjects.at(i)->shadowY() );
		QCOMPARE( objects.at(i)->shadowOpacity(), outObjects.at(i)->shadowOpacity() );
		QVERIFY( objects.at(i)->shadowColorNode() == outObjects.at(i)->shadowColorNode() );
		QCOMPARE( objects.at(i)->naturalSize().w().pt(), outObjects.at(i)->naturalSize().w().pt() ); // Fuzzy
		QCOMPARE( objects.at(i)->naturalSize().h().pt(), outObjects.at(i)->naturalSize().h().pt() ); // Fuzzy

		QCOMPARE( objects.at(i)->text(), outObjects.at(i)->text() );
		QCOMPARE( objects.at(i)->fontFamily(), outObjects.at(i)->fontFamily() );
		QCOMPARE( objects.at(i)->fontSize(), outObjects.at(i)->fontSize() );
		QCOMPARE( objects.at(i)->fontWeight(), outObjects.at(i)->fontWeight() );
		QCOMPARE( objects.at(i)->fontItalicFlag(), outObjects.at(i)->fontItalicFlag() );
		QCOMPARE( objects.at(i)->fontUnderlineFlag(), outObjects.at(i)->fontUnderlineFlag() );
		QVERIFY( objects.at(i)->textColorNode() == outObjects.at(i)->textColorNode() );
		QCOMPARE( objects.at(i)->textHAlign(), outObjects.at(i)->textHAlign() );
		QCOMPARE( objects.at(i)->textVAlign(), outObjects.at(i)->textVAlign() );
		QCOMPARE( objects.at(i)->textWrapMode(), outObjects.at(i)->textWrapMode() );
		QCOMPARE( objects.at(i)->textLineSpacing(), outObjects.at(i)->textLineSpacing() );
		QCOMPARE( objects.at(i)->textAutoShrink(), outObjects.at(i)->textAutoShrink() );

		QVERIFY( objects.at(i)->filenameNode() == outObjects.at(i)->filenameNode() );
		if ( objects.at(i)->image() )
		{
			QCOMPARE( *(objects.at(i)->image()), *(outObjects.at(i)->image()) );
		}
		else
		{
			QCOMPARE( objects.at(i)->image(), outObjects.at(i)->image() );
		}
		QCOMPARE( objects.at(i)->svg(), outObjects.at(i)->svg() );

		QCOMPARE( objects.at(i)->lineWidth(), outObjects.at(i)->lineWidth() );
		QVERIFY( objects.at(i)->lineColorNode() == outObjects.at(i)->lineColorNode() );
		QVERIFY( objects.at(i)->fillColorNode() == outObjects.at(i)->fillColorNode() );

		QCOMPARE( objects.at(i)->bcData(), outObjects.at(i)->bcData() );
		QCOMPARE( objects.at(i)->bcTextFlag(), outObjects.at(i)->bcTextFlag() );
		QCOMPARE( objects.at(i)->bcChecksumFlag(), outObjects.at(i)->bcChecksumFlag() );
		QVERIFY( objects.at(i)->bcColorNode() == outObjects.at(i)->bcColorNode() );
		QVERIFY( !( objects.at(i)->bcStyle() != outObjects.at(i)->bcStyle() ) ); // Only != operator
		QCOMPARE( objects.at(i)->bcFormatDigits(), outObjects.at(i)->bcFormatDigits() );

		QCOMPARE( objects.at(i)->canText(), outObjects.at(i)->canText() );
		QCOMPARE( objects.at(i)->canFill(), outObjects.at(i)->canFill() );
		QCOMPARE( objects.at(i)->canLineColor(), outObjects.at(i)->canLineColor() );
		QCOMPARE( objects.at(i)->canLineWidth(), outObjects.at(i)->canLineWidth() );
	}

	outBuffer.clear();
	XmlLabelCreator::serializeObjects( outObjects, outBuffer );
	QCOMPARE( buffer, outBuffer );
}
