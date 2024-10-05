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

char	**ft_get_path(char *env_path)
{
	char	**paths;

	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (ft_fail(ERR_MALLOC, "no PATH"), NULL);
	return (paths);
}

void	ft_set_shlvl(t_env *env, t_minishell *minishell)
{
	minishell->shlvl = ft_atoi(env->value) + 1;
	if (env->value)
		free(env->value);
	env->value = ft_itoa(minishell->shlvl);
	if (!env->value)
		ft_fail(ERR_MALLOC, "no SHLVL in env");
}

void	ft_set_shell(t_env *env, t_minishell *minishell)
{
	char	*pwd;
	char	*minishell_path;

	if (env->value)
		free(env->value);
	pwd = ft_getcwd(&(minishell->env));
	minishell_path = ft_build_path(pwd, "./minishell", 0);
	if (!minishell_path)
		ft_fail(ERR_MALLOC, "no SHELL in env");
	env->value = minishell_path;
}

void	ft_set_from_env_minishell(t_minishell *minishell)
{
	t_env	*env;
	int		count;

	count = 0;
	env = minishell->env;
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
			minishell->path = ft_get_path(env->value);
		else if (!ft_strcmp(env->name, "SHLVL"))
			ft_set_shlvl(env, minishell);
		else if (!ft_strcmp(env->name, "SHELL"))
			ft_set_shell(env, minishell);
		else
			count --;
		count ++;
		if (count == 3)
			return ;
		env = env->next;
	}
}

int	ft_init_minishell(char **envp)
{
	t_minishell	minishell;

	if (!ft_token_good())
		return (ft_fail(ERR_TOKEN, NULL), 1);
	minishell.env = ft_env_of_envp(envp);
	if (!minishell.env)
		ft_fail(ERR_ENV, NULL);
	ft_load_history(&minishell);
	minishell.path = NULL;
	minishell.shlvl = 1;
	ft_set_from_env_minishell(&minishell);
	minishell.status = STATUS_OK;
	minishell.parsing_status = STATUS_OK;
	ft_print_banner();
	ft_minishell_input(&minishell);
	return (0);
}
