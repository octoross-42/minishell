/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:03 by octoross          #+#    #+#             */
/*   Updated: 2024/09/23 18:27:28 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_ast	*ft_new_ast(t_lexer *lexer)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->token = lexer->token;
	if (ft_is_fork(ast->token))
		ast->data = NULL;
	else
		ast->data = lexer->data;
	ast->left = NULL;
	ast->right = NULL;
	ast->parent = NULL;
	ast->cmd = false;
	return (ast);
}

void	ft_clear_ast(t_ast *ast)
{
	if (!ast)
		return ;
	ft_clear_ast(ast->left);
	ft_clear_ast(ast->right);
	if (ast->token == CMD)
		ft_free_until((void **)ast->data, -1);
	else if (ft_is_redir(ast->token))
		free(ast->data);
	free(ast);
}

int	ft_add_new_ast(t_ast *new, t_ast **current, t_ast **top)
{
	int	status;

	if (!top || !current)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	if (!(*top))
	{
		*top = new;
		*current = new;
		if (new->token == CMD)
			(*current)->cmd = true;
	}
	else
	{
		status = ft_add_ast(new, current, top);
		if (status != STATUS_OK)
			return (ft_clear_ast(*top), status);
	}
	return (STATUS_OK);
}

// #include "dev.h"

t_ast	*ft_ast(t_lexer *lexer, int *status)
{
	t_ast	*new;
	t_ast	*current;
	t_ast	*top;

	top = NULL;
	current = NULL;
	*status = STATUS_OK;
	while (lexer)
	{
		new = ft_new_ast(lexer);
		if (!new)
		{
			*status = STATUS_MALLOC;
			ft_fail(ERR_MALLOC, NULL);
			return (ft_clear_ast(top), NULL);
		}
		*status = ft_add_new_ast(new, &current, &top);
		if (*status != STATUS_OK)
			return (NULL);
		lexer = lexer->next;
		// print_ast(top, 0);
	}
	return (top);
}
