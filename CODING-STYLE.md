Tabs vs. Spaces
---------------

Tabs are only used at the beginning of a line, and only used to express indentation level.  Spaces are used
for any other type of vertical alignment, e.g. aligning function arguments.  This ensures that the code
displays correctly everywhere, regardless of the viewer's tab size, and does not inflict the viewer with my
choice of tab size (8 spaces).

I use the emacs smart-tabs-mode to automatically enforce this.
See https://www.emacswiki.org/emacs/SmartTabs for more information.


Indentation Style
-----------------

Glabels code uses the Allman (a.k.a "BSD Style") of code indentation.  I.e. the brace associated with a
control statement is placed on the next line, indented to the same level as the control statement.
Statements within the braces are indented to the next level.

```
while ( condition )
{
	something();
	somethingElse();
}

if ( condition2 )
{
	handleCondition2();
}
else
{
	somethingElse();
}
```

See https://en.wikipedia.org/wiki/Indent_style#Allman_style for more information.
