CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
NAME			= ft_od.a
OBJECTS			= build/ft_od.o

.DEFAULT_TARGET	:= all

.PHONY: all
all: $(NAME)

$(NAME): build
	mkdir build

.PHONY: build
build: $(OBJECTS)
	
build/ft_od.o:
	$(CC) $(CFLAGS) -c srcs/ft_od.c -o $@

.PHONY:	clean
clean:
	rm build/*.o

.PHONY: fclean
fclean:
	rm -rf build

.PHONY: re
re:	fclean build

