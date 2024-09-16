NAME = minishell

SRCS = src/parsing/ast_add.c \
		src/parsing/ast.c \
		src/display/banner.c \
		src/display/input.c \
		src/utils/utils.c \
		src/main.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror 
INCLUDE = include/

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -g3 -c $< -o ${<:.c=.o} 

$(NAME): ${OBJS}
	$(CC) $(OBJS) -o $(NAME) -lreadline 

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all