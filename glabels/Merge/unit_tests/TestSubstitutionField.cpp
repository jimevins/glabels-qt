/*  TestSubstitutionField.cpp
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#include "TestSubstitutionField.h"

#include "SubstitutionField.h"


QTEST_MAIN(TestSubstitutionField)
	

void TestSubstitutionField::construction()
{
	glabels::merge::SubstitutionField f1( "${1234}" );
	QCOMPARE( f1.fieldName(),    QString( "1234" ) );

	glabels::merge::SubstitutionField f2( "${abc:=ABC}" );
	QCOMPARE( f2.fieldName(),    QString( "abc" ) );
	QCOMPARE( f2.defaultValue(), QString( "ABC" ) );

	glabels::merge::SubstitutionField f3( "${x:%08.2f}" );
	QCOMPARE( f3.fieldName(),    QString( "x" ) );
	QCOMPARE( f3.format(),       QString( "%08.2f" ) );
	QCOMPARE( f3.formatType(),   QChar('f') );

	glabels::merge::SubstitutionField f4( "${y:%08.2f:=12.34}" );
	QCOMPARE( f4.fieldName(),    QString( "y" ) );
	QCOMPARE( f4.defaultValue(), QString( "12.34" ) );
	QCOMPARE( f4.format(),       QString( "%08.2f" ) );
	QCOMPARE( f4.formatType(),   QChar('f') );
}


void TestSubstitutionField::simpleEvaluation()
{
	glabels::merge::SubstitutionField f1( "${1}" );
	glabels::merge::SubstitutionField f2( "${2}" );
	glabels::merge::SubstitutionField f3( "${3}" );
	glabels::merge::SubstitutionField f4( "${4}" );

	glabels::merge::Record record1;
	record1[ "1" ] = "Abcdefg";
	record1[ "2" ] = "Hijklmn";
	record1[ "3" ] = "Opqrstu";
	record1[ "4" ] = "Vwxyz!@";

	QCOMPARE( f1.evaluate( record1 ), QString( "Abcdefg" ) );
	QCOMPARE( f2.evaluate( record1 ), QString( "Hijklmn" ) );
	QCOMPARE( f3.evaluate( record1 ), QString( "Opqrstu" ) );
	QCOMPARE( f4.evaluate( record1 ), QString( "Vwxyz!@" ) );

	glabels::merge::Record record2;
	record2[ "1" ] = "1234567";
	record2[ "2" ] = "FooBar";
	record2[ "3" ] = "8901234";
	record2[ "4" ] = "#$%^&*";

	QCOMPARE( f1.evaluate( record2 ), QString( "1234567" ) );
	QCOMPARE( f2.evaluate( record2 ), QString( "FooBar" ) );
	QCOMPARE( f3.evaluate( record2 ), QString( "8901234" ) );
	QCOMPARE( f4.evaluate( record2 ), QString( "#$%^&*" ) );
}


void TestSubstitutionField::defaultValueEvaluation()
{
	glabels::merge::SubstitutionField f1( "${1:=foo1}" );
	glabels::merge::SubstitutionField f2( "${2:=foo2}" );
	glabels::merge::SubstitutionField f3( "${3:=foo3}" );
	glabels::merge::SubstitutionField f4( "${4:=foo4}" );

	glabels::merge::Record record1;
	record1[ "1" ] = "Abcdefg";
	record1[ "2" ] = "Hijklmn";
	record1[ "3" ] = "Opqrstu";
	record1[ "4" ] = "Vwxyz!@";

	QCOMPARE( f1.evaluate( record1 ), QString( "Abcdefg" ) );
	QCOMPARE( f2.evaluate( record1 ), QString( "Hijklmn" ) );
	QCOMPARE( f3.evaluate( record1 ), QString( "Opqrstu" ) );
	QCOMPARE( f4.evaluate( record1 ), QString( "Vwxyz!@" ) );

	glabels::merge::Record record2; // All fields empty

	QCOMPARE( f1.evaluate( record2 ), QString( "foo1" ) );
	QCOMPARE( f2.evaluate( record2 ), QString( "foo2" ) );
	QCOMPARE( f3.evaluate( record2 ), QString( "foo3" ) );
	QCOMPARE( f4.evaluate( record2 ), QString( "foo4" ) );

	glabels::merge::Record record3;
	record3[ "1" ] = "xyzzy";
	// Field "2" empty
	// Field "3" empty
	record3[ "4" ] = "plugh";
	
	QCOMPARE( f1.evaluate( record3 ), QString( "xyzzy" ) );
	QCOMPARE( f2.evaluate( record3 ), QString( "foo2" ) );
	QCOMPARE( f3.evaluate( record3 ), QString( "foo3" ) );
	QCOMPARE( f4.evaluate( record3 ), QString( "plugh" ) );
}


void TestSubstitutionField::formattedStringEvaluation()
{
	glabels::merge::SubstitutionField f1( "${1:%10s}" );
	glabels::merge::SubstitutionField f2( "${2:%10s}" );
	glabels::merge::SubstitutionField f3( "${3:%10s}" );
	glabels::merge::SubstitutionField f4( "${4:%10s}" );

	glabels::merge::SubstitutionField f5( "${5:%-10s}" );
	glabels::merge::SubstitutionField f6( "${6:%-10s}" );
	glabels::merge::SubstitutionField f7( "${7:%-10s}" );
	glabels::merge::SubstitutionField f8( "${8:%-10s}" );

	glabels::merge::Record record1;
	record1[ "1" ] = "0";
	record1[ "2" ] = "1";
	record1[ "3" ] = "-1";
	record1[ "4" ] = "3.14";

	record1[ "5" ] = "0";
	record1[ "6" ] = "100";
	record1[ "7" ] = "-100";
	record1[ "8" ] = "3.14";
	
	QCOMPARE( f1.evaluate( record1 ), QString( "         0" ) );
	QCOMPARE( f2.evaluate( record1 ), QString( "         1" ) );
	QCOMPARE( f3.evaluate( record1 ), QString( "        -1" ) );
	QCOMPARE( f4.evaluate( record1 ), QString( "      3.14" ) );

	QCOMPARE( f5.evaluate( record1 ), QString( "0         " ) );
	QCOMPARE( f6.evaluate( record1 ), QString( "100       " ) );
	QCOMPARE( f7.evaluate( record1 ), QString( "-100      " ) );
	QCOMPARE( f8.evaluate( record1 ), QString( "3.14      " ) );
}


void TestSubstitutionField::formattedFloatEvaluation()
{
	glabels::merge::SubstitutionField f1( "${1:%+5.2f}" );
	glabels::merge::SubstitutionField f2( "${2:%+5.2f}" );
	glabels::merge::SubstitutionField f3( "${3:%+5.2f}" );
	glabels::merge::SubstitutionField f4( "${4:%+5.2f}" );

	glabels::merge::SubstitutionField f5( "${5:%+5.2e}" );
	glabels::merge::SubstitutionField f6( "${6:%+5.2e}" );
	glabels::merge::SubstitutionField f7( "${7:%+5.2e}" );
	glabels::merge::SubstitutionField f8( "${8:%+5.2e}" );

	glabels::merge::Record record1;
	record1[ "1" ] = "0";
	record1[ "2" ] = "1";
	record1[ "3" ] = "-1";
	record1[ "4" ] = "3.14";

	record1[ "5" ] = "0";
	record1[ "6" ] = "100";
	record1[ "7" ] = "-100";
	record1[ "8" ] = "3.14";
	
	QCOMPARE( f1.evaluate( record1 ), QString( "+0.00" ) );
	QCOMPARE( f2.evaluate( record1 ), QString( "+1.00" ) );
	QCOMPARE( f3.evaluate( record1 ), QString( "-1.00" ) );
	QCOMPARE( f4.evaluate( record1 ), QString( "+3.14" ) );

	QCOMPARE( f5.evaluate( record1 ), QString( "+0.00e+00" ) );
	QCOMPARE( f6.evaluate( record1 ), QString( "+1.00e+02" ) );
	QCOMPARE( f7.evaluate( record1 ), QString( "-1.00e+02" ) );
	QCOMPARE( f8.evaluate( record1 ), QString( "+3.14e+00" ) );
}


void TestSubstitutionField::formattedIntEvaluation()
{
	glabels::merge::SubstitutionField f1( "${1:%08d}" );
	glabels::merge::SubstitutionField f2( "${2:%08d}" );
	glabels::merge::SubstitutionField f3( "${3:%08d}" );
	glabels::merge::SubstitutionField f4( "${4:%08d}" );

	glabels::merge::SubstitutionField f5( "${5:%08x}" );
	glabels::merge::SubstitutionField f6( "${6:%08x}" );
	glabels::merge::SubstitutionField f7( "${7:%08x}" );
	glabels::merge::SubstitutionField f8( "${8:%08x}" );

	glabels::merge::Record record1;
	record1[ "1" ] = "0";
	record1[ "2" ] = "1";
	record1[ "3" ] = "-1";
	record1[ "4" ] = "3.14";

	record1[ "5" ] = "100";
	record1[ "6" ] = "0x100";
	record1[ "7" ] = "-1";
	record1[ "8" ] = "314";
	
	QCOMPARE( f1.evaluate( record1 ), QString( "00000000" ) );
	QCOMPARE( f2.evaluate( record1 ), QString( "00000001" ) );
	QCOMPARE( f3.evaluate( record1 ), QString( "-0000001" ) );
	QCOMPARE( f4.evaluate( record1 ), QString( "00000000" ) ); // Invalid integer value

	QCOMPARE( f5.evaluate( record1 ), QString( "00000064" ) ); // 100(decimal) == 64(hex)
	QCOMPARE( f6.evaluate( record1 ), QString( "00000100" ) );
	QCOMPARE( f7.evaluate( record1 ), QString( "00000000" ) ); // Invalid unsigned integer
	QCOMPARE( f8.evaluate( record1 ), QString( "0000013a" ) ); // 314(decimal) == 13a(hex)
}
