/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:00:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/22 01:00:08 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_fork(t_ast *ast, t_minishell *minishell)
{
	int		pipefd[2];
	pid_t	pid;

	if (ast->token == PIPE && (pipe(pipefd) == -1))
	{
		ft_fail(ERR_PIPE, NULL);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_fail(ERR_FORK, NULL);
		return ;
	}
	if (!pid)
	{
		if (ast->token == PIPE)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		ft_exec_ast(ast->left, minishell);
	}
	ft_exec_ast(ast->right, minishell);
}
