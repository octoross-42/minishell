/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 01:52:22 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path(t_env *env)
{
	int		i;
	char	*path;
	char	**paths;

	if (!env)
		return (NULL);
	i = 0;
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

void	ft_exit_minishell(t_minishell *minishell, int status)
{
	ft_free_until((void **)(minishell->path), -1);
	ft_clear_env(minishell->env);
	exit(status);
}

t_env	*ft_env_of(char **envp)
{
	t_env	*env;
	t_env	*last;
	t_env	*new;
	int		i;
	int		j;

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
		if (!env)
			env = new;
		else
			last->next = new;
		last = new;
		last->next = NULL;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (!envp[i][j])
			return (ft_fail(ERR_PARSING_ENV, NULL), ft_clear_env(env), NULL);
		last->name = ft_strndup(envp[i], j ++);
		if (!last->name)
			return (ft_fail(ERR_MALLOC, NULL), ft_clear_env(env), NULL);
		last->value = ft_strdup(envp[i] + j);
		if (!last->value)
			return (ft_fail(ERR_MALLOC, NULL), ft_clear_env(env), NULL);
		i++;
	}
	return (env);
}

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;
	t_env		*env;

	minishell.env = ft_env_of(envp);
	if (!minishell.env)
		ft_fail(ERR_ENV, NULL);
	// else
	// {
	// 	env = minishell.env;
	// 	while (env)
	// 	{
	// 		printf("%s=\"%s\"\n", env->name, env->value);
	// 		env = env->next;
	// 	} 
	// }
	minishell.status = STATUS_OK;
	minishell.parsing_status = STATUS_OK;
	minishell.path = ft_get_path(minishell.env);
	ft_minishell_input(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_print_banner();
	ft_init_minishell(envp);
	return (0);
}
