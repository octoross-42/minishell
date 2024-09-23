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

int	ft_len_quotes(char **s, t_expand **expand, t_expand **last, int *status)
{
	char	quote;
	int		len;
	int		i;

	quote = **s;
	len = 0;
	(*s)++;
	while (**s && (**s != quote))
	{
		i = 1;
		if ((quote != '\'') && (**s == '$'))
		{
			i = ft_len_expand(s, expand, last, status);
			if (i < 0)
				return (-1);
			len += i;
		}
		else
			(*s)++;
		len += i;
	}
	if (**s != quote)
		return (*status = STATUS_SYNTAX, -1);
	(*s)++;
	return (len);
}

int	ft_close_quotes(char **s, char *data, t_expand **expand)
{
	char	quote;
	int		i;
	int		j;

	quote = **s;
	(*s)++;
	i = 0;
	while (**s && (**s != quote))
	{
		if ((quote != '\'') && (**s == '$'))
		{
			j = ft_expand(s, data, expand);
			if (j < 0)
				return (-1);
			i += j;
		}
		else
		{
			data[i ++] = **s;
			(*s)++;
		}
	}
	(*s)++;
	return (i);
}
