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

void ft_do_pipe(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];
	t_pid	*next;

	if ((ast->token == PIPE) && (pipe(pipefd) == -1))
	{
		ft_fail(ERR_PIPE, NULL);
		ft_exit_minishell(minishell, STATUS_PIPE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_fail(ERR_FORK, NULL);
		ft_exit_minishell(minishell, STATUS_FORK);
	}
	if (!pid)
	{
		// printf("child\n");
		if (minishell->pipe_before)
		{
			dup2(minishell->pipe, STDIN_FILENO);
			close(minishell->pipe);
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		minishell->pipe_before = false;
		// TODO free ast
		// printf("child good\n");
		if (ast->token == PIPE)
			ft_exec_ast(ast->left, minishell);
		else
			ft_exec_ast(ast, minishell);
		ft_exit_minishell(minishell, STATUS_OK);
	}
	// printf("a\n");
	close(pipefd[1]);
	// printf("b\n");
	if (minishell->pipe_before)
		close(minishell->pipe);
	// printf("c\n");
	if (ast->token == PIPE)
		minishell->pipe = pipefd[0];
	else
		minishell->pipe = -1;
	// printf("d\n");
	if (((ast->token == PIPE) && ast->left->cmd) || (minishell->pipe_before && ast->cmd))
		ft_add_pid_to_wait(pid, minishell);
	// printf("e\n");
	// TODO free ast
	if (ast->token == PIPE)
		minishell->pipe_before = true;
	// printf("f\n");
	if (minishell->pipe_before && (ast->token != PIPE))
	{
		// printf("last pipe\n");
		if (minishell->last_cmd != -1)
		{
			// printf("ya une commande\n");
			waitpid(minishell->last_cmd, &minishell->status, 0);
			// printf("we good ?\n");
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
	// printf("g\n");
	if (ast->token == PIPE)
		minishell->pipe_before = true;
	// printf("h\n");
	ft_exec_ast(ast->right, minishell);
}

