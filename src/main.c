/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:11 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 19:30:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_token_good(void)
{
	if ((PIPE == OR) || (PIPE == AND) || (PIPE == SUBSHELL)
		|| (PIPE == INPUT) || (PIPE == OUTPUT) || (PIPE == APPEND)
		|| (PIPE == HERE_DOC) || (PIPE == CMD))
		return (false);
	if ((OR == AND) || (OR == SUBSHELL)
		|| (OR == INPUT) || (OR == OUTPUT) || (OR == APPEND)
		|| (OR == HERE_DOC) || (OR == CMD))
		return (false);
	if ((AND == SUBSHELL)
		|| (AND == INPUT) || (AND == OUTPUT) || (AND == APPEND)
		|| (AND == HERE_DOC) || (AND == CMD))
		return (false);
	if ((SUBSHELL == INPUT) || (SUBSHELL == OUTPUT) || (SUBSHELL == APPEND)
		|| (SUBSHELL == HERE_DOC) || (SUBSHELL == CMD))
		return (false);
	if ((INPUT == OUTPUT) || (INPUT == APPEND) || (INPUT == HERE_DOC)
		|| (INPUT == CMD))
		return (false);
	if ((OUTPUT == APPEND) || (OUTPUT == HERE_DOC) || (OUTPUT == CMD))
		return (false);
	if ((APPEND == HERE_DOC) || (APPEND == CMD))
		return (false);
	return (HERE_DOC != CMD);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_init_minishell(envp);
	return (0);
}
