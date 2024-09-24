/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/24 22:44:24 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (ft_fail(ERR_PATH, NULL), NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (ft_fail(ERR_PATH, NULL), NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void	ft_exit_minishell(t_minishell *minishell, int status)
{
	ft_free_until((void **)(minishell->path), -1);
	ft_clear_ast(minishell->ast);
	exit(status);
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
}

t_env	*ft_env_of(char **envp)
{
	t_env	*env;
	t_env	*last;
	t_env	*new;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
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
		if (last)
			last->next = new;
		last = new;
		last->next = NULL;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (!envp[i][j])
			return (ft_clear_env(env), NULL);
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

	minishell.env = ft_env_of(envp);
	if (!minishell.env)
		ft_fail(ERR_ENV, NULL);
	minishell.status = STATUS_OK;
	minishell.parsing_status = STATUS_OK;
	minishell.path = ft_get_path(envp);
	minishell.ast = NULL;
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
