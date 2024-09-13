/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:26:57 by octoross          #+#    #+#             */
/*   Updated: 2024/09/13 21:19:16 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_is_fork(int token)
{
	return ((token == PIPE) || (token == OR) || (token == AND));
}

bool	ft_is_redir(int token)
{
	if ((token == INPUT) || (token == OUTPUT)
		|| (token == HERE_DOC) || (token == APPEND));
}

bool	ft_fork_token(t_ast *new, t_ast *current, t_ast	**top)
{
	t_ast	*ast;

	ast = current;
	while (ast && ast->parent
		&& !ft_is_fork(ast->parent->token))
		ast = ast->parent;
	if (!ast)
		return (ft_fail(ERR_AST), NULL);
	else
	{
		new->left = ast;
		if (!ast->parent)
		{
			new->left = ast;
			*top = new;
		}
		else
		{
			new->parent = ast->parent;
			ast->parent->right = new;
		}
	}
	return (true);
}

bool	ft_redic_token(t_ast *new, t_ast *current, t_ast **top)
{
	if (current && (current->token == CMD))
	{
		if (*top == current)
			*top = new;
		new->parent = current->parent;
		new->left = current;
		if (current->parent->left == current)
			current->parent->left = new;
		else
			current->parent->right = new;
	}
	else
	{
		new->parent = current;
		if (!current->left)
			current->left = new;
		else if (!current->right)
			current->right = new;
		else
			return (ft_fail(ERR_AST), false);
	}
	return (true);
}

bool	ft_cmd_token(t_ast *new, t_ast *current)
{
	if (!current->left)
		current->left = new;
	else if (!current->right)
		current->right = new;
	else
		return (ft_fail(ERR_AST), false);
	return (true);
}
