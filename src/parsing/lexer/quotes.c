/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:02:11 by octoross          #+#    #+#             */
/*   Updated: 2024/09/19 18:02:11 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_char_is_quote(char c)
{
	return ((c == '\'') || (c == '"'));
}

int	ft_len_quotes(char **s, char *quote)
{
	int	len;

	*quote = **s;
	(*s)++;
	len = 0;
	while (**s)
	{
		if ((**s == '$') && (ft_isname(*(*s + 1)) || (*(*s + 1) == '?')) && (*quote != '\''))
			return ((*s)--, len);
		else if (**s == *quote)
			return (*quote = 0, len);
		else
			len ++;
		(*s)++;
	}
	return (ft_fail(ERR_SYNTAX, "newline"), -1);
}

int	ft_close_quotes(char **s, char *data, char *quote)
{
	int	len;

	*quote = **s;
	(*s)++;
	len = 0;
	while (**s)
	{	
		if ((**s == '$') && (ft_isname(*(*s + 1)) || (*(*s + 1) == '?')) && (*quote != '\''))
			return ((*s)--, len);
		else if (**s == *quote)
			return (*quote = 0, len);
		else
			data[len ++] = **s;
		(*s)++;
	}
	return (ft_fail(ERR_SYNTAX, "newline"), -1);
}
