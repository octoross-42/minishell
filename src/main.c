/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 15:52:11 by octoross         ###   ########.fr       */
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

void	ft_exit_minishell(t_minishell *minishell, int status)
{
	ft_free_until((void **)(minishell->path), -1);
	ft_clear_env(minishell->env);
	exit(status);
}

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;
	t_env		*env;

	minishell.env = ft_env_of_envp(envp);
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
