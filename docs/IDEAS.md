Ideas
=====

This file is simply a collection of ideas for future capabilities of glabels.
The ideas may or may not be very well thought out -- it simply a scratchpad.


Merge Fields
------------

Currently substitution fields are specified simply by `${field-name}`. Here, I
am exploring ideas to extend this to be a richer substitution language.
Some of the criteria to consider are:

 - A rich formatting capability probably cannot be done through GUI controls alone.
 - It should be simple and easy to understand, but also powerful.
 - Is there an existing language that can be used in whole or in part.
 

## Format Control
It is desirable to control the format of the fields -- e.g. decimal, hex,
number of digits, leading zeros, fixed width, left or right justification,
etc.  Perhaps something like `${NAME:%-10s}`, i.e.
`${field-name:printf-style-format}`.


## Default Values
It would also be desirable to specify a default value.  (Or an initial value
in the event of a counter, see Label Counter below.)  Perhaps, something like
`${field-name:=value}`


## Possible Syntax
This is the first stab at a syntax specification.  It is roughly based on
the parameter substitution of the Bourne shell.

```
<field>     ::= "${" <field_name> [ ":" _modifiers_ ] "}"
<modifiers> ::= <modifier> [ ":" <modifiers> ]
<modifier>  ::= { "%" <format_spec> | "=" <value> }
```

Need a way to quote "`:`" in value.  Perhaps "`\:`" or maybe string values
should always be in quotes (you would still need to quote out quotes.


## Special Builtin Fields

### Label Counter

It would be nice if there was a label counter field.  Maybe something like
`${#}` or `${label#}`.  Also desirable would be the ability to set the start
value.  Possibly even reading it from a file and updating the file each time.
You would want to control if the value is repeated for copies or every copy
would be unique -- perhaps two different fields.  It would also be desirable to
control the format of the counter -- e.g. decimal, hex, number of digits, or
leading zeros.

### Date and Time Fields

Date and time fields would need to be able to be formatted much like strftime.


## Examples
Just some examples of the type of thing I am thinking.

```
${1}       /// CSV column 1
${addr1}   /// Field named "addr1"
${n:%09d}  /// Field named "n", format as 9 decimal digits with leading zeros
${MI:=NMI} /// Field named "MI", with default value of "NMI"
${#:%06d:=1000} /// Label counter, format as 6 decimal digits with leading zeros, starting at 1000
${#:%06d:<count.txt:>count.txt}  /// Perhaps a way to read and write the starting and ending value

```

