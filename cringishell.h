#ifndef LEXER_H
# define LEXER_H

# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<curses.h>
# include<term.h>
# include<unistd.h>
# include<stdlib.h>
# include<signal.h>
# include<string.h>
# include<stdlib.h>

# define UNDEFINED 0
# define QUOTE 1
# define DOUBLE 2
# define EXPAND 3
# define PIPE 4
# define INPUT 5
# define OUTPUT 6
# define HERE_DOC 7
# define APPEND 8
# define FILE 9
# define CMD 10
# define ARG 11
# define AMPER 12
# define ESP 13
# define LPAR 14
# define RPAR 15

typedef struct s_lexer
{
	void			*data;
	char			token;
	int             pos;
	int             cmd_pos;
	struct	s_lexer	*next;
}	t_lexer;

typedef struct  s_parse
{
	int pos;
	int	cmd;
}	t_parse;

#endif