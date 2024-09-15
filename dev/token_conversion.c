/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:45:24 by octoross          #+#    #+#             */
/*   Updated: 2024/09/15 20:05:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

char	*str_of_token(int token)
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

int	token_of_str(char *token)
{
	if (!strcmp(token, "PIPE"))
		return (PIPE);
	if (!strcmp(token, "OR"))
		return (OR);
	if (!strcmp(token, "AND"))
		return (AND);
	if (!strcmp(token, "INPUT"))
		return (INPUT);
	if (!strcmp(token, "OUTPUT"))
		return (OUTPUT);
	if (!strcmp(token, "HERE_DOC"))
		return (HERE_DOC);
	if (!strcmp(token, "APPEND"))
		return (APPEND);
	if (!strcmp(token, "CMD"))
		return (CMD);
	else
		return (0);
}
