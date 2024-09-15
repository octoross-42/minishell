/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:03 by octoross          #+#    #+#             */
/*   Updated: 2024/09/15 20:06:56 by octoross         ###   ########.fr       */
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
	if (ft_is_fork(ast->token))
		ast->data = NULL;
	else
		ast->data = lexer->data;
	ast->left = NULL;
	ast->right = NULL;
	ast->parent = NULL;
	return (ast);
}

bool	ft_is_fork(int token)
{
	return ((token == PIPE) || (token == OR) || (token == AND));
}

bool	ft_is_output(int token)
{
	return ((token == OUTPUT) || (token == APPEND));
}

void	ft_clear_ast(t_ast *ast)
{
	if (!ast)
		return ;
	ft_clear_ast(ast->left);
	ft_clear_ast(ast->right);
	free(ast);
}

t_ast	*ft_ast(t_lexer *lexer)
{
	t_ast	*new;
	t_ast	*current;
	t_ast	*top;

	top = NULL;
	while (lexer)
	{
		new = ft_new_ast(lexer);
		if (!new)
			return (NULL);
		if (!top)
		{
			top = new;
			current = new;
		}
		else if (!ft_add_ast(new, &current, &top))
			return (ft_clear_ast(top), NULL);
		lexer = lexer->next;
	}
	return (top);
}
