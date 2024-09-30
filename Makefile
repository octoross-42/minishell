NAME = minishell

SRCS = src/display/banner.c \
		src/display/input.c \
		src/parsing/ast/ast_add.c \
		src/parsing/ast/ast.c \
		src/parsing/token/token_is.c \
		src/parsing/token/conversion.c \
		src/parsing/lexer/parse_expand.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/parse_arg.c \
		src/parsing/lexer/parse_arg_utils.c \
		src/parsing/lexer/parse_redir.c \
		src/parsing/lexer/parse_cmd.c \
		src/parsing/lexer/quotes.c \
		src/execution/cmd.c \
		src/execution/exec.c \
		src/execution/pipe.c \
		src/execution/redir.c \
		src/execution/argv.c \
		src/minishell/env.c \
		src/minishell/env_conversion.c \
		src/minishell/minishell.c \
		src/history/add_history.c \
		src/buildin/buildin.c \
		src/buildin/echo.c \
		src/buildin/env.c \
		src/buildin/pwd.c \
		src/buildin/cd.c \
		src/utils/char.c \
		src/utils/string.c \
		src/utils/string_copy.c \
		src/utils/utils.c \
		src/utils/split.c \
		src/utils/itoa.c \
		src/utils/gnl/gnl.c \
		src/utils/gnl/gnl_utils.c \
		src/wildcard/wildcard.c \
		src/wildcard/wildcard_utils.c \
		src/wildcard/wildcards_utils.c \
		src/wildcard/fit_wildcard.c \
		src/main.c \
		dev/print.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
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
