CC					= gcc
CFLAGS				= -Wall -Werror -Wextra 
.DEFALT_GOAL		:= all
NAME				= ft_tail 

SOURCES				= $(wildcard ./srcs/ft_*.c)
#HEADERS				= $(wildcard includes/*.h)
OBJECTS				= $(patsubst %.c, %.o, $(SOURCES))
#V1_TESTS			= $(wildcard tests/v1/*.c)
#V2_TESTS			= $(wildcard tests/v2/*.c)

#DEP					= $(wildcard includes/*.h)
#-include			$(DEP)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	/bin/rm -f $(OBJECTS)

.PHONY: fclean
fclean: clean
	/bin/rm -f $(NAME)

.PHONY: re
re: fclean all

