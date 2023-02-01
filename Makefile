##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## MAKEFILE
##

CFLAGS = -g3 -lncurses -Wno-unused-command-line-argument

SRC	=	$(wildcard *.c) \

OBJ	=	$(SRC:.c=.o)

NAME	=	my_ftp

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
