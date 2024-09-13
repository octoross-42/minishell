/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:03 by octoross          #+#    #+#             */
/*   Updated: 2024/09/13 21:18:01 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_ast	*ft_new_ast(t_lexer *lexer)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (ft_fail(ERR_MALLOC), NULL);
	ast->token = lexer->token;
	ast->data = lexer->data;
	ast->left = NULL;
	ast->right = NULL;
	ast->parent = NULL;
	return (ast);
}

static bool	ft_add_ast(t_ast *new, t_ast *current, t_ast **top)
{
	if (ft_is_fork(new->token) && !ft_fork_token(new, current, top))
		return (NULL);
	else if (ft_is_redir(new->token) && !ft_redic_token(new, current, top))
		return (NULL);
	else if ((new->token == CMD) && !ft_cmd_token(new, current))
		return (NULL);
	else
		return (ft_fail(ERR_AST), NULL);
}

t_ast	*ft_ast(t_lexer *lexer)
{
	t_ast	*new;
	t_ast	*current;
	t_ast	*top;

	while (lexer)
	{
		new = ft_new_ast(lexer);
		if (!new)
			return (NULL);
		if (!top)
			top = new;
		else if (!ft_add_ast(new, current, &top))
			return (NULL);
		current = new;
		lexer = lexer->next;
	}
	return (top);
}
