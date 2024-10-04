/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:42:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 17:42:08 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_pipefd(int pipefd[2], t_ast *ast, t_minishell *minishell)
{
	if (minishell->pipe_before)
	{
		ft_dup2_std(minishell->pipe, IN, minishell);
	}
	if (ast->token == PIPE)
	{
		ft_dup2_std(pipefd[1], OUT, minishell);
		close(pipefd[0]);
	}
	minishell->pipe_before = false;
}

void	ft_do_pipe_child(int pipefd[2], t_ast *ast, t_minishell *minishell)
{
	t_ast	*left;
	t_ast	*right;
	t_pid	*next;

	left = ast->left;
	right = ast->right;
	while (minishell->wait_for_pids)
	{
		next = minishell->wait_for_pids->next;
		free(minishell->wait_for_pids);
		minishell->wait_for_pids = next;
	}
	ft_child_pipefd(pipefd, ast, minishell);
	if (ast->token == PIPE)
	{
		ft_clear_node_ast(ast);
		ft_clear_ast(right);
		ft_exec_ast(left, minishell);
	}
	else
		ft_exec_ast(ast, minishell);
	ft_exit_minishell(minishell, minishell->status);
}

void	ft_do_pipe_parent(int pipefd[2], pid_t pid, \
	t_ast *ast, t_minishell *minishell)
{
	t_ast	*right;
	t_ast	*left;

	if (minishell->pipe_before)
		close(minishell->pipe);
	if (ast->token == PIPE)
	{
		minishell->pipe = pipefd[0];
		close(pipefd[1]);
	}
	else
		minishell->pipe = -1;
	if (((ast->token == PIPE) && ast->left->cmd)
		|| (minishell->pipe_before && ast->cmd))
		ft_add_pid_to_wait(pid, minishell);
	if (minishell->pipe_before && (ast->token != PIPE))
		ft_last_pipe_wait(minishell);
	minishell->pipe_before = (ast->token == PIPE);
	right = ast->right;
	left = ast->left;
	ft_clear_node_ast(ast);
	ft_clear_ast(left);
	ft_exec_ast(right, minishell);
}

void	ft_do_pipe(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];

	if ((ast->token == PIPE) && (pipe(pipefd) == -1))
	{
		ft_fail(ERR_PIPE, NULL);
		minishell->status = STATUS_PIPE;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_fail(ERR_FORK, NULL);
		minishell->status = STATUS_FORK;
		return ;
	}
	if (!pid)
		ft_do_pipe_child(pipefd, ast, minishell);
	ft_do_pipe_parent(pipefd, pid, ast, minishell);
}
