##
## EPITECH PROJECT, 2023
## BS-my_ftp
## File description:
## Makefile
##

CC ?=gcc
RM = rm -f

NAME =  my_ftp
SRCS = $(wildcard *.c) \
       
       $(wildcard src/*.c) \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -Wall -Wextra -I include -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)


fclean: clean
	$(RM) $(NAME)
	$(RM) $(wildcard vgcore*)

re: fclean all



.PHONY: all clean fclean re tests_run
