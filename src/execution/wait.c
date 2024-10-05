/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:39:46 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 12:39:46 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pid_to_wait(pid_t pid, t_minishell *minishell)
{
	t_pid	*new;

	new = (t_pid *)malloc(sizeof(t_pid));
	if (!new)
		ft_fail(ERR_MALLOC, "cannot wait for pipe");
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

void	ft_waitpid(pid_t pid, t_minishell *minishell, \
	bool register_status)
{
	int	status;

	waitpid(pid, &status, 0);
	if (register_status)
	{
		minishell->status = WEXITSTATUS(status);
	}
}
