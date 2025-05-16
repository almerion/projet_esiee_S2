CC=gcc
CFLAG = -Wall -ansi -std=c99 -Werror -Wextra -g -Ofast
SRC_DIR = src
OBJ_DIR = bin
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAG)

exe: $(OBJ)
	$(CC) -o $@ $^

clean: 
	rm -f exe
	rm -f $(OBJ)