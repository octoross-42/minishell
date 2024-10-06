/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:37:18 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 19:37:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_minishell(t_minishell *minishell)
{
	t_pid	*next;

	while (minishell->wait_for_pids)
	{
		next = minishell->wait_for_pids->next;
		free(minishell->wait_for_pids);
		minishell->wait_for_pids = next;
	}
	ft_free_until((void **)(minishell->path), -1);
	minishell->path = NULL;
	ft_clear_env(minishell->env);
	minishell->env = NULL;
	if (minishell->history >= 0)
		close(minishell->history);
}

void	ft_exit_minishell(t_minishell *minishell, int status)
{
	ft_clear_minishell(minishell);
	ft_reset_stds(minishell);
	exit(status);
}

void	ft_change_shlvl(t_minishell *minishell)
{
	t_env	*env;
	char	*shlvl_str;
	char	*str;

	(minishell->shlvl)++;
	env = minishell->env;
	shlvl_str = ft_itoa(minishell->shlvl);
	if (!shlvl_str)
	{
		ft_fail(ERR_MALLOC, "shlvl didnt change in PATH");
		return ;
	}
	str = ft_strdup("SHLVL");
	if (!str)
	{
		ft_fail(ERR_MALLOC, "shlvl didnt change in PATH");
		return ;
	}
	ft_add_env(&(minishell->env), str, shlvl_str);
}
