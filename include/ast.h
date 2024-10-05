/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:21:09 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 22:08:08 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H

# define AST_H

# include "lexer.h"

typedef struct s_ast
{
	int				token;
	bool			cmd;
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}	t_ast;

void	ft_clear_node_ast(t_ast *ast);
void	ft_clear_ast(t_ast *ast);
bool	ft_is_output(int token);
int		ft_output_token(t_ast *new, t_ast **current, t_ast **top);
int		ft_pipe_token(t_ast *new, t_ast **current, t_ast **top);
int		ft_subshell_token(t_ast *new, t_lexer **last, t_ast **current);
int		ft_append_ast(t_ast *new, t_ast **current);
int		ft_add_ast(t_ast *new, t_lexer **last, t_ast **current, t_ast **top);
t_ast	*ft_ast(t_lexer *lexer, int *status, t_lexer **last);

#endif