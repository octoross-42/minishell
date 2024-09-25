/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:21:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 17:35:17 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_last(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	pid_t	wait_pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fail(ERR_FORK, NULL);
		ft_exit_minishell(minishell, STATUS_FORK);
	}
	if (!pid)
	{
		ft_do_previous_pipe(minishell);
		ft_wait_previous(ast, minishell);
		ft_exec_ast(ast, minishell, true);
	}
	if (minishell->pipe_before == PIPE)
		close(minishell->pipe);
	minishell->last_pid = pid;
	if (ast->cmd || (minishell->pipe_before != PIPE))
		minishell->last_cmd = pid;
	else
		minishell->last_cmd = -1;
	if (minishell->last_cmd != -1)
		waitpid(minishell->last_cmd, &minishell->status, 0);
	while (wait(NULL) != -1)
		;
	ft_minishell_input(minishell);
}

void	ft_exec_ast(t_ast *ast, t_minishell *minishell, bool in_fork)
{
	if (ast-token == PIPE))
		ft_exec_fork(ast, minishell);
	else
	{
		if (!in_fork)
			ft_exec_last(ast, minishell);
		else
		{
			if (ft_is_redir(ast->token))
				ft_redir(ast, minishell);
			else if (ast->token == CMD)
				ft_exec_cmd(ast, minishell);
			else
			{
				ft_fail(ERR_PARSING, NULL);
				minishell->status = STATUS_PROG;
				if (in_fork)
					ft_exit_minishell(minishell, minishell->status);
			}
		}
	}
}

void	ft_exec_line(t_ast *ast, t_minishell *minishell)
{
	int	status;

	if (!ast)
		ft_minishell_input(minishell);
	printf("executing line\n");
	minishell->pipe_before = CMD;
	minishell->last_pid = -1;
	minishell->last_cmd = -1;
	minishell->pipe = -1;
	ft_exec_ast(ast, minishell, false);
	// ft_minishell_input(minishell);
	// ft_exit_minishell(minishell, STATUS_OK);
}


	// waitpid(minishell->last_pid, &status, 0);
	// while (wait(NULL) != -1)
	// 	;
	// exit(WEXITSTATUS(status));