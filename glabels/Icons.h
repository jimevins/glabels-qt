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
				addFile( ":icons/24x24/actions/glabels-merge.png" );
			}
		};


		class ObjectProperties : public QIcon
		{
		public:
			ObjectProperties()
			{
				addPixmap( QPixmap( ":icons/24x24/actions/glabels-object-properties.svg" ) );
			}
		};


		class AlignLeft : public QIcon
		{
		public:
			AlignLeft()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-left.svg" ) );
			}
		};


		class AlignHCenter : public QIcon
		{
		public:
			AlignHCenter()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-hcenter.svg" ) );
			}
		};


		class AlignRight : public QIcon
		{
		public:
			AlignRight()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-right.svg" ) );
			}
		};


		class AlignBottom : public QIcon
		{
		public:
			AlignBottom()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-bottom.svg" ) );
			}
		};


		class AlignVCenter : public QIcon
		{
		public:
			AlignVCenter()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-vcenter.svg" ) );
			}
		};


		class AlignTop : public QIcon
		{
		public:
			AlignTop()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-align-top.svg" ) );
			}
		};


		class CenterHoriz : public QIcon
		{
		public:
			CenterHoriz()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-center-horiz.svg" ) );
			}
		};


		class CenterVert : public QIcon
		{
		public:
			CenterVert()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-center-vert.svg" ) );
			}
		};


		class FlipHoriz : public QIcon
		{
		public:
			FlipHoriz()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-flip-horiz.svg" ) );
			}
		};


		class FlipVert : public QIcon
		{
		public:
			FlipVert()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-flip-vert.svg" ) );
			}
		};


		class RotateLeft : public QIcon
		{
		public:
			RotateLeft()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-rotate-left.svg" ) );
			}
		};


		class RotateRight : public QIcon
		{
		public:
			RotateRight()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-rotate-right.svg" ) );
			}
		};


		class OrderBottom : public QIcon
		{
		public:
			OrderBottom()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-order-bottom.svg" ) );
			}
		};


		class OrderTop : public QIcon
		{
		public:
			OrderTop()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-order-top.svg" ) );
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
				addPixmap( QPixmap( ":icons/16x16/actions/edit-copy.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/edit-copy.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/edit-copy.svg" ) );
			}
		};


		class EditCut : public QIcon
		{
		public:
			EditCut()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/edit-cut.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/edit-cut.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/edit-cut.svg" ) );
			}
		};


		class EditPaste : public QIcon
		{
		public:
			EditPaste()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/edit-paste.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/edit-paste.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/edit-paste.svg" ) );
			}
		};


		class FileNew : public QIcon
		{
		public:
			FileNew()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/file-new.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/file-new.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/file-new.svg" ) );
			}
		};


		class FileOpen : public QIcon
		{
		public:
			FileOpen()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/file-open.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/file-open.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/file-open.svg" ) );
			}
		};


		class FilePrint : public QIcon
		{
		public:
			FilePrint()
			{
				addPixmap( QPixmap( ":icons/32x32/actions/print.svg" ) );
			}
		};


		class FileSave : public QIcon
		{
		public:
			FileSave()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/file-save.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/file-save.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/file-save.svg" ) );
			}
		};


		class FileSaveAs : public QIcon
		{
		public:
			FileSaveAs()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/file-save-as.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/file-save-as.svg" ) );
				addPixmap( QPixmap( ":icons/24x24/actions/file-save-as.svg" ) );
			}
		};


		class ZoomBestFit : public QIcon
		{
		public:
			ZoomBestFit()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-zoom-to-fit.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-zoom-to-fit.svg" ) );
			}
		};


		class ZoomIn : public QIcon
		{
		public:
			ZoomIn()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-zoom-in.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-zoom-in.svg" ) );
			}
		};


		class ZoomOriginal : public QIcon
		{
		public:
			ZoomOriginal()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-zoom-one-to-one.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-zoom-one-to-one.svg" ) );
			}
		};


		class ZoomOut : public QIcon
		{
		public:
			ZoomOut()
			{
				addPixmap( QPixmap( ":icons/16x16/actions/glabels-zoom-out.svg" ) );
				addPixmap( QPixmap( ":icons/22x22/actions/glabels-zoom-out.svg" ) );
			}
		};

	}

}


#endif // Icons_h
