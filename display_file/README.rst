display_file
============

ft_display_file program displays on the STDOUT, only the content of the file given as argument.

make
----

- ``all``       : compile c file and creates binary *ft_display_file.*
- ``clean``     : clean object-files only.
- ``fclean``    : clean main target file also.

Constraints
-----------


Arguments
^^^^^^^^^

- All files given as arguments validation test should occur.
- Error messages have to be displayed on their reserved output followed by a new line.
- If no argument is given, it should display File name missing.
- (deprecated) If there is more than one argument, it should display Too many arguments.

Error
^^^^^

- If the file cannot read, it should display *cannot read file.*
