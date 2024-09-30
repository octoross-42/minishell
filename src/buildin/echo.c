/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:14 by octoross          #+#    #+#             */
/*   Updated: 2024/09/30 22:11:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **arg)
{
	bool	opt_n;

	if (!arg[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	opt_n = !ft_strcmp(arg[1], "-n");
	if (opt_n && !arg[2])
		return ;
	else if (opt_n && arg[2])
		arg += 2;
	else
		arg ++;
	while (*arg)
	{
		write(STDOUT_FILENO, *arg, ft_strlen(*arg));
		arg ++;
		if (*arg)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!opt_n)
		write(STDOUT_FILENO, "\n", 1);
}
