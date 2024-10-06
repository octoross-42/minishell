NAME	=	minishell

RESET	:=	\e[0m
BOLD	:=	\e[1m
ITAL	:=	\e[3m
BLINK	:=	\e[5m
GREEN	:=	\e[32m
YELLOW	:=	\e[33m
BLUE	:=	\e[34m
CYAN	:=	\e[36m
PINK	:=	\e[38;2;255;182;193m

CC		=	cc
CFLAGS	= -Wall -Wextra -Werror -MMD -g3
INCLUDE	= include/
LFLAGS	= -lreadline

SIGNALS_SRCS = src/signals/signals.c
DISPLAY_SRCS = src/display/banner.c \
	src/display/input.c
EXECUTION_SRCS = src/execution/cmd.c \
	src/execution/exec.c \
	src/execution/pipe.c \
	src/execution/wait.c \
	src/execution/here_doc.c \
	src/execution/redir.c
ARGV_SRCS = src/argv/arg_of.c \
	src/argv/argv.c \
	src/argv/fill_argv.c \
	src/argv/wildcard_arg.c \
	src/argv/file_arg.c
PARSING_SRCS = src/parsing/ast/ast_add.c \
	src/parsing/ast/ast.c \
	src/parsing/token/token_is.c \
	src/parsing/token/conversion.c \
	src/parsing/lexer/parse_expand.c \
	src/parsing/lexer/lexer.c \
	src/parsing/lexer/lexer_utils.c \
	src/parsing/lexer/parse_arg.c \
	src/parsing/lexer/parse_arg_utils.c \
	src/parsing/lexer/parse_redir.c \
	src/parsing/lexer/parse_cmd.c \
	src/parsing/lexer/quotes.c
MINISHELL_SRCS = src/minishell/env.c \
	src/minishell/env_conversion.c \
	src/minishell/minishell_utils.c \
	src/minishell/minishell.c
HISTORY_SRCS = src/history/add_history.c
BUILDIN_SRCS = src/buildin/buildin.c \
	src/buildin/echo.c \
	src/buildin/env.c \
	src/buildin/export.c \
	src/buildin/unset.c \
	src/buildin/pwd.c \
	src/buildin/cd.c \
	src/buildin/exit.c
UTILS_SRCS = src/utils/char.c \
	src/utils/string.c \
	src/utils/string_copy.c \
	src/utils/utils.c \
	src/utils/split.c \
	src/utils/itoa.c \
	src/utils/gnl/gnl.c \
	src/utils/gnl/gnl_utils.c
WILDCARD_SRCS = src/wildcard/wildcard.c \
	src/wildcard/wildcard_utils.c \
	src/wildcard/fit_wildcard.c
MAIN_SRCS = src/main.c
DEV_SRCS = dev/print.c

SRCS = $(SIGNALS_SRCS) \
	$(DISPLAY_SRCS) \
	$(ARGV_SRCS) \
	$(EXECUTION_SRCS) \
	$(PARSING_SRCS) \
	$(MINISHELL_SRCS) \
	$(HISTORY_SRCS) \
	$(BUILDIN_SRCS) \
	$(UTILS_SRCS) \
	$(WILDCARD_SRCS) \
	$(MAIN_SRCS) \
	$(DEV_SRCS)

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@printf "\r                                                                                                                                       \r\
	$(BOLD)$(BLUE)[objs]: $(RESET)$<"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -g3 -c $< -o $@

$(NAME): $(OBJS)
	@printf "\r                                                                                                                                       \r\
	$(BOLD)$(BLUE)Compilation: $(RESET)done!\n"
	@printf "$(BOLD)$(YELLOW)\nLinking...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@printf "$(BOLD)$(BLUE)Linking: $(RESET)done!$(RESET)\n"
	@printf "\n$(BOLD)$(GREEN)[$(NAME) ready]$(RESET)\n"

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(BOLD)$(CYAN)[objs]\t $(RESET)Clean completed\n"
 
fclean: 
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@printf "$(BOLD)$(CYAN)[objs/minishell] $(RESET)Full clean completed!\n"

re:	
	@make --silent fclean
	@printf "\n"
	@make --silent $(NAME)

.PHONY:	all clean fclean re
