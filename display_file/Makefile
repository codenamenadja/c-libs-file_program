CC					= gcc
CFLAGS				= -Wall -Werror -Wextra 
NAME				= ft_display_file
SOURCE				= ./ft_display_file.c

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

