glabels-batch-qt 1 "December 2018" glabels-batch-qt "User Manual"
=================================================================

# NAME
  glabels-batch-qt - gLabels Label Designer (Batch Front-end)

# SYNOPSIS
  glabels-qt [options] [files…]

# DESCRIPTION
  glabels-qt is the development version of the next major version of gLabels (4.0).  glabels-batch-qt is the batch front-end of glabels-qt.


# OPTIONS
  -p, --printer <printer>
    Send output to <printer>. (Default="")

  -o, --output <filename>
    Set output filename to <filename> (Default="output.pdf")

  -s, --sheets <n>
    Set number of sheets to <n> (Default=1).

  -c, --copies <n>
    Set number of copies to <n> (Default=1).

  -f, --first <n>
    Set starting label on 1st page to <n> (Default=1).

  -l, --outlines
    Print label outlines.

  -m, --crop-marks
    Print crop marks.

  -r, --reverse
    Print in reverse (mirror image).

  -h, --help
    Shows this help and exit.

  -v, --version
    Shows version information and exit.

Arguments:

  file
    gLabels project file to print.

# EXAMPLES

  To print 4 copies of my-business-card.glabels with crop marks on the USB printer lp0:

      glabels-batch-qt -m -p /dev/usb/lp0 ~/Documents/my-business-card.glabels

  To save a PDF of my-business-card.glabels at ~/Documents/businesscards.pdf:

      glabels-batch-qt -o ~/Documents/businesscards.pdf ~/Documents/my-business-card.glabels

  *Note:* Currently opening project files from older Glabels versions (3.x and older) isn't fully supported yet. Opening such a file could lead to unexpected behavior and data loss.

# SEE ALSO
  glabels-qt.conf(5), glabels-qt(1)

# AUTHORS
  Current maintainer: Jim Evins (https://github.com/jimevins)
