/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:14:27 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 16:07:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

int	profondeur_ast(t_ast *ast)
{
	int	left;
	int	right;

	if (ast)
	{
		left = profondeur_ast(ast->left);
		right = profondeur_ast(ast->right);
		if (left < right)
			return (right + 1);
		else
			return (left + 1);
	}
	else
		return (0);
}

t_lexer	*ft_lexerof(int token, void *data)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->token = token;
	if (ft_is_fork(lexer->token))
		lexer->data = NULL;
	else
		lexer->data = data;
	lexer->next = NULL;
	return (lexer);
}

int	main(int argc, char **argv)
{
	int		i;
	t_lexer	*lexer;
	t_lexer	*next;
	t_ast	*ast;
	char	*data;

	i = 1;
	lexer = NULL;
	while (i < argc)
	{
		if (ft_is_fork(ft_token_of_str(argv[i])))
			data = NULL;
		else
			data = argv[i + 1];
		if (!lexer)
		{
			lexer = ft_lexerof(ft_token_of_str(argv[i]), data);
			next = lexer;
		}
		else
		{
			next->next = ft_lexerof(ft_token_of_str(argv[i]), data);
			next = next->next;
		}
		if (data)
			i ++;
		i ++;
	}
	ast = ft_ast(lexer);
	while (lexer)
	{
		next = lexer->next;
		free(lexer);
		lexer = next;
	}
	print_ast(ast, 0);
	ft_clear_ast(ast);
}
