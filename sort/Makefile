CC					= gcc
CFLAGS				= -Wall -Werror -Wextra 
NAME				= sort
SOURCE				= ./srcs/ft_sort.c

.DEFAULT_GOAL		:= all

.PHONY: all
all: $(NAME)

$(NAME): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean
clean:
	/bin/rm -f $(NAME)

.PHONY: re
re: clean all

