/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:26:57 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 21:21:02 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ft_append_ast(t_ast *new, t_ast **current)
{
	t_ast	*parent;

	new->parent = *current;
	if (!(*current)->left)
		(*current)->left = new;
	else if (!(*current)->right)
		(*current)->right = new;
	else
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	*current = new;
	if ((*current)->token == CMD)
	{
		(*current)->cmd = true;
		parent = (*current)->parent;
		while (parent && !ft_is_separator(parent->token))
		{
			parent->cmd = true;
			parent = parent->parent;
		}
	}
	return (STATUS_OK);
}

int	ft_pipe_token(t_ast *new, t_ast **current, t_ast **top)
{
	t_ast	*ast;

	ast = *current;
	while (ast && ast->parent
		&& !ft_is_sep_or_sub(ast->parent->token))
		ast = ast->parent;
	if (!ast->parent)
		*top = new;
	else
	{
		new->parent = ast->parent;
		if (ast->parent->left == ast)
			ast->parent->left = new;
		else
			ast->parent->right = new;
	}
	new->left = ast;
	ast->parent = new;
	*current = new;
	return (STATUS_OK);
}

int	ft_redir_token(t_ast *new, t_ast **current, t_ast **top)
{
	if ((*current)->token == CMD)
	{
		new->cmd = true;
		if (*top == *current)
			*top = new;
		else
		{
			if ((*current)->parent->left == *current)
				(*current)->parent->left = new;
			else if ((*current)->parent->right == *current)
				(*current)->parent->right = new;
			else
				return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
			new->parent = (*current)->parent;
		}
		new->left = (*current);
		(*current)->parent = new;
		return (STATUS_OK);
	}
	else
		return (ft_append_ast(new, current));
}

int	ft_subshell_token(t_ast *new, t_lexer **last, t_ast **current)
{
	int		status;

	new->left = ft_ast((*last)->next, &status, last);
	if (status != STATUS_OK)
		return (status);
	if (!(new->left))
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	new->cmd = new->left->cmd;
	if (new != *current)
		return (ft_append_ast(new, current));
	return (STATUS_OK);
}

int	ft_add_ast(t_ast *new, t_lexer **last, t_ast **current, t_ast **top)
{
	if (new->token == SUBSHELL)
		return (ft_subshell_token(new, last, current));
	else if (new->token == PIPE)
		return (ft_pipe_token(new, current, top));
	else if (ft_is_redir(new->token))
		return (ft_redir_token(new, current, top));
	else if ((new->token == CMD) || ft_is_separator(new->token))
		return (ft_append_ast(new, current));
	else
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
}
