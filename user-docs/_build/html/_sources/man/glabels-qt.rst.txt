glabels-qt
==========

SYNOPSIS
--------

**glabels-qt** [*options*] [*filename* ...]

DESCRIPTION
-----------

:program:`glabels-qt` is a GUI program for designing and printing labels and
business cards.  It is designed to work with various laser/ink-jet peel-off
label and business card sheets that you’ll find at most office supply stores.

OPTIONS
-------

.. program:: glabels-qt

.. option::  -h, --help

	     Displays usage information and exits.

.. option::  -v, --version

             Displays version information and exits.

FILES
-----

.. describe:: ${prefix}/share/glabels-qt/templates/

	      Directory containing predefined product templates distributed with glabels.

.. describe:: ${XDG_CONFIG_HOME}/glabels.org/glabels-qt/

	      Directory containing user defined product templates created with the
	      gLabels Product Template Designer.  **Do not place manually created
	      templates here!**

.. describe:: ${HOME}/.glabels/

              Directory for manually created product templates.

REPORTING BUGS
--------------

Bugs and feature requests can be reported via the gLabels issue tracking system at GitHub (<https://github.com/jimevins/glabels-qt/issues>).  You will need a GitHub account to submit new issues or to comment on existing issues.


SEE ALSO
--------

:manpage:`glabels-batch-qt(1)`

The gLabels homepage at <http://glabels.org/>.
