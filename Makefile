NAME = minishell

SRCS = src/display/banner.c \
		src/display/input.c \
		src/parsing/ast/ast_add.c \
		src/parsing/ast/ast.c \
		src/parsing/token/token_is.c \
		src/parsing/token/conversion.c \
		src/parsing/lexer/expand.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/parse_arg.c \
		src/parsing/lexer/parse_cmd.c \
		src/parsing/lexer/quotes.c \
		src/execution/exec.c \
		src/utils/char.c \
		src/utils/string.c \
		src/utils/utils.c \
		src/utils/split.c \
		src/main.c \
		dev/print.c \

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