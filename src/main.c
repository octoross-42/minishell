/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 19:08:55 by octoross         ###   ########.fr       */
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

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;

	minishell.envp = envp;
	minishell.status = STATUS_OK;
	minishell.path = ft_get_path(envp);
	minishell.ast = NULL;
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
