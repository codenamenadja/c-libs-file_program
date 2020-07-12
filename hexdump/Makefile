CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I. -c
.DEFALT_GOAL		:= all
NAME				= ft_hexdump.a

SOURCES				= $(wildcard srcs/ft_*.c)
HEADERS				= $(wildcard includes/*.h)
OBJECTS				= $(patsubst %.c, %.o, $(SOURCES))

#DEP					= $(wildcard includes/*.h)
#-include			$(DEP)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

.PHONY: clean
clean:
	/bin/rm -f $(OBJECTS)

.PHONY: fclean
fclean: clean
	/bin/rm -f $(NAME)

.PHONY: re
re: fclean all

