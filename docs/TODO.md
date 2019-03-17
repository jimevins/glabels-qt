To Do List for gLabels 4.0 -- 2018-04-15
========================================

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


Write help documentation
------------------------


To Do List for gLabels 4.1 -- 2019-03-17
========================================

Create a "built-in" merge source
--------------------------------
As an alternative to external merge sources, let the user edit the merge source
in situ.  The user can add fields.  The user can add records using those fields.
The user created database will become part of the glabels project file.
For simple databases, such as a small address list, this would be much easier
to deal with than creating it externally.
