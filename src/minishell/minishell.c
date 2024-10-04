/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:54:18 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 21:54:18 by octoross         ###   ########.fr       */
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
	ft_clear_env(minishell->env);
}

void	ft_exit_minishell(t_minishell *minishell, int status)
{
	ft_clear_minishell(minishell);
	ft_reset_stds(minishell);
	exit(status);
}

char	**ft_get_path(t_env *env)
{
	char	**paths;

	if (!env)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
		{
			paths = ft_split(env->value, ':');
			if (!paths)
				return (ft_fail(ERR_PATH, NULL), NULL);
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

bool	ft_token_good(void)
{
	if ((PIPE == OR) || (PIPE == AND) || (PIPE == SUBSHELL)
		|| (PIPE == INPUT) || (PIPE == OUTPUT) || (PIPE == APPEND)
		|| (PIPE == HERE_DOC) || (PIPE == CMD))
		return (false);
	if ((OR == AND) || (OR == SUBSHELL)
		|| (OR == INPUT) || (OR == OUTPUT) || (OR == APPEND)
		|| (OR == HERE_DOC) || (OR == CMD))
		return (false);
	if ((AND == SUBSHELL)
		|| (AND == INPUT) || (AND == OUTPUT) || (AND == APPEND)
		|| (AND == HERE_DOC) || (AND == CMD))
		return (false);
	if ((SUBSHELL == INPUT) || (SUBSHELL == OUTPUT) || (SUBSHELL == APPEND)
		|| (SUBSHELL == HERE_DOC) || (SUBSHELL == CMD))
		return (false);
	if ((INPUT == OUTPUT) || (INPUT == APPEND) || (INPUT == HERE_DOC)
		|| (INPUT == CMD))
		return (false);
	if ((OUTPUT == APPEND) || (OUTPUT == HERE_DOC) || (OUTPUT == CMD))
		return (false);
	if ((APPEND == HERE_DOC) || (APPEND == CMD))
		return (false);
	return (HERE_DOC != CMD);
}

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;

	if (!ft_token_good())
		ft_fail(ERR_TOKEN, NULL);
	minishell.env = ft_env_of_envp(envp);
	if (!minishell.env)
		ft_fail(ERR_ENV, NULL);
	minishell.status = STATUS_OK;
	minishell.parsing_status = STATUS_OK;
	minishell.path = ft_get_path(minishell.env);
	ft_minishell_input(&minishell);
}
