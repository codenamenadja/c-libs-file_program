sort
====

Write sorted concatenation of all FILE(s) *to standard output.*
With no FILE or file is -, *read standard input.*

Synopsis
--------

   sort [OPTION]... [FILE] [FILE2]

make
----

- ``all``       : compile c file and creates binary *ft_sort*
- ``clean``     : clean object-files only.
- ``fclean``    : clean main target file also.

Constraints
-----------

Options
^^^^^^^

General

   - ``--output=<FILENAME>``		: write output to FILENAME instead of STDOUT.
   - ``--buffer-size=<SIZE>``		: use SIZE for main memory buffer.

Ordering

   - ``--dictionary-order``			: consider only blanks and alphanumeric charcters.
   - ``--reverse``					: show in reverse.
   - ``--numeric-sort``				: comparing according to string numerical value.
   - ``--generial-numeric-sort``	: compare according to general numerical value.

Filtering

   - ``--unique``					: ignore, multiple occurence.
   - ``--ignore-case``
   - ``--ignore-nonprinting``
   - ``--ignore-leading-blanks``

Arguments
^^^^^^^^^

- Max file can have two files, sort and merge to output.
- Error messages have to be displayed on their reserved output followed by a new line.
- If no argument is given, it should display File name missing.
- If there is more than one argument, it should display Too many arguments.

Error
^^^^^

- If the file cannot read, it should display *cannot read file.*


Workflow
--------

1. read all the lines of input.
#. sort them.
#. print them in order.
