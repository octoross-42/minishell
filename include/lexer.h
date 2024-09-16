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

// ERR_AST is never supposed to be print
# define ERR_AST "Bad parsing happenned :(\n"

typedef struct s_lexer
{
	void			*data;
	char			token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_ast
{
	int				token;
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}	t_ast;

bool			ft_is_output(int token);
bool			ft_output_token(t_ast *new, t_ast **current, t_ast **top);
bool			ft_is_fork(int token);
bool			ft_fork_token(t_ast *new, t_ast **current, t_ast **top);
bool			ft_append_ast(t_ast *new, t_ast **current);
bool			ft_add_ast(t_ast *new, t_ast **current, t_ast **top);
t_ast			*ft_ast(t_lexer *lexer);
void			ft_clear_ast(t_ast *ast);

#endif
