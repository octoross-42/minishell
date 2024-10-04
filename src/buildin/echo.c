/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:14 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 15:54:42 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_optn_echo(char ***arg)
{
	int		j;
	bool	opt_n;

	opt_n = false;
	while (**arg)
	{
		j = 0;
		while ((**arg)[j ++] == 'n')
			opt_n = true;
		if ((**arg)[j] != '\0')
			(*arg)++;
		else
			return (opt_n);
	}
	return (opt_n);
}

void	print_echo(char **arg)
{
	bool	opt_n;

	if (!arg[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	opt_n = ft_optn_echo(&arg);
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
