/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:04:18 by octoross          #+#    #+#             */
/*   Updated: 2024/09/19 18:04:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_len_t_arg(char *s, char quote, int *status)
{
	int	len;
	int	len_quotes;

	len = 0;
	*status = STATUS_OK;
	while (*s && !ft_isspace(*s) && !ft_char_is_token(*s))
	{
		if (ft_is_expand(*s, *(s + 1), quote))
			return (len);
		else if ((*s == '$') && ft_char_is_quote(*(s + 1)) && !quote)
			;
		else if (ft_char_is_quote(*s) && !quote)
		{
			len_quotes = ft_len_quotes(&s, &quote);
			if (len_quotes < 0)
				return (*status = STATUS_SYNTAX, -1);
			len += len_quotes;
		}
		else if (*s == quote)
			quote = 0;
		else
			len ++;
		s ++;
	}
	return (len);
}

void	ft_arg_is_wildcard(char c, char quote, t_arg *arg)
{
	t_arg	*previous;

	if (c == '*' && !quote)
	{
		if (arg->wildcard)
			return ;
		previous = arg;
		while (previous && !(previous->wildcard))
		{
			previous->wildcard = true;
			previous = previous->previous;
		}
	}
}

int	ft_fill_arg(char **s, t_arg *arg, char *quote)
{
	int		i;
	char	*str;

	str = arg->str;
	while (**s && !ft_isspace(**s) && !ft_char_is_token(**s))
	{
		if (ft_is_expand(**s, *(*s + 1), *quote))
			return (STATUS_OK);
		else if ((**s == '$') && ft_char_is_quote(*(*s + 1)) && !(*quote))
			;
		else if (ft_char_is_quote(**s) && !(*quote))
		{
			i = ft_close_quotes(s, str, quote);
			if (i < 0)
				return (STATUS_SYNTAX);
			str += i;
		}
		else if (**s == *quote)
			*quote = 0;
		else
			*(str ++) = **s;
		ft_arg_is_wildcard(**s, *quote, arg);
		(*s)++;
	}
	return (STATUS_OK);
}

int	ft_set_arg(char **s, t_arg *arg, char *quote)
{
	int	status;
	int	len;

	status = STATUS_OK;
	if ((**s == '$') && ft_char_is_quote(*(*s + 1)) && !(*quote))
		(*s)++;
	if (ft_is_expand(**s, *(*s + 1), *quote))
		return (ft_arg_expand(s, arg));
	else
	{
		len = ft_len_t_arg(*s, *quote, &status);
		if (len < 0)
			return (status);
		arg->str = (char *)malloc((len + 1) * sizeof(char));
		if (!arg->str)
			return (ft_fail(ERR_MALLOC, "no parsing"), STATUS_MALLOC);
		arg->str[len] = 0;
		status = ft_fill_arg(s, arg, quote);
		if (status != STATUS_OK)
			return (status);
	}
	return (status);
}

int	ft_parse_arg(char **s, t_arg **data)
{
	int			status;
	t_arg		*last;
	char		quote;

	*data = NULL;
	last = NULL;
	quote = 0;
	while (**s && !ft_isspace(**s) && !ft_char_is_token(**s))
	{
		status = ft_add_new_arg(&last, data);
		if (status != STATUS_OK)
			return (status);
		status = ft_set_arg(s, last, &quote);
		if (status != STATUS_OK)
			return (status);
	}
	if (quote)
		return (ft_fail(ERR_SYNTAX, "newline"), STATUS_SYNTAX);
	return (STATUS_OK);
}
