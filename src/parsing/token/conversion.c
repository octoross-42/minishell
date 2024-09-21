/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:49:29 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 19:49:53 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_str_of_token(int token)
{
	if (token == PIPE)
		return ("PIPE");
	if (token == OR)
		return ("OR");
	if (token == AND)
		return ("AND");
	if (token == INPUT)
		return ("INPUT");
	if (token == OUTPUT)
		return ("OUTPUT");
	if (token == HERE_DOC)
		return ("HERE_DOC");
	if (token == APPEND)
		return ("APPEND");
	if (token == CMD)
		return ("CMD");
	else
		return (NULL);
}

int	ft_token_of_str(char *token)
{
	if (!ft_strcmp(token, "PIPE"))
		return (PIPE);
	if (!ft_strcmp(token, "OR"))
		return (OR);
	if (!ft_strcmp(token, "AND"))
		return (AND);
	if (!ft_strcmp(token, "INPUT"))
		return (INPUT);
	if (!ft_strcmp(token, "OUTPUT"))
		return (OUTPUT);
	if (!ft_strcmp(token, "HERE_DOC"))
		return (HERE_DOC);
	if (!ft_strcmp(token, "APPEND"))
		return (APPEND);
	if (!ft_strcmp(token, "CMD"))
		return (CMD);
	else
		return (0);
}
