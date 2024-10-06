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
# include "token.h"
# include "err.h"

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
	char			*str;
	struct s_arg	*next;
	struct s_arg	*previous;
}	t_arg;

void	ft_clear_arg(t_arg *arg);
void	ft_clear_args(t_arg **args, int until);
int		ft_add_new_arg(t_arg **last, t_arg **top);

bool	ft_is_expand(char c, char next, char quote);
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

int		ft_parse_subshell(char **s, t_lexer **lexer);
int		ft_parse_redir(char **s, t_lexer *lexer);
int		ft_parse_arg(char **s, t_arg **data);
int		ft_parse_cmd(char **s, t_lexer *lexer);
void	ft_clear_lexer(t_lexer *lexer, int erase_data);
bool	ft_add_lexer(t_lexer **top, t_lexer **last);
int		ft_merge_cmds_between_redir(t_lexer **lexer);
t_lexer	*ft_lexer(char *line, int *status);

#endif
