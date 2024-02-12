SRC		:=	$(shell find . -type f -name '*.c')

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	= -std=gnu -Wall -Wextra
V_FLAG  = --leak-check=full --show-leak-kinds=all --track-origins=yes
EXE		= myftp
SAN		= -g3

all:	$(EXE)

%.o:	%.cpp
		$(CC) -o $@ -c $< $(CFLAGS) $(SAN)

$(EXE): $(OBJ)
		$(CC) -o $(EXE) $^

clean:
		@rm -rf $(OBJ)
		@rm -rf vgcore*
		@rm -rf *.gcda
		@rm -rf *.gcno

fclean:	clean
		@rm -rf $(EXE)

re:	fclean all

val:
	make re && valgrind ./$(EXE)

val_full:
	make re && valgrind $(V_FLAG) ./$(EXE)
