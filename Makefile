NAME = minishell

SRCS = src/parsing/ast/ast_add.c \
		src/parsing/ast/ast.c \
		src/display/banner.c \
		src/display/input.c \
		src/execution/exec.c \
		src/utils/libc.c \
		src/utils/utils.c \
		src/utils/split.c \
		src/main.c \
		dev/print.c \
		dev/token_conversion.c

OBJS = ${SRCS:.c=.o}

CC = cc
# CFLAGS = -Wall -Wextra -Werror
INCLUDE = include/

# enlever g3
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