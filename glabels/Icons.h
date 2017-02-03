/*  Icons.h
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

#ifndef Icons_h
#define Icons_h


#include <QIcon>


namespace glabels
{

	///
	/// Glabels Icons
	///
	namespace Icons
	{

		class Arrow : public QIcon
		{
		public:
			Arrow()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-arrow.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-arrow.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-arrow.svg" ) );
			}
		};


		class Barcode : public QIcon
		{
		public:
			Barcode()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-barcode.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-barcode.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-barcode.svg" ) );
			}
		};


		class Box : public QIcon
		{
		public:
			Box()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-box.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-box.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-box.svg" ) );
			}
		};


		class Ellipse : public QIcon
		{
		public:
			Ellipse()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-ellipse.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-ellipse.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-ellipse.svg" ) );
			}
		};


		class Image : public QIcon
		{
		public:
			Image()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-image.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-image.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-image.svg" ) );
			}
		};


		class Line : public QIcon
		{
		public:
			Line()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-line.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-line.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-line.svg" ) );
			}
		};


		class Text : public QIcon
		{
		public:
			Text()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-text.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-text.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-text.svg" ) );
			}
		};


		class Merge : public QIcon
		{
		public:
			Merge()
			{
				addFile( ":icons/16x16/actions/glabels-merge.png" );
				addFile( ":icons/24x24/actions/glabels-merge.png" );
			}
		};


		class ObjectProperties : public QIcon
		{
		public:
			ObjectProperties()
			{
				addFile( ":icons/16x16/actions/glabels-object-properties.png" );
				addFile( ":icons/24x24/actions/glabels-object-properties.png" );
			}
		};


		class AlignLeft : public QIcon
		{
		public:
			AlignLeft()
			{
				addFile( ":icons/16x16/actions/glabels-align-left.png" );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-align-left.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-align-left.svg" ) );
			}
		};


		class AlignHCenter : public QIcon
		{
		public:
			AlignHCenter()
			{
				addFile( ":icons/16x16/actions/glabels-align-hcenter.png" );
			}
		};


		class AlignRight : public QIcon
		{
		public:
			AlignRight()
			{
				addFile( ":icons/16x16/actions/glabels-align-right.png" );
			}
		};


		class AlignBottom : public QIcon
		{
		public:
			AlignBottom()
			{
				addFile( ":icons/16x16/actions/glabels-align-bottom.png" );
			}
		};


		class AlignVCenter : public QIcon
		{
		public:
			AlignVCenter()
			{
				addFile( ":icons/16x16/actions/glabels-align-vcenter.png" );
			}
		};


		class AlignTop : public QIcon
		{
		public:
			AlignTop()
			{
				addFile( ":icons/16x16/actions/glabels-align-top.png" );
			}
		};


		class CenterHoriz : public QIcon
		{
		public:
			CenterHoriz()
			{
				addFile( ":icons/16x16/actions/glabels-center-horiz.png" );
			}
		};


		class CenterVert : public QIcon
		{
		public:
			CenterVert()
			{
				addFile( ":icons/16x16/actions/glabels-center-vert.png" );
			}
		};


		class FlipHoriz : public QIcon
		{
		public:
			FlipHoriz()
			{
				addFile( ":icons/16x16/actions/glabels-flip-horiz.png" );
			}
		};


		class FlipVert : public QIcon
		{
		public:
			FlipVert()
			{
				addFile( ":icons/16x16/actions/glabels-flip-vert.png" );
			}
		};


		class RotateLeft : public QIcon
		{
		public:
			RotateLeft()
			{
				addFile( ":icons/16x16/actions/glabels-rotate-left.png" );
			}
		};


		class RotateRight : public QIcon
		{
		public:
			RotateRight()
			{
				addFile( ":icons/16x16/actions/glabels-rotate-right.png" );
			}
		};


		class OrderBottom : public QIcon
		{
		public:
			OrderBottom()
			{
				addFile( ":icons/16x16/actions/glabels-order-bottom.png" );
			}
		};


		class OrderTop : public QIcon
		{
		public:
			OrderTop()
			{
				addFile( ":icons/16x16/actions/glabels-order-top.png" );
			}
		};


		class AlignTextLeft : public QIcon
		{
		public:
			AlignTextLeft()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-align-text-left.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-align-text-left.svg" ) );
			}
		};


		class AlignTextCenter : public QIcon
		{
		public:
			AlignTextCenter()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-align-text-center.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-align-text-center.svg" ) );
			}
		};


		class AlignTextRight : public QIcon
		{
		public:
			AlignTextRight()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-align-text-right.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-align-text-right.svg" ) );
			}
		};


		class AlignTextBottom : public QIcon
		{
		public:
			AlignTextBottom()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-valign-text-bottom.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-valign-text-bottom.svg" ) );
			}
		};


		class AlignTextMiddle : public QIcon
		{
		public:
			AlignTextMiddle()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-valign-text-middle.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-valign-text-middle.svg" ) );
			}
		};


		class AlignTextTop : public QIcon
		{
		public:
			AlignTextTop()
			{
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-valign-text-top.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-valign-text-top.svg" ) );
			}
		};


		class BucketFill : public QIcon
		{
		public:
			BucketFill()
			{
				addFile( ":icons/16x16/actions/glabels-bucket-fill.png" );
				addFile( ":icons/24x24/actions/glabels-bucket-fill.png" );
			}
		};


		class Pencil : public QIcon
		{
		public:
			Pencil()
			{
				addFile( ":icons/16x16/actions/glabels-pencil.png" );
				addFile( ":icons/24x24/actions/glabels-pencil.png" );
			}
		};


		class Glabels : public QIcon
		{
		public:
			Glabels()
			{
				addFile( ":icons/16x16/apps/glabels.png" );
				addFile( ":icons/24x24/apps/glabels.png" );
				addFile( ":icons/32x32/apps/glabels.png" );
				addFile( ":icons/48x48/apps/glabels.png" );
				addFile( ":icons/scalable/apps/glabels.svg" );
			}
		};


		class EditCopy : public QIcon
		{
		public:
			EditCopy()
			{
				addFile( ":icons/24x24/actions/edit-copy.png" );
			}
		};


		class EditCut : public QIcon
		{
		public:
			EditCut()
			{
				addFile( ":icons/24x24/actions/edit-cut.png" );
			}
		};


		class EditPaste : public QIcon
		{
		public:
			EditPaste()
			{
				addFile( ":icons/24x24/actions/edit-paste.png" );
			}
		};


		class FileNew : public QIcon
		{
		public:
			FileNew()
			{
				addFile( ":icons/24x24/actions/file-new.png" );
			}
		};


		class FileOpen : public QIcon
		{
		public:
			FileOpen()
			{
				addFile( ":icons/24x24/actions/file-open.png" );
			}
		};


		class FilePrint : public QIcon
		{
		public:
			FilePrint()
			{
				addFile( ":icons/24x24/actions/file-print.png" );
				addFile( ":icons/32x32/actions/file-print.png" );
			}
		};


		class FileSave : public QIcon
		{
		public:
			FileSave()
			{
				addFile( ":icons/24x24/actions/file-save.png" );
			}
		};


		class FileSaveAs : public QIcon
		{
		public:
			FileSaveAs()
			{
				addFile( ":icons/24x24/actions/file-save-as.png" );
			}
		};


		class ZoomBestFit : public QIcon
		{
		public:
			ZoomBestFit()
			{
				addFile( ":icons/24x24/actions/zoom-best-fit.png" );
			}
		};


		class ZoomIn : public QIcon
		{
		public:
			ZoomIn()
			{
				addFile( ":icons/24x24/actions/zoom-in.png" );
			}
		};


		class ZoomOriginal : public QIcon
		{
		public:
			ZoomOriginal()
			{
				addFile( ":icons/24x24/actions/zoom-original.png" );
			}
		};


		class ZoomOut : public QIcon
		{
		public:
			ZoomOut()
			{
				addFile( ":icons/24x24/actions/zoom-out.png" );
			}
		};

	}

}


#endif // Icons_h
