ft_od
=====

NAME 
   od - dump files in octal and other formats

SYNOPSIS
   od	[OPTION]... [FILE]...
   od	[-abcdfilosx]... [FILE]  [[+]OFFSET[.][b]]
   od	--traditional [OPTION]... [FILE] [[+]OFFSET[.][b] [+][LABEL][.][b]]

DESCRIPTION
   Write an unambiguous(not open to multiple meaning) representation, octal bytes by default, of FILE to STDOUT.
   *LABEL*
      LABEL is pseudo-address at first byte printed,
      That is incremented whem dump is progressing.
   - With more than one FILE arg, concatenate them in the listed order to form the input.
   - With no FILE, or when FILE is -, read standard input.

OPTIONS
   - ``-traditional``
      Accept arguments in third form above.
