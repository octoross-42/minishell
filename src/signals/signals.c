/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:58:29 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 02:58:29 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = NO_SIG;

void	ft_input_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = SIG_INT;
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_exec_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIG_INT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_here_doc_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIG_INT;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	ft_setup_signals(void (*ft_handle_sig)(int))
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
