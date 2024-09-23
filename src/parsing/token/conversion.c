/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:49:29 by octoross          #+#    #+#             */
/*   Updated: 2024/09/23 02:27:23 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_name_of_token(int token)
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
char	*ft_str_of_token(int token)
{
	if (token == PIPE)
		return ("|");
	if (token == OR)
		return ("||");
	if (token == AND)
		return ("&&");
	if (token == INPUT)
		return ("<");
	if (token == OUTPUT)
		return (">");
	if (token == HERE_DOC)
		return ("<<");
	if (token == APPEND)
		return (">>");
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

int	ft_get_next_token(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (OR);
	else if (!ft_strncmp(s, "&&", 2))
		return (AND);
	else if (!ft_strncmp(s, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(s, "<<", 2))
		return (HERE_DOC);
	else if (!ft_strncmp(s, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(s, "<", 1))
		return (INPUT);
	else if (!ft_strncmp(s, ">", 1))
		return (OUTPUT);
	else
		return (CMD);
}
