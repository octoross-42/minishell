/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:00:54 by octoross          #+#    #+#             */
/*   Updated: 2024/09/19 21:03:19 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

void	print_lexer(t_lexer *lexer)
{
	int	i;
	while (lexer)
	{
		printf("token : %s", str_of_token(lexer->token));
		if (lexer->data)
		{
			i = 0;
			printf(" data : ");
			while (lexer->data[i])
				printf("'%s' ", lexer->data[ i++]);
		}
		printf("\n");
		lexer = lexer->next;
	}
}

void	print_ast(t_ast *ast, int n)
{
	int	i;
	int	left;

	if (!ast)
		return ;
	if (!n)
		printf("\n");
	left = (n > 0);
	if (n < 0)
		n = -n;
	if (ast->right)
		print_ast(ast->right, -n - 1);
	i = 0;
	while (i++ < n)
		printf("\t");
	if (n && left)
		printf("\\");
	else if (n)
		printf("/");
	printf("%s %s\n", str_of_token(ast->token), ast->data);
	if (ast->left)
		print_ast(ast->left, n + 1);
}
