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

BUGS
----

To report a bug or make a suggestion regarding this application or this manual
page, you can use the issues section at Github:

<https://github.com/jimevins/glabels-qt/issues>

It is needed to register/sign in before. In case of you use another locale than
**en** on your system, it would be very helpful for developers if you set the
locale back to American English with the command ``export LC_ALL=C`` before
launching `glabels-qt`.

SEE ALSO
--------

:manpage:`glabels-batch-qt(1)`
	 
The gLabels homepage at <http://glabels.org/>.
