CC = gcc
CFLAGS = -Wall -ansi -std=c99 -Werror -Wextra -g -I include

DEPS =  include/adress.h \
        include/matrix.h \
        include/parser.h \
        include/path.h \
        include/genetic.h

SRC =   src/main.c \
        src/genetic.c \
        src/matrix.c \
        src/parser.c \
        src/path.c \
        src/adress.c

OBJ = $(SRC:.c=.o)

all: genetic

genetic: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) genetic
