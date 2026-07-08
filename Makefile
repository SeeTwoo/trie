NAME = trie_search
CC = cc -Wall -Wextra -Werror -Iincludes
CCDEBUG = $(CC) -g3 -O0

SRC_DIR = src
SRC_FILES = main.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

debug:
	$(MAKE) CC="$(CCDEBUG)" all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
