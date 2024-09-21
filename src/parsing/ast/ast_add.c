/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:26:57 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 18:45:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_append_ast(t_ast *new, t_ast **current)
{
	new->parent = *current;
	if (!(*current)->left)
		(*current)->left = new;
	else if (!(*current)->right)
		(*current)->right = new;
	else
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	*current = new;
	return (STATUS_OK);
}

int	ft_fork_token(t_ast *new, t_ast **current, t_ast **top)
{
	t_ast	*ast;

	ast = *current;
	while (ast && ast->parent
		&& !ft_is_fork(ast->parent->token))
		ast = ast->parent;
	if (!ast->parent)
		*top = new;
	else
	{
		new->parent = ast->parent;
		ast->parent->right = new;
		// HYPO : cannot be 2 | d'affilée
	}
	new->left = ast;
	ast->parent = new;
	*current = new;
	return (STATUS_OK);
}

int	ft_output_token(t_ast *new, t_ast **current, t_ast **top)
{
	// HYPO : 2 cmd cannot succeed
	if (((*current)->token == CMD))
	{
		if (*top == *current)
			*top = new;
		if ((*current)->parent->left == *current)
			(*current)->parent->left = new;
		else
			(*current)->parent->right = new;
		new->parent = (*current)->parent;
		new->left = (*current);
		(*current)->parent = new;
		return (STATUS_OK);
		// TODO enlever les bool return des add_token
	}
	else
		return (ft_append_ast(new, current));
}

int	ft_add_ast(t_ast *new, t_ast **current, t_ast **top)
{
	if (ft_is_fork(new->token))
		return (ft_fork_token(new, current, top));
		// HYPO : fork cant be last or first so cannot be current
	if (ft_is_output(new->token))
		return (ft_output_token(new, current, top));
	if ((new->token == INPUT) || (new->token == HERE_DOC)
		|| (new->token == CMD))
		return (ft_append_ast(new, current));
	else
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
}
