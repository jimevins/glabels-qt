Manually Creating Product Templates
===================================

This document is a reference for manually creating *gLabels* product templates.

*gLabels* searches for templates in several locations as described here:</p>


Location                                 | Description
-----------------------------------------|-----------------------------------------
${prefix}/share/libglabels-qt/templates/ | Predefined templates distributed with glabels.
${XDG_CONFIG_HOME}/libglabels/templates  | User defined templates created with the gLabels Template Designer.
${HOME}/.glabels                         | Manually created templates should be placed here.



Assumptions/caveats
-------------------

A sheet contains only one size of label or card (if a sheet contains more than one size of item,
it can be split into multiple templates for multiple pass printing).

Distances can be expressed in units of *pt*, *in1*, *mm*, *cm*, or *pc*.  For example:
`"1.0in"` or `"2.54cm"`.  If no units are specified, computer points (*pt*) will
be assumed (1 *pt* = 1/72 *in* = 0.352778 *mm*).


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

*Template* Node
---------------

A *Template* node describes a single stationery product.  It must contain exactly one instance of
a label node, either *Label-rectangle*, *Label-round*, *Label-ellipse* or *Label-cd*.

Property       | Description
---------------|------------
*brand*        | Brand or manufacturer of stationery product. E.g. "Avery".
*part*         | Part number or name of stationery product. E.g. "8160".
*size*         | Paper size.  Must match an ID defined in *paper-sizes.xml* or "Other".  E.g. "A4".
*description*  | Description of stationery product.  E.g, "Mailing Labels".
*_description* | Translatable description of stationery product. Used in predefined labels instead of description.
*width*        | Page width. Only valid if `size="Other"`.
*height*       | Page height. Only valid if `size="Other"`.
*equiv*        | Equivalent part number.  If this property is present, the template is a clone of another template of the same brand.  The template will inherit all properties, except brand and name from the other template. This equiv property must refer to a previously defined template - *gLabels* does not currently support forward references.

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

Property      | Description
--------------|------------
*category*    | A category for the template. A template can belong to multiple categories by simply adding multiple *Meta* nodes to the parent *Template* node. The category must match an existing ID defined in categories.xml.  E.g. `category="media"`
*product_url* | A URL pointing to the vendor's webpage for the specific product, if available.


*Label-rectangle* Node
----------------------

A *Label-rectangle* node describes the dimensions of a single label or business card that is rectangular
in shape (may have rounded edges).

Property      | Description
--------------|------------
*id*          | Reserved for future use.  Should always be 0.
*width*       | Width of label or card. E.g. `width="29mm"`
*height*      | Height of label or card. E.g. `height="100mm"`
*round*       | Radius of corners.  For items with square edges (business cards), the radius should be 0.
*x_waste*     | Amount of horizontal waste (over-print) to allow.  This is useful for minimizing alignment problems when using non-white backgrounds (e.g. images).
*y_waste*     | Amount of vertical waste (over-print) to allow.

![Label-rectangle properties](images/glabels-template-rect-label.png)


  <!-- ************************ -->
  <!-- BEGIN Label-ellipse Node -->
  <!-- ************************ -->
  <section id="template-label-ellipse-node">
    <title>*Label-ellipse* Node</title>

    <p>A *Label-ellipse* node describes the
      dimensions of a single label or business card that is elliptic
      in shape.</p>

    <table frame="all" rules="rows">
      <tr>
        <td><p>Property</p></td>  <td><p>Description</p></td>
      </tr>
      <tr>
        <td><p></p></td>  <td><p></p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*id*</p></td>
        <td><p>Reserved for future use.  Should always be 0.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*width*</p></td>
        <td><p>Width of the ellipse</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*height*</p></td>
        <td><p>Height of the ellipse</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*waste*</p></td>
        <td><p>Amount of waste (over-print) to allow.  This is useful
            for minimizing alignment problems when using non-white
            backgrounds (e.g. images).</p></td>
      </tr>
    </table>

    <!-- ==== Figure ==== -->
    <figure>
      <desc><span>Label-ellipse</span> parameters</desc>
      <media type="image" src="figures/glabels-template-ellipse-label.png" mime="image/png" style="right">
        <p>*Label-ellipse* parameters</p>
      </media>
    </figure>
    <!-- ==== End of Figure ==== -->

  </section>
  <!-- ************************ -->
  <!-- END Label-ellipse Node   -->
  <!-- ************************ -->


  <!-- ********************** -->
  <!-- BEGIN Label-round Node -->
  <!-- ********************** -->
  <section id="template-label-round-node">
    <title>*Label-round* Node</title>

    <p>A *Label-round* node describes the dimensions
      of a simple round label (not a CD).</p>

    <table frame="all" rules="rows">
      <tr>
        <td><p>Property</p></td>  <td><p>Description</p></td>
      </tr>
      <tr>
        <td><p></p></td>  <td><p></p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*id*</p></td>
        <td><p>Reserved for future use.  Should always be 0.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*radius*</p></td>
        <td><p>Radius (1/2 diameter) of label</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*waste*</p></td>
        <td><p>Amount of waste (over-print) to allow.  This is useful
                for minimizing alignment problems when using non-white
                backgrounds (e.g. images).</p></td>
      </tr>
    </table>

    <!-- ==== Figure ==== -->
    <figure>
      <desc>*Label-ellipse* parameters</desc>
      <media its:translate="no" type="image" src="figures/glabels-template-circle-label.png" mime="image/png" style="right">
        <p>*Label-ellipse* parameters</p>
      </media>
    </figure>
    <!-- ==== End of Figure ==== -->

  </section>
  <!-- ********************** -->
  <!-- END Label-round Node   -->
  <!-- ********************** -->


  <!-- ******************* -->
  <!-- BEGIN Label-cd Node -->
  <!-- ******************* -->
  <section id="template-label-cd-node">
    <title>*Label-cd* Node</title>

    <p>A *Label-cd* node describes the dimensions
      of a CD, DVD, or business card CD.</p>

    <table frame="all" rules="rows">
      <tr>
        <td><p>Property</p></td>  <td><p>Description</p></td>
      </tr>
      <tr>
        <td><p></p></td>  <td><p></p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*id*</p></td>
        <td><p>Reserved for future use.  Should always be 0.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*radius*</p></td>
        <td><p>Outer radius of label</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*hole*</p></td>
        <td><p>Radius of concentric hole</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*width*</p></td>
        <td><p>If present, the label is clipped to the given width.
                      (Useful for "business card CDs").</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*height*</p></td>
        <td><p>If present, the label is clipped to the given height.
                      (Useful for "business card CDs").</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*waste*</p></td>
        <td><p>Amount of waste (over-print) to allow.  This is useful
                      for minimizing alignment problems when using non-white
                      backgrounds (e.g. images).</p></td>
      </tr>
    </table>

    <!-- ==== Figure ==== -->
    <figure>
      <desc>*Label-cd* parameters</desc>
      <media its:translate="no" type="image" src="figures/glabels-template-cd-label.png" mime="image/png" style="right">
        <p>CD label parameters</p>
      </media>
    </figure>
    <!-- ==== End of Figure ==== -->

  </section>
  <!-- ******************* -->
  <!-- END Label-cd Node   -->
  <!-- ******************* -->


  <!-- ***************** -->
  <!-- BEGIN Markup Node -->
  <!-- ***************** -->
  <section id="template-markup">
    <title>*Markup* Nodes</title>

    <p>Templates may contain optional markup nodes.  These nodes are used to describe
    a simple set of markup lines that are visible in the <app>glabels</app> drawing canvas, but
    not visible when printed.  These lines can represent margins, fold lines, center lines,
    special areas, or other helpful hints to the user of a template.</p>


    <!-- ======================== -->
    <!-- BEGIN Markup-margin Node -->
    <!-- ======================== -->
    <section id="template-markup-margin-node">
      <title>*Markup-margin* Node</title>

      <p>A *Markup-margin* describes a margin along
      all edges of a label.</p>

      <table frame="all" rules="rows">
        <tr>
          <td><p>Property</p></td>  <td><p>Description</p></td>
        </tr>
        <tr>
          <td><p></p></td>  <td><p></p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*size*</p></td>
          <td><p>Size of the margin.  I.e. the distance of the margin
                        line from the edge of the card/label.</p></td>
        </tr>
      </table>
    </section>
    <!-- ======================== -->
    <!-- END Markup-margin Node   -->
    <!-- ======================== -->


    <!-- ====================== -->
    <!-- BEGIN Markup-line Node -->
    <!-- ====================== -->
    <section id="template-markup-line-node">
      <title>*Markup-line* Node</title>

      <p>A *Markup-line* node describes a markup line.</p>

      <table frame="all" rules="rows">
        <tr>
          <td><p>Property</p></td>  <td><p>Description</p></td>
        </tr>
        <tr>
          <td><p></p></td>  <td><p></p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*x1*</p></td>
          <td><p>x coordinate of 1st endpoint of the line segment.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*y1*</p></td>
          <td><p>y coordinate of 1st endpoint of the line segment.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*x2*</p></td>
          <td><p>x coordinate of 2nd endpoint of the line segment.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*y2*</p></td>
          <td><p>y coordinate of 2nd endpoint of the line segment.</p></td>
        </tr>
      </table>
    </section>
    <!-- ====================== -->
    <!-- END Markup-line Node   -->
    <!-- ====================== -->


    <!-- ======================== -->
    <!-- BEGIN Markup-circle Node -->
    <!-- ======================== -->
    <section id="template-markup-circle-node">
      <title>*Markup-circle* Node</title>

      <p>A *Markup-circle* describes a markup circle.</p>

      <table frame="all" rules="rows">
        <tr>
          <td><p>Property</p></td>  <td><p>Description</p></td>
        </tr>
        <tr>
          <td><p></p></td>  <td><p></p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*x0*</p></td>
          <td><p>x coordinate of circle origin (center).</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*y0*</p></td>
          <td><p>y coordinate of circle origin (center).</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*radius*</p></td>
          <td><p>Radius of circle.</p></td>
        </tr>
      </table>
    </section>
    <!-- ======================== -->
    <!-- END Markup-circle Node   -->
    <!-- ======================== -->


    <!-- ====================== -->
    <!-- BEGIN Markup-rect Node -->
    <!-- ====================== -->
    <section id="template-markup-rect-node">
      <title>*Markup-rect* Node</title>

      <p>A *Markup-rect* describes a markup rectangle.</p>

      <table frame="all" rules="rows">
        <tr>
          <td><p>Property</p></td>  <td><p>Description</p></td>
        </tr>
        <tr>
          <td><p></p></td>  <td><p></p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*x1*</p></td>
          <td><p>x coordinate of upper left corner of rectangle.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*y1*</p></td>
          <td><p>y coordinate of upper left corner of rectangle.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*w*</p></td>
          <td><p>Width of rectangle.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*h*</p></td>
          <td><p>Height of rectangle.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*r*</p></td>
          <td><p>Radius of rounded corners of rectangle.</p></td>
        </tr>
      </table>
    </section>
    <!-- ====================== -->
    <!-- END Markup-rect Node   -->
    <!-- ====================== -->


    <!-- ========================= -->
    <!-- BEGIN Markup-ellipse Node -->
    <!-- ========================= -->
    <section id="template-markup-ellipse-node">
      <title>*Markup-ellipse* Node</title>

      <p>A *Markup-ellipse* describes a markup ellipse.</p>

      <table frame="all" rules="rows">
        <tr>
          <td><p>Property</p></td>  <td><p>Description</p></td>
        </tr>
        <tr>
          <td><p></p></td>  <td><p></p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*x1*</p></td>
          <td><p>x coordinate of upper left corner of ellipse.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*y1*</p></td>
          <td><p>y coordinate of upper left corner of ellipse.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*w*</p></td>
          <td><p>Width of ellipse.</p></td>
        </tr>
        <tr>
          <td its:translate="no"><p>*h*</p></td>
          <td><p>Height of ellipse.</p></td>
        </tr>
      </table>
    </section>
    <!-- ========================= -->
    <!-- END Markup-ellipse Node   -->
    <!-- ========================= -->

  </section>
  <!-- ***************** -->
  <!-- END Markup Node   -->
  <!-- ***************** -->


  <!-- ***************** -->
  <!-- BEGIN Layout Node -->
  <!-- ***************** -->
  <section id="template-layout-node">
    <title>*Layout* Node</title>

    <p>A label node may contain multiple *Layout*
      children.  If labels are arranged in a simple grid pattern, only
      one layout is needed.  However, if labels are arranged in multiple
      grids, such as a running bond pattern, multiple
      *Layout* tags can be used.</p>
    <p>A common example for multiple layouts is a sheet with three
       CD labels:</p>

    <!-- ==== Figure ==== -->
    <figure>
      <desc>CD label sheet</desc>
      <media its:translate="no" type="image" src="figures/layouts-cdlabel.png" mime="image/png" style="right">
        <p>CD label sheet</p>
      </media>
    </figure>
    <!-- ==== End of Figure ==== -->

    <p>The two labels on the left edge can be assigned to a grid, assuming we
       can define the coordinates for the top left label and the distance to
       the second label properly. The distance to the left edge is common to
       these labels. The third one on the right edge has no common distance
       values with the other ones, that's why we have to define a second layout,
       with unique coordinates for the top left corner of that label.</p>

	<note style="tip">
	<p>You can define multiple layouts only if the labels on the sheet
        have the same shape. If your sheet contains different shapes, you have
        to define each shape in another template separately. Future versions
        of <app>gLabels</app> will probably be able to concatenate such sheets
        with different shapes within a single template.</p>
      </note>

	<note style="tip">
	<p>A single label can always be treated as a grid of one.</p>
      </note>

    <table frame="all" rules="rows">
      <tr>
        <td><p>Property</p></td>  <td><p>Description</p></td>
      </tr>
      <tr>
        <td><p></p></td>  <td><p></p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*nx*</p></td>
        <td><p>Number of labels/cards across in the grid (horizontal)</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*ny*</p></td>
        <td><p>Number of labels/cards across in the grid (vertical)</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*x0*</p></td>
        <td><p>Distance from left edge of sheet to the left edge of
            the left column of cards/labels in the layout.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*y0*</p></td>
        <td><p>Distance from the top edge of sheet to the top edge of
             the top row of labels/cards in the layout.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*dx*</p></td>
        <td><p>Horizontal pitch of grid.</p></td>
      </tr>
      <tr>
        <td its:translate="no"><p>*dy*</p></td>
        <td><p>Vertical pitch of grid.</p></td>
      </tr>
    </table>

    <!-- ==== Figure ==== -->
    <figure>
      <desc>*Layout* parameters</desc>
      <media its:translate="no" type="image" src="figures/glabels-template-layout.png" mime="image/png" style="right">
        <p><span>Layout</span> Parameters</p>
      </media>
    </figure>
    <!-- ==== End of Figure ==== -->

  </section>
  <!-- ***************** -->
  <!-- END Layout Node   -->
  <!-- ***************** -->


</page>







