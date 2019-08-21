/*  TestModelImageObject.cpp
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

#include "TestModelImageObject.h"
#include "Test_Constants.h"

#include "model/Model.h"
#include "model/ModelImageObject.h"
#include "model/Size.h"

#include "merge/Factory.h"
#include "merge/TextCsvKeys.h"
#include "merge/Record.h"

#include <QtDebug>


QTEST_MAIN(TestModelImageObject)

using namespace glabels::model;
using namespace glabels::merge;


void TestModelImageObject::initTestCase()
{
	Factory::init();
}


void TestModelImageObject::readImageFile()
{
	QImage paintDevice( 10, 160, QImage::Format_RGB32 );
	paintDevice.fill( Qt::white );
	QPainter painter( &paintDevice );

	Model model;

	ModelImageObject object;
	object.setX0( 1 );
	object.setY0( 1 );
	object.setSize( 8, 8 );
	TextNode filenameNode( true, "image" );
	object.setFilenameNode( filenameNode );

	model.addObject( object.clone() );

	object.setY0( 11 );
	object.setSize( 8, 8 );
	TextNode filenameNode2( true, "var" );
	object.setFilenameNode( filenameNode2 );

	model.addObject( object.clone() );

	// Blue 8x8 square
	QByteArray pngArray = QByteArray::fromBase64( glabels::test::blue_8x8_png );
	QImage png;
	QVERIFY( png.loadFromData( pngArray, "PNG" ) );
	QTemporaryFile png1; png1.open(); png1.close(); png.save( png1.fileName(), "PNG" );
	QTemporaryFile png2; png2.open(); png2.close(); png.save( png2.fileName(), "PNG" );

	// Red 8x8 square
	QByteArray svg = glabels::test::red_8x8_svg;
	QString svgTemplate = QDir::tempPath().append( QDir::separator() ).append( "TestModelImageObject_XXXXXX.svg" );
	QTemporaryFile svg1( svgTemplate ); svg1.open(); svg1.write( svg ); svg1.close();
	QTemporaryFile svg2( svgTemplate ); svg2.open(); svg2.write( svg ); svg2.close();

	QFileInfo png1FileInfo( png1.fileName() );
	QFileInfo png2FileInfo( png2.fileName() );
	QFileInfo svg1FileInfo( svg1.fileName() );
	QFileInfo svg2FileInfo( svg2.fileName() );

	QString modelFileName = png1FileInfo.dir().absolutePath().append( QDir::separator() ).append( "TestModelImageObject.glabels" );
	model.setFileName( modelFileName );

	QTemporaryFile csv;
	csv.open();
	csv.write( "id,image,type\n" );
	csv.write( "1," ); csv.write( png1FileInfo.fileName().toUtf8() ); csv.write( ",png\n" );
	csv.write( "2," ); csv.write( png1FileInfo.filePath().toUtf8() ); csv.write( ",png\n" );
	csv.write( "3," ); csv.write( svg1FileInfo.fileName().toUtf8() ); csv.write( ",svg\n" );
	csv.write( "4," ); csv.write( svg2FileInfo.filePath().toUtf8() ); csv.write( ",svg\n" );
	csv.write( "5," ); csv.write( svg2FileInfo.fileName().toUtf8() ); csv.write( ",svg\n" );
	csv.write( "6," ); csv.write( png2FileInfo.fileName().toUtf8() ); csv.write( ",png\n" );
	csv.write( "7," ); csv.write( svg1FileInfo.filePath().toUtf8() ); csv.write( ",svg\n" );
	csv.write( "8," ); csv.write( png2FileInfo.filePath().toUtf8() ); csv.write( ",png\n" );
	csv.close();

	Merge* merge = Factory::createMerge( TextCsvKeys::id() );
	QVERIFY( merge );
	QCOMPARE( merge->id(), TextCsvKeys::id() );
	merge->setSource( csv.fileName() );
	model.setMerge( merge );

	// Green 8x8 square
	pngArray = QByteArray::fromBase64( glabels::test::green_8x8_png );
	QVERIFY( png.loadFromData( pngArray, "PNG" ) );
	QTemporaryFile png3; png3.open(); png3.close(); png.save( png3.fileName(), "PNG" );
	QFileInfo png3FileInfo( png3.fileName() );

	Variable var( Variable::Type::STRING, "var", png3FileInfo.fileName(), Variable::Increment::PER_ITEM );
	model.variables()->addVariable( var );

	const QList<Record*> records = merge->selectedRecords();
	QCOMPARE( records.size(), 8 );
	int i, cnt;
	for ( i = 0, cnt = records.size(); i < cnt; i++ )
	{
		model.draw( &painter, false, records[i], model.variables() );
		painter.translate( 0, 20 );
	}
	paintDevice.save( "/tmp/readimagefile.png", "PNG" );

	QColor color, white = Qt::white;
	for ( i = 0, cnt = records.size(); i < cnt; i++ )
	{
		qDebug() << "record" << i;
		color = records[i]->value( "type" ) == "png" ? Qt::blue : Qt::red;
		QCOMPARE( white, paintDevice.pixelColor( 1, 0 + i * 20 ) );
		QCOMPARE( color, paintDevice.pixelColor( 1, 1 + i * 20 ) );
		QCOMPARE( color, paintDevice.pixelColor( 1, 8 + i * 20 ) );
		QCOMPARE( white, paintDevice.pixelColor( 1, 9 + i * 20 ) );

		// Variable
		color = Qt::green;
		QCOMPARE( white, paintDevice.pixelColor( 1, 10 + i * 20 ) );
		QCOMPARE( color, paintDevice.pixelColor( 1, 11 + i * 20 ) );
		QCOMPARE( color, paintDevice.pixelColor( 1, 18 + i * 20 ) );
		QCOMPARE( white, paintDevice.pixelColor( 1, 19 + i * 20 ) );
	}

	delete model.merge();
	delete model.variables();
}
