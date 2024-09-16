/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/16 17:34:22 by octoross         ###   ########.fr       */
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
		ft_input_minishell();
	else
	{
		wait(NULL);
		if (!minishell->exit)
			ft_init_input(minishell);
	}
}

void	ft_init_minishell(void)
{
	t_minishell	minishell;

	minishell.exit = false;
	ft_init_input(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_print_banner();
	ft_init_minishell();
}
