CC = gcc
CFLAGS = -Wall -ansi -std=c99 -Werror -Wextra -g -I include

DEPS =  include/adress.h \
        include/gene.h \
        include/individual.h \
        include/matrix.h \
        include/parser.h \
        include/population.h \
        include/genetic.h

SRC =   src/main.c \
        src/genetic.c \
        src/matrix.c \
        src/parser.c \
        src/individual.c \
        src/adress.c \
        src/gene.c \
        src/population.c

OBJ = $(SRC:.c=.o)

all: genetic

genetic: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) genetic
