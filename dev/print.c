/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:00:54 by octoross          #+#    #+#             */
/*   Updated: 2024/09/24 23:48:00 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

void	print_lexer(t_lexer *lexer)
{
	int		i;
	char	**args;

	while (lexer)
	{
		printf("token : %s", ft_name_of_token(lexer->token));
		if (lexer->data)
		{
			if (lexer->token == CMD)
			{
				args = (char **)lexer->data;
				i = 0;
				printf(", data : ");
				while (args[i])
					printf("'%s' ", args[i ++]);
			}
			else if (ft_is_redir(lexer->token))
				printf(", data : '%s'", (char *)lexer->data);
		}
		printf("\n");
		lexer = lexer->next;
	}
}

void	print_node_ast(t_ast *ast, int n, int left)
{
	int		i;
	t_arg	**args;
	t_arg	*arg;

	i = 0;
	while (i++ < n)
		printf("\t");
	if (n && left)
		printf("\\");
	else if (n)
		printf("/");
	printf("%s", ft_name_of_token(ast->token), ast->cmd);
	if (ast->cmd)
		printf(" (cmd)");
	if (ast->token == CMD)
	{
		printf(" :");
		args = ast->data;
		i = 0;
		while (args[i])
		{
			arg = args[i ++];
			printf(" \"");
			while (arg)
			{
				if (arg->expand)
					printf(" expand :");
				printf(" '%s'", arg->data);
				arg = arg->next;
			}
			printf("\"");
		}
	}
	else if (ft_is_redir(ast->token))
		printf(" : '%s'\n", (char *)ast->data);
	printf("\n");
}

void	print_ast(t_ast *ast, int n)
{
	int		left;

	if (!ast)
		return ;
	if (!n)
		printf("\n");
	left = (n > 0);
	if (n < 0)
		n = -n;
	if (ast->right)
		print_ast(ast->right, -n - 1);
	print_node_ast(ast, n, left);
	if (ast->left)
		print_ast(ast->left, n + 1);
}
