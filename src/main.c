/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/16 20:37:51 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_input(t_minishell *minishell)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fail(ERR_FORK);
		exit(EXIT_FAILURE);
	}
	else if (!pid)
		ft_input_minishell(minishell);
	else
	{
		while (wait(NULL) != -1)
			;
		ft_init_input(minishell);
	}
}

void	ft_init_minishell(char **envp)
{
	t_minishell	minishell;

	minishell.envp = envp;
	ft_init_input(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_print_banner();
	ft_init_minishell(envp);
	return (0);
}
