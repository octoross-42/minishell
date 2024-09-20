/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/17 16:24:43 by octoross         ###   ########.fr       */
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
				return (ft_fail(ERR_PATH), NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (ft_fail(ERR_PATH), NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;

	minishell.envp = envp;
	minishell.path = ft_get_path(envp);
	ft_minishell_input(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// int	i = 0;
	// while (envp[i ++])
	// 	printf("envp %d : %s\n", i, envp[i]);
	ft_print_banner();
	ft_init_minishell(envp);
	return (0);
}
