Manually Creating Product Templates
===================================

This document is a reference for manually creating *gLabels* product templates.

*gLabels* searches for templates in several locations as described here:</p>


Location                                  | Description
------------------------------------------|-----------------------------------------
${prefix}/share/glabels-qt/templates/     | Predefined templates distributed with glabels.
${XDG_CONFIG_HOME}/glabels.org/glabels-qt | User defined templates created with the gLabels Product Template Designer. **Do not place manually created templates here!**
${HOME}/.glabels                          | Manually created templates should be placed here.



Assumptions/caveats
-------------------

A sheet contains only one size of label or card (if a sheet contains more than one size of item,
it can be split into multiple templates for multiple pass printing).


Template Files
--------------

A template file contains a single *Glabels-templates* top-level node.

```xml
<?xml version="1.0"?>
<Glabels-templates>

   ...one or more templates...

</Glabels-templates>
```

An example template file containing a single *Template* node:

```xml
<?xml version="1.0"?>
<Glabels-templates>

  <Template brand="Avery" part="8160" size="US-Letter" description="Mailing Labels">
    <Meta category="label"/>
    <Meta category="mail"/>
    <Label-rectangle id="0" width="189pt" height="72pt" round="5pt">
      <Markup-margin size="5pt"/>
      <Layout nx="3" ny="10" x0="11.25pt" y0="36pt" dx="200pt" dy="72pt"/>
    </Label-rectangle>
  </Template>

</Glabels-templates>
```

*Distance* Attributes
---------------------

A distance attribute is expressed as a number followed by a unit identifier.
Valid unit identifiers are *pt*, *in*, *mm*, *cm*, or *pc*.  These are a subset of
the SVG absolute length units.  Examples:

```xml
    <Label-round radius="1.0in" >
    <Label-round radius="2.54cm">
```

If no units are specified, computer points (*pt*) will be assumed (1 *pt* = 1/72 *in* = 0.352778 *mm*).


*Template* Node
---------------

A *Template* node describes a single stationery product.  It must contain exactly one instance of
a label node, either *Label-rectangle*, *Label-round*, *Label-ellipse* or *Label-cd*.

Property       | Type     | Description
---------------|----------|------------
*brand*        | string   | Brand or manufacturer of stationery product. E.g. "Avery".
*part*         | string   | Part number or name of stationery product. E.g. "8160".
*size*         | string   | Paper size.  Must match an ID defined in *paper-sizes.xml*, "roll" or "other".  E.g. "A4".
*description*  | string   | Description of stationery product.  E.g, "Mailing Labels".
*_description* | string   | Translatable description of stationery product. Used in predefined labels instead of description.
*width*        | distance | Page width. Only valid if `size="other"` or `size="roll"`.
*height*       | distance | Page height. Only valid if `size="other"`.  Value is ignored if `size="roll"`.
*equiv*        | string   | Equivalent part number.  If this property is present, the template is a clone of another template of the same brand.  The template will inherit all properties, except brand and name from the other template. This equiv property must refer to a previously defined template - *gLabels* does not currently support forward references.

### Guidelines for Creating Product Descriptions

If creating templates to be distributed with *gLabels*, please use the following guidelines.

* If possible, Reuse the description of a similar product
* Only capitalize the first word of description
* Keep descriptions general
* Do not repeat the part number or name in the description


*Meta* Node
-----------

A *Meta* node contains some additional information about the template. A *Template* node may contain zero
or more *Meta* nodes.  Only one property should be defined per *Meta* node.

Property       | Type     | Description
---------------|----------|------------
*category*     | string   | A category for the template. A template can belong to multiple categories by simply adding multiple *Meta* nodes to the parent *Template* node. The category must match an existing ID defined in categories.xml.  E.g. `category="media"`
*product_url*  | string   | A URL pointing to the vendor's webpage for the specific product, if available.


*Label-rectangle* Node
----------------------

A *Label-rectangle* node describes the dimensions of a single label or business card that is rectangular
in shape (may have rounded edges).

Property       | Type     | Description
---------------|----------|------------
*id*           | integer  | Reserved for future use.  Should always be 0.
*width*        | distance | Width of label or card. E.g. `width="29mm"`
*height*       | distance | Height of label or card. E.g. `height="100mm"`
*round*        | distance | Radius of corners.  For items with square edges (business cards), the radius should be 0.
*x_waste*      | distance | Amount of horizontal waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).
*y_waste*      | distance | Amount of vertical waste (over-print) to allow.

![Label-rectangle properties](images/glabels-template-rect-label.png)


*Label-ellipse* Node
--------------------

A *Label-ellipse* node describes the dimensions of a single label or business card that is elliptical
in shape.

Property       | Type     | Description
---------------|----------|------------
*id*           | integer  | Reserved for future use.  Should always be 0.
*width*        | distance | Width of label or card. E.g. `width="29mm"`
*height*       | distance | Height of label or card. E.g. `height="100mm"`
*waste*        | distance | Amount of waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).

![Label-ellipse properties](images/glabels-template-ellipse-label.png)


*Label-round* Node
------------------

A *Label-round* node describes the dimensions of a simple round label (not a CD).

Property       | Type     | Description
---------------|----------|------------
*id*           | integer  | Reserved for future use.  Should always be 0.
*radius*       | distance | Radius (1/2 diameter) of label or card. E.g. `radius="14.5mm"`
*waste*        | distance | Amount of waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).

![Label-round properties](images/glabels-template-round-label.png)


*Label-cd* Node
---------------

A *Label-cd* node describes the dimensions of a CD, DVD, or business card CD.

Property       | Type     | Description
---------------|----------|------------
*id*           | integer  | Reserved for future use.  Should always be 0.
*radius*       | distance | Outer radius (1/2 diameter) of label. E.g. `radius="58.5mm"`
*hole*         | distance | Radius (1/2 diameter) of concentric hole. E.g. `hole="18mm"`
*width*        | distance | If present, the label is clipped to the given Width. (For use with business card CDs.)
*height*       | distance | If present, the label is clipped to the given height. (For use with business card CDs.)
*waste*        | distance | Amount of waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).

![Label-cd properties](images/glabels-template-cd-label.png)

*Label-continuous* Node
-----------------------

A *Label-continuous* node describes the dimensions of a single section of a continuous label tape.

Property         | Type     | Description
-----------------|----------|------------
*id*             | integer  | Reserved for future use.  Should always be 0.
*width*          | distance | Width of label or card. E.g. `width="29mm"`
*min_height*     | distance | Minimum user defined height or length of label.
*max_height*     | distance | Maximum user defined height or length of label.
*default_height* | distance | Default user defined height or length of label.


*Label-path* Node
-----------------

A *Label-path* node describes the dimensions of a label with an outline defined by an arbitrary path.

Property       | Type     | Description
---------------|----------|------------
*id*           | integer  | Reserved for future use.  Should always be 0.
*d_units*      | string   | Units used in path definition.  Must be a supported distance unit identifier.  (default = `"pt"`)
*d*            | string   | Path definition.  This is a subset of of the SVG path "d" attribute.  Commands include "M/m", "L/l", "H/h", "V/v", and "Z/z".  Commands and data must be delimited by white space."
*x_waste*      | distance | Amount of horizontal waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).
*y_waste*      | distance | Amount of vertical waste (over-print) to allow.


*Markup* Nodes
--------------

Templates may contain optional markup nodes.  These nodes are used to describe
a simple set of markup lines that are visible in the *glabels* drawing canvas, but
not visible when printed.  These lines can represent margins, fold lines, center lines,
special areas, or other helpful hints to the user of a template.


### *Markup-margin* Node

A *Markup-margin* describes a margin along all edges of a label.

Property       | Type     | Description
---------------|----------|------------
*size*         | distance | Size of the margin.  I.e. the distance of the margin line from the edge of the card/label.
*x_size*       | distance | Size of the margin in x dimension.  I.e. the distance of the margin line from the edge of the card/label.
*y_size*       | distance | Size of the margin in y dimension.  I.e. the distance of the margin line from the edge of the card/label.


### *Markup-line* Node

A *Markup-line* node describes a markup line.

Property       | Type     | Description
---------------|----------|------------
*x1*           | distance | X coordinate of 1st endpoint of the line segment.
*y1*           | distance | Y coordinate of 1st endpoint of the line segment.
*x2*           | distance | X coordinate of 2nd endpoint of the line segment.
*y2*           | distance | Y coordinate of 2nd endpoint of the line segment.


### *Markup-circle* Node

A *Markup-circle* describes a markup circle.

Property       | Type     | Description
---------------|----------|------------
*x0*           | distance | X coordinate of circle origin (center).
*y0*           | distance | Y coordinate of circle origin (center).
*radius*       | distance | Radius of circle.


### *Markup-rect* Node

A *Markup-rect* describes a markup rectangle.

Property       | Type     | Description
---------------|----------|------------
*x1*           | distance | X coordinate of upper left corner of rectangle.
*y1*           | distance | Y coordinate of upper left corner of rectangle.
*w*            | distance | Width of rectangle.
*h*            | distance | Height of rectangle.
*r*            | distance | Radius of rounded corners of rectangle.


### *Markup-ellipse* Node

A *Markup-ellipse* describes a markup ellipse.

Property       | Type     | Description
---------------|----------|------------
*x1*           | distance | X coordinate of upper left corner of ellipse bounding box.
*y1*           | distance | Y coordinate of upper left corner of ellipse bounding box.
*w*            | distance | Width of ellipse.
*h*            | distance | Height of ellipse.


*Layout* Node
-------------

A label node may contain multiple *Layout* children.  If labels are arranged in a simple grid pattern, only
one layout is needed.  However, if labels are arranged in multiple grids, such as a running bond pattern,
multiple *Layout* tags can be used.

A common example for multiple layouts is a sheet with three CD labels:

![CD Label layout example](images/layouts-cdlabel.png)

The two labels on the left edge can be assigned to a grid, assuming we
can define the coordinates for the top left label and the distance to
the second label properly. The distance to the left edge is common to
these labels. The third one on the right edge has no common distance
values with the other ones, that's why we have to define a second layout,
with unique coordinates for the top left corner of that label.

> You can define multiple layouts only if the labels on the sheet
> have the same shape. If your sheet contains different shapes, you have
> to define each shape in another template separately. Future versions
> of <app>gLabels</app> will probably be able to concatenate such sheets
> with different shapes within a single template.</p>

> A single label can always be treated as a grid of one.

Property       | Type     | Description
---------------|----------|------------
*nx*           | integer  | Number of labels/cards in the grid in the X direction (horizontal).
*ny*           | integer  | Number of labels/cards in the grid in the Y direction (vertical).
*x0*           | distance | Distance from left edge of sheet to the left edge of the left column of cards/labels in the layout.
*y0*           | distance | Distance from the top edge of sheet to the top edge of the top row of labels/cards in the layout.
*dx*           | distance | Horizontal pitch of grid.
*dy*           | distance | Vertical pitch of grid.

![Layout example](images/glabels-template-layout.png)
