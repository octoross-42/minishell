/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:18:17 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 21:18:17 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_envp(char **name, char **value, char *envp)
{
	int	i;

	i = 0;
	if (ft_isdigit(envp[i]))
		return (STATUS_EXPORT);
	while (ft_isname(envp[i]) && (envp[i] != '='))
		i ++;
	if (envp[i] && (envp[i] != '=') && !ft_isname(envp[i]))
		return (STATUS_EXPORT);
	*name = ft_strndup(envp, i);
	if (!(*name))
		return (ft_fail(ERR_MALLOC, "no new env"), STATUS_MALLOC);
	if (envp[i] == '=')
	{
		*value = ft_strdup(envp + i + 1);
		if (!(*value))
		{
			free(name);
			ft_fail(ERR_MALLOC, "no new env");
			return (STATUS_MALLOC);
		}
	}
	else
		*value = NULL;
	return (STATUS_OK);
}

bool	ft_new_env_from_envp(t_env **env, char *envp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ft_fail(ERR_MALLOC, "no new env"), false);
	new->next = NULL;
	if (ft_parse_envp(&(new->name), &(new->value), envp) != STATUS_OK)
		return (free(new), false);
	if (!(*env))
	{
		new->previous = new;
		*env = new;
	}
	else
	{
		new->previous = (*env)->previous;
		(*env)->previous->next = new;
		(*env)->previous = new;
	}
	return (true);
}

t_env	*ft_env_of_envp(char **envp)
{
	t_env	*env;
	int		i;

	if (!envp)
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_new_env_from_envp(&env, envp[i++]))
			return (env);
	}
	return (env);
}

bool	ft_fill_envp_from_env(char **envp, t_env *next)
{
	int		len_name;
	int		len_value;

	len_name = ft_strlen(next->name);
	len_value = ft_strlen(next->value);
	(*envp) = (char *)malloc(sizeof(char) * (len_name + len_value + 2));
	if (!(*envp))
	{
		ft_fail(ERR_MALLOC, "no env");
		return (false);
	}
	(*envp)[len_name + len_value + 1] = '\0';
	ft_strcpy(*envp, next->name);
	(*envp)[len_name] = '=';
	ft_strcpy(*envp + len_name + 1, next->value);
	return (true);
}

char	**ft_envp_of_env(t_env *env)
{
	int		len;
	t_env	*next;
	char	**envp;

	len = 0;
	next = env;
	while (next)
	{
		len ++;
		next = next->next;
	}
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (ft_fail(ERR_MALLOC, "no env"), NULL);
	envp[len] = NULL;
	next = env;
	len = 0;
	while (next)
	{
		if (!ft_fill_envp_from_env(&envp[len], next))
			return (ft_free_until((void **)envp, len), NULL);
		next = next->next;
		len ++;
	}
	return (envp);
}
