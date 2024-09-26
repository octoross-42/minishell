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

void	ft_do_pipe_child(int pipefd[2], t_ast *ast, t_minishell *minishell)
{
	t_ast	*left;
	t_ast	*right;
	t_pid	*next;

	while (minishell->wait_for_pids)
	{
		next = minishell->wait_for_pids->next;
		free(minishell->wait_for_pids);
		minishell->wait_for_pids = next;
	}
	if (minishell->pipe_before)
	{
		dup2(minishell->pipe, STDIN_FILENO);
		close(minishell->pipe);
	}
	if (ast->token == PIPE)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	minishell->pipe_before = false;
	left = ast->left;
	right = ast->right;
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

void	ft_add_pid_to_wait(pid_t pid, t_minishell *minishell)
{
	t_pid	*new;

	new = (t_pid *)malloc(sizeof(t_pid));
	if (!new)
		ft_fail(ERR_MALLOC, NULL);
	new->pid = pid;
	new->next = minishell->wait_for_pids;
	minishell->wait_for_pids = new;
	minishell->last_cmd = pid;
}

void	ft_last_pipe_wait(t_minishell *minishell)
{
	t_pid	*next;
	int		status;

	if (minishell->last_cmd != -1)
	{
		waitpid(minishell->last_cmd, &status, 0);
		minishell->status = WEXITSTATUS(status);
		while (minishell->wait_for_pids)
		{
			waitpid(minishell->wait_for_pids->pid, NULL, 0);
			next = minishell->wait_for_pids->next;
			free(minishell->wait_for_pids);
			minishell->wait_for_pids = next;
		}
	}
	else
		minishell->status = STATUS_OK;
	minishell->wait_for_pids = NULL;
}

void	ft_do_pipe_parent(int pipefd[2], pid_t pid, t_ast *ast, t_minishell *minishell)
{
	if (minishell->pipe_before)
		close(minishell->pipe);
	if (ast->token == PIPE)
	{
		minishell->pipe = pipefd[0];
		close(pipefd[1]);
	}
	else
		minishell->pipe = -1;
	if (((ast->token == PIPE) && ast->left->cmd) || (minishell->pipe_before && ast->cmd))
		ft_add_pid_to_wait(pid, minishell);
	if (minishell->pipe_before && (ast->token != PIPE))
	{
		// printf("pipe before and last for wait\n");
		ft_last_pipe_wait(minishell);
	}
}

void ft_do_pipe(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];
	t_pid	*next;
	t_ast	*right;
	t_ast	*left;

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
	if (ast->token == PIPE)
		minishell->pipe_before = true;
	right = ast->right;
	left = ast->left;
	ft_clear_node_ast(ast);
	ft_clear_ast(left);
	if (right)
		printf("right : %s\n", ft_name_of_token(right->token));
	ft_exec_ast(right, minishell);
}
