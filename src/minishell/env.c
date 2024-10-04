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

bool	ft_aldeady_in_env(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			free(env->value);
			env->value = value;
			return (true);
		}
		env = env->next;
	}
	return (false);
}

int	ft_add_env(t_env **env, char *name, char *value)
{
	t_env	*new;

	if (!env)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	if (ft_aldeady_in_env(*env, name, value))
		return (free(name), STATUS_OK);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ft_fail(ERR_MALLOC, "no new env"), STATUS_MALLOC);
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
	return (STATUS_OK);
}

char	*ft_get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_expand(t_arg *arg, t_minishell *minishell)
{
	char	*value;

	if (!arg || !arg->expand || !(arg->str))
		return ;
	if (!ft_strcmp(arg->str, "?"))
	{
		value = ft_itoa(minishell->status);
		if (!value)
			ft_fail(ERR_EXPAND, arg->str);
		free(arg->str);
		arg->str = value;
		arg->expand = false;
		return ;
	}
	value = ft_get_env_value(arg->str, minishell->env);
	free(arg->str);
	arg->str = value;
}
