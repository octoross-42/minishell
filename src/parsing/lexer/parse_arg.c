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

int	ft_len_arg(char *s, t_expand **expand)
{
	int			i;
	int			len;
	t_expand	*last;

	last = NULL;
	len = 0;
	while (*s && !ft_isspace(*s) && !ft_char_is_token(*s))
	{
		i = 1;
		if (*s == '$')
			i = ft_len_expand(&s, expand, &last);
		else if (ft_char_is_quote(*s))
			i = ft_len_quotes(&s, expand, &last);
		else
			s ++;
		if (i < 0)
			return (ft_fail(ERR_MALLOC, NULL), -1);
		len += i;
	}
	return (len);
}

bool	ft_init_parsing_arg(char *s, char **data, t_expand **expand)
{
	int			len;

	len = ft_len_arg(s, expand);
	if (len <= 0)
		return (false);
	*data = (char *)malloc((len + 1) * sizeof(char));
	if (!(*data))
		return (ft_fail(ERR_MALLOC, NULL), false);
	(*data)[len] = '\0';
	return (true);
}

bool	ft_parse_arg(char **s, char **data)
{
	int			i;
	int			j;
	t_expand	*expand;

	expand = NULL;
	if (!ft_init_parsing_arg(*s, data, &expand))
		return (ft_clear_expand(expand), false);
	i = 0;
	while (**s && !ft_isspace(**s) && !ft_char_is_token(**s))
	{
		j = 0;
		if (**s == '$')
			j = ft_expand_arg(s, &((*data)[i]), &expand);
		else if (ft_char_is_quote(**s))
			j = ft_close_quotes(s, &((*data)[i]), &expand);
		else
			(*data)[i ++] = *((*s)++);
		if (j < 0)
			return (false);
		i += j;
	}
	return (true);
}
