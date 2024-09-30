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

bool	ft_fill_env_from_envp(t_env *env, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] != '=')
		return (ft_fail(ERR_PARSING_ENV, NULL), false);
	env->name = ft_strndup(envp, i ++);
	if (!env->name)
		return (ft_fail(ERR_MALLOC, "no env"), false);
	env->value = ft_strdup(&envp[i]);
	if (!env->value)
		return (ft_fail(ERR_MALLOC, "no env"), false);
	return (true);
}

t_env	*ft_env_of_envp(char **envp)
{
	t_env	*env;
	t_env	*last;
	t_env	*new;
	int		i;

	if (!envp)
		return (NULL);
	env = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (ft_fail(ERR_MALLOC, "no env"), ft_clear_env(env), NULL);
		new->previous = last;
		if (!env)
			env = new;
		else
			last->next = new;
		last = new;
		last->next = NULL;
		if (!ft_fill_env_from_envp(last, envp[i ++]))
			return (ft_clear_env(env), NULL);
	}
	if (env)
		env->previous = last;
	return (env);
}

char **ft_envp_of_env(t_env *env)
{
	int		len;
	int		len_name;
	int		len_value;
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
		len_name = ft_strlen(next->name);
		len_value = ft_strlen(next->value);
		envp[len] = (char *)malloc(sizeof(char) * (len_name + len_value + 2));
		if (!(envp[len]))
			return (ft_fail(ERR_MALLOC, "no env"), ft_free_until((void **)envp, len), NULL);
		envp[len][len_name + len_value + 1] = '\0';
		ft_strcpy(envp[len], next->name);
		envp[len][len_name] = '=';
		ft_strcpy(envp[len] + len_name + 1, next->value);
		next = next->next;
		len ++;
	}
	return (envp);
}
