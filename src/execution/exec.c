/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:21:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 00:08:23 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_fork(t_ast *ast, t_minishell *minishell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_free_until((void **)minishell->path, -1);
		ft_clear_ast(minishell->ast);
		ft_fail(ERR_FORK, NULL);
		exit(EXIT_FORK);
	}
}

void	ft_redir(t_ast *ast)
{
	return ;
}

void	ft_exec_cmd(void)
{
	return ;
}

void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
{
	if (ft_is_fork(ast->token))
		ft_exec_fork(ast, minishell);
	else if (ft_is_redir(ast->token))
		ft_redir(ast);
	else if (ast->token == CMD)
		ft_exec_cmd();
	else
	{
		ft_free_until((void **)minishell->path, -1);
		ft_clear_ast(minishell->ast);
		ft_fail(ERR_TOKEN, NULL);
		exit(EXIT_TOKEN);
	}
}

void	ft_exec_line(t_minishell *minishell)
{
	int	status;
	
	if (!minishell->ast)
	{
		ft_free_until((void **)minishell->path, -1);
		// exit(EXIT_SUCCESS);
		// TODO
	}
	minishell->last_pid = fork();
	if (minishell->last_pid == -1)
	{
		ft_free_until((void **)minishell->path, -1);
		ft_fail(ERR_FORK, NULL);
		exit(EXIT_FORK);
	}
	else if (!minishell->last_pid)
		ft_exec_ast(minishell->ast, minishell);
	else
	{
		waitpid(minishell->last_pid, &status, 0);
		while (wait(NULL) != -1)
			;
		ft_minishell_input(minishell);
	}
	ft_free_until((void **)minishell->path, -1);
	ft_clear_ast(minishell->ast);
	exit(EXIT_SUCCESS);
}
