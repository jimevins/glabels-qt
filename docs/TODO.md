To Do List for gLabels 4.0 -- 2019-10-07
========================================

Expose user variables to glabels-batch
--------------------------------------
There should be a way to set initial values of user variables from the glabels-batch
command line.  Possibly even create them on the fly.

Add programmable margin to text objects
---------------------------------------
The current built-in fixed margin seems to confuse people when dealing with
different horizontal and vertical alignments.

Improve print copies UI
-----------------------
As with previous versions of glabels, there should be a way of selecting
the number of sheets to print.  Merge printing should be able to be collated
or not, and if printing multiple copies, start on the same first label.

Printer calibration tool
------------------------
There desperately needs to be a printer calibration tool.  At a minimum
the tool should allow adjusting horizontal and vertical offsets.  The
adjustments should be unique to each printer.

I am thinking of a test page with a cross in the center.  It would have a
grid around this cross, indicating how much to adjust x & y.  The user
would fold the paper in quaters and use this grid to guestimate the offsets.

There should be warnings about how printers may drift from calibration or
even not have repeatable results.

* A more sophisticated tool, could adjust for scaling and skew, but it would
be very difficult to interact with the user on these.


Write help documentation
------------------------


Completed List for gLabels 4.0 -- 2018-04-15
============================================

Add "User Variables" feature
----------------------------

* Add page to MainWindow to
    - Define variables
    - Set their initial values
    - Control how they might increment (per item instance, per item copy, per page)

* Save as part of glabels project file


Add support for arbitrary label shapes
--------------------------------------

* I.e. similar to an SVG path.


Add support for "Continuous Roll" labels
----------------------------------------

* If product template is for a continuous roll, define a mininum and default length
    - This determines h and dy

* Add option to Properties page to adjust this value



To Do List for gLabels 4.1 -- 2019-03-17
========================================

Create a "built-in" merge source
--------------------------------
As an alternative to external merge sources, let the user edit the merge source
in situ.  The user can add fields.  The user can add records using those fields.
The user created database will become part of the glabels project file.
For simple databases, such as a small address list, this would be much easier
to deal with than creating it externally.
