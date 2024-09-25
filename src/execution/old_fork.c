/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:42:58 by octoross          #+#    #+#             */
/*   Updated: 2024/09/22 23:42:58 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_pipe(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	if ((ast->token == PIPE) && (pipe(pipefd) == -1))
	{
		ft_fail(ERR_PIPE, NULL);
		return (false);
	}
	return (true);
}

void	ft_pipe_parent(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	if (minishell->pipe_before == PIPE)
		close(minishell->pipe);
	if (ast->token == PIPE)
	{
		close(pipefd[1]);
		minishell->pipe = pipefd[0];
	}
}

void	ft_do_previous_pipe(t_minishell *minishell)
{
	if (minishell->pipe_before == PIPE)
	{
		dup2(minishell->pipe, STDIN_FILENO);
		// TODO protéger les dup2
		close(minishell->pipe);
	}
}

void	ft_wait_previous(t_ast *ast, t_minishell *minishell)
{
	if ((minishell->pipe_before == AND) || (minishell->pipe_before == OR))
	{
		if (minishell->last_cmd == -1)
		{
			if (minishell->pipe_before == AND)
				ft_exec_ast(ast, minishell, true);
			else if (minishell->pipe_before == OR)
				ft_exit_minishell(minishell, STATUS_OK);
		}
		waitpid(minishell->last_cmd, &minishell->status, 0);
		if (WEXITSTATUS(minishell->status) != STATUS_OK)
		{
			if (minishell->pipe_before == AND)
				ft_exit_minishell(minishell, WEXITSTATUS(minishell->status));
			else if (minishell->pipe_before == OR)
				ft_exec_ast(ast, minishell, true);
		}
		else
		{
			if (minishell->pipe_before == OR)
				ft_exit_minishell(minishell, WEXITSTATUS(minishell->status));
			else if (minishell->pipe_before == AND)
				ft_exec_ast(ast, minishell, true);
		}
	}
}

void	ft_do_child(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	pid_t	wait_pid;

	ft_do_previous_pipe(minishell);
	if (ast->token == PIPE)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	ft_wait_previous(ast->left, minishell);
	ft_exec_ast(ast->left, minishell, true);
}

void	ft_exec_fork(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];
	
	if (!ft_init_pipe(ast, minishell, pipefd))
	{
		ft_fail(ERR_PIPE, NULL);
		return ;
	}
	pid = fork();
	if (pid == -1)

		ft_fail(ERR_FORK, NULL);
	if (!pid)
		ft_do_child(ast, minishell, pipefd);
	minishell->last_pid = pid;
	if (ast->left->cmd || (minishell->pipe_before != PIPE))
		minishell->last_cmd = pid;
	else
		minishell->last_cmd = -1;
	ft_pipe_parent(ast, minishell, pipefd);
	minishell->pipe_before = ast->token;
	ft_exec_ast(ast->right, minishell, false);
}
