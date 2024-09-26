/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:45:42 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 15:45:42 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_env(t_env *env)
{
	if (!env)
		return ;
	if (env->next)
		ft_clear_env(env->next);
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}

static void	ft_fill_env_from_envp(t_env *env, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] != '=')
	{
		ft_fail(ERR_PARSING_ENV, NULL);
		ft_clear_env(env);
		return ;
	}
	env->name = ft_strndup(envp, i ++);
	if (!env->name)
	{
		ft_fail(ERR_MALLOC, NULL);
		ft_clear_env(env);
		return ;
	}
	env->value = ft_strdup(envp + i);
	if (!env->value)
	{
		ft_fail(ERR_MALLOC, NULL);
		ft_clear_env(env);
		return ;
	}
}

int	ft_add_env(t_env **env, char *name, char *value)
{
	t_env *new;

	if (!env)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
	new->next = NULL;
	new->previous = new;
	new->name = name;
	new->value = value;
	if (!(*env))
		*env = new;
	else
	{
		new->previous = (*env)->previous;
		(*env)->previous->next = new;
		(*env)->previous = new;
	}
}

t_env	*ft_env_of_envp(char **envp)
{
	t_env	*env;
	t_env	*last;
	t_env	*new;
	int		i;

	if (!envp)
		return (ft_fail(ERR_ENV, NULL), NULL);
	env = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (ft_fail(ERR_MALLOC, NULL), ft_clear_env(env), NULL);
		new->previous = last;
		if (!env)
			env = new;
		else
			last->next = new;
		last = new;
		last->next = NULL;
		ft_fill_env_from_envp(last, envp[i ++]);
	}
	return (env->previous = last, env);
}
