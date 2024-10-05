/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 22:24:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_token_good(void)
{
	int	tokens[10];
	int	i;
	int	j;

	tokens[0] = SUBSHELL;
	tokens[1] = END_SUBSHELL;
	tokens[2] = PIPE;
	tokens[3] = OR;
	tokens[4] = AND;
	tokens[5] = INPUT;
	tokens[6] = HERE_DOC;
	tokens[7] = OUTPUT;
	tokens[8] = APPEND;
	tokens[9] = CMD;
	i = 0;
	while (i < 10)
	{
		j = (i ++) + 1;
		while (j < 10)
		{
			if (tokens[i - 1] == tokens[j ++])
				return (false);
		}
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (ft_init_minishell(envp));
}
