##
## EPITECH PROJECT, 2024
## B-NWP-400-LYN-4-1-myftp-mael.rabot
## File description:
## Makefile
##

SRC		 := $(shell find . -type f -name '*.c' -not -path "./tests/*")
TEST_SRC := $(shell find . -type f -name '*.c' -not -name 'main.c')

OBJ		=	$(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra
V_FLAG  = --leak-check=full --show-leak-kinds=all --track-origins=yes
EXE		= myftp
TEST_EXE = unit_tests
SAN		= -g3
COV		= --coverage

all:	$(EXE)

%.o:	%.c
		$(CC) -o $@ -c $< $(CFLAGS) $(SAN)

$(EXE): $(OBJ)
		$(CC) -o $(EXE) $^

$(TEST_EXE): $(TEST_OBJ)
	$(CC) -o $(TEST_EXE) $^ -lcriterion $(COV)

clean:
		@rm -rf $(OBJ)
		@rm -rf vgcore*
		@rm -rf *.gcda
		@rm -rf *.gcno
		@rm -rf ./test/*.o

fclean:	clean
		@rm -rf $(EXE)
		@rm -rf $(TEST_EXE)

re:	fclean all

val:
	make re && valgrind ./$(EXE)

val_full:
	make re && valgrind $(V_FLAG) ./$(EXE)

test: $(TEST_EXE)
	./$(TEST_EXE) --verbose

tests_run: fclean test
	gcovr --exclude-directories tests

.PHONY: all clean fclean re val val_full test tests_run
