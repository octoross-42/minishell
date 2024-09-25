/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:56:56 by octoross          #+#    #+#             */
/*   Updated: 2024/09/06 14:56:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "utils.h"

# define PIPE 1
# define OR 2
# define AND 3
# define INPUT 4
# define OUTPUT 5
# define HERE_DOC 6
# define APPEND 7
# define CMD 8

// ERR_PARSING is never supposed to be print
# define ERR_PARSING "Bad parsing happenned :(\n"
# define ERR_SYNTAX "syntax error near unexpected token `%s'\n"

typedef struct s_expand
{
	bool			is_expand;
	char			*name;
	int				len_name;
	struct s_expand	*next;
}	t_expand;

typedef struct s_arg
{
	bool			expand;
	bool			wildcard;
	char			*data;
	struct s_arg	*next;
}	t_arg;

int		ft_arg_expand(char **s, t_arg *arg);
int		ft_len_quotes(char **s, char *quote);
int		ft_close_quotes(char **s, char *data, char *quote);

typedef struct s_lexer
{
	void			*data;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*previous;
}	t_lexer;

int		ft_parse_redir(char **s, t_lexer *lexer);
int		ft_parse_arg(char **s, t_arg **data);
int		ft_parse_cmd(char **s, t_lexer *lexer);
void	ft_clear_lexer(t_lexer *lexer, int erase_data);
t_lexer	*ft_lexer(char *line, int *status);

typedef struct s_ast
{
	int				token;
	bool			cmd;
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}	t_ast;

bool	ft_is_separator(int token);
bool	ft_is_redir(int token);
bool	ft_is_output(int token);
int		ft_output_token(t_ast *new, t_ast **current, t_ast **top);
bool	ft_is_fork(int token);
int		ft_fork_token(t_ast *new, t_ast **current, t_ast **top);
int		ft_append_ast(t_ast *new, t_ast **current);
int		ft_add_ast(t_ast *new, t_ast **current, t_ast **top);
t_ast	*ft_ast(t_lexer *lexer, int *status);
void	ft_clear_ast(t_ast *ast);

#endif
