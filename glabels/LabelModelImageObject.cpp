/*  LabelModelImageObject.cpp
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

#include "LabelModelImageObject.h"

#include "Size.h"
#include <QBrush>
#include <QPen>
#include <QImage>
#include <QFileInfo>
#include <QtDebug>


namespace
{
}


///
/// Static data
///
QImage* LabelModelImageObject::smDefaultImage = 0;


///
/// Constructor
///
LabelModelImageObject::LabelModelImageObject() : mImage(0), mSvg(0)
{
	mOutline = new Outline( this );

	mHandles << new HandleNorthWest( this );
	mHandles << new HandleNorth( this );
	mHandles << new HandleNorthEast( this );
	mHandles << new HandleEast( this );
	mHandles << new HandleSouthEast( this );
	mHandles << new HandleSouth( this );
	mHandles << new HandleSouthWest( this );
	mHandles << new HandleWest( this );

	if ( smDefaultImage == 0 )
	{
		smDefaultImage = new QImage( ":images/checkerboard.png" );
	}
}


///
/// Copy constructor
///
LabelModelImageObject::LabelModelImageObject( const LabelModelImageObject* object ) : LabelModelObject(object)
{
	mFilenameNode = object->mFilenameNode;
}


///
/// Destructor
///
LabelModelImageObject::~LabelModelImageObject()
{
	delete mOutline;

	foreach( Handle* handle, mHandles )
	{
		delete handle;
	}
	mHandles.clear();
}


///
/// Clone
///
LabelModelImageObject* LabelModelImageObject::clone() const
{
	return new LabelModelImageObject( this );
}


///
/// Image filenameNode Property Getter
///
TextNode LabelModelImageObject::filenameNode( void ) const
{
	return mFilenameNode;
}


///
/// Image filenameNode Property Setter
///
void LabelModelImageObject::setFilenameNode( const TextNode& value )
{
	if ( mFilenameNode != value )
	{
		mFilenameNode = value;
		loadImage();
		
		emit changed();
	}
}


///
/// Image originalSize Property Getter (assumes 72 DPI, i.e. 1pixel == 1pt)
///
Size LabelModelImageObject::originalSize() const
{
	Size size( glabels::Distance::pt(72), glabels::Distance::pt(72) );

	if ( mImage )
	{
		QSize qsize = mImage->size();
		size.setW( glabels::Distance::pt( qsize.width() ) );
		size.setH( glabels::Distance::pt( qsize.height() ) );
	}
	else if ( mSvg )
	{
		QSize qsize = mSvg->defaultSize();
		size.setW( glabels::Distance::pt( qsize.width() ) );
		size.setH( glabels::Distance::pt( qsize.height() ) );
	}

	return size;
}


///
/// Draw shadow of object
///
void LabelModelImageObject::drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const
{
	QRectF destRect( 0, 0, mW.pt(), mH.pt() );
	
	QColor shadowColor = mShadowColorNode.color( record );
	shadowColor.setAlphaF( mShadowOpacity );

	if ( mImage && mImage->hasAlphaChannel() && (mImage->depth() == 32) )
	{
		QImage* shadowImage = createShadowImage( shadowColor );
		painter->drawImage( destRect, *shadowImage );
		delete shadowImage;
	}
	else
	{
		if ( mImage || inEditor )
		{
			painter->setBrush( shadowColor );
			painter->setPen( QPen( Qt::NoPen ) );

			painter->drawRect( destRect );
		}
	}
}

	
///
/// Draw object itself
///
void LabelModelImageObject::drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const
{
	QRectF destRect( 0, 0, mW.pt(), mH.pt() );
	
	if ( inEditor && (mFilenameNode.isField() || (!mImage && !mSvg) ) )
	{
		painter->save();
		painter->setRenderHint( QPainter::SmoothPixmapTransform, false );
		painter->drawImage( destRect, *smDefaultImage );
		painter->restore();
	}
	else if ( mImage )
	{
		painter->drawImage( destRect, *mImage );
	}
	else if ( mSvg )
	{
		mSvg->render( painter, destRect );
	}
	else if ( mFilenameNode.isField() )
	{
		// TODO
	}
}


///
/// Path to test for hover condition
///
QPainterPath LabelModelImageObject::hoverPath( double scale ) const
{
	QPainterPath path;
	path.addRect( 0, 0, mW.pt(), mH.pt() );

	return path;
}


///
/// Load image
///
void LabelModelImageObject::loadImage()
{
	if ( mImage )
	{
		delete mImage;
	}
	if ( mSvg )
	{
		delete mSvg;
	}

	if ( mFilenameNode.isField() )
	{
		mImage = 0;
		mSvg = 0;
	}
	else
	{
		QString filename = mFilenameNode.data();
		QFileInfo fileInfo( filename );

		if ( fileInfo.isReadable() )
		{
			if ( (fileInfo.suffix() == "svg") || (fileInfo.suffix() == "SVG") )
			{
				mSvg = new QSvgRenderer( filename );
				if ( !mSvg->isValid() )
				{
					mSvg = 0;
				}
				else
				{
					// Adjust size based on aspect ratio of SVG image
					QRectF rect = mSvg->viewBoxF();
					double aspectRatio = rect.height() / rect.width();
					if ( mH > mW*aspectRatio )
					{
						mH = mW*aspectRatio;
					}
					else
					{
						mW = mH/aspectRatio;
					}
				}
			}
			else
			{
				mImage = new QImage( filename );
				if ( mImage->isNull() )
				{
					mImage = 0;
				}
				else
				{
					// Adjust size based on aspect ratio of image
					double imageW = mImage->width();
					double imageH = mImage->height();
					double aspectRatio = imageH / imageW;
					if ( mH > mW*aspectRatio )
					{
						mH = mW*aspectRatio;
					}
					else
					{
						mW = mH/aspectRatio;
					}
				}
			}
		}
	}
}


///
/// Create shadow image
///
QImage* LabelModelImageObject::createShadowImage( const QColor& color ) const
{
	int r = color.red();
	int g = color.green();
	int b = color.blue();
	int a = color.alpha();
		
	QImage* shadow = new QImage( *mImage );
	for ( int iy = 0; iy < shadow->height(); iy++ )
	{
		QRgb* scanLine = (QRgb*)shadow->scanLine( iy );
		
		for ( int ix = 0; ix < shadow->width(); ix++ )
		{
			scanLine[ix] = qRgba( r, g, b, (a*qAlpha(scanLine[ix]))/255 );
		}
	}

	return shadow;
}
