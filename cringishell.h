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

# define PIPE 1
# define OR 2
# define AND 3
# define INPUT 4
# define OUTPUT 5
# define HERE_DOC 6
# define APPEND 7
# define CMD 8

typedef struct s_lexer
{
	void			*data;
	char			*token;
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