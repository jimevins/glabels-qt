/*  DataCache.cpp
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

#include "DataCache.h"

#include "LabelModelImageObject.h"


namespace glabels
{

	DataCache::DataCache()
	{
		// empty
	}


	DataCache::DataCache( const LabelModel* model )
	{
		foreach( LabelModelObject* object, model->objectList() )
		{
			if ( LabelModelImageObject* imageObject = dynamic_cast<LabelModelImageObject*>(object) )
			{
				TextNode filenameNode = imageObject->filenameNode();
				if ( !filenameNode.isField()  )
				{
					if ( const QImage* image = imageObject->image() )
					{
						addImage( filenameNode.data(), *imageObject->image() );
					}
					else
					{
						// TODO handle SVG files
					}
				}
			}
		}
	}


	bool DataCache::hasImage( const QString& name ) const
	{
		return mImageMap.contains( name );
	}


	QImage DataCache::getImage( const QString& name ) const
	{
		return mImageMap[ name ];
	}


	void DataCache::addImage( const QString& name, const QImage& image )
	{
		mImageMap[ name ] = image;
	}


	QList<QString> DataCache::imageNames() const
	{
		return mImageMap.keys();
	}

	
}
