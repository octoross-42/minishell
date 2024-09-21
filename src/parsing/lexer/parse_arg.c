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

static int	ft_len_arg(char *s, t_expand **expand, int *status)
{
	int			i;
	int			len;
	t_expand	*last;

	last = NULL;
	len = 0;
	*status = STATUS_OK;
	while (*s && !ft_isspace(*s) && !ft_char_is_token(*s))
	{
		i = 1;
		if (*s == '$')
			i = ft_len_expand(&s, expand, &last, status);
		else if (ft_char_is_quote(*s))
			i = ft_len_quotes(&s, expand, &last, status);
		else
			s ++;
		if (i < 0)
			return (-1);
		len += i;
	}
	return (len);
}

static int	ft_init_parsing_arg(char *s, char **data, t_expand **expand)
{
	int	len;
	int	status;	

	len = ft_len_arg(s, expand, &status);
	if (len <= 0)
		return (status);
	*data = (char *)malloc((len + 1) * sizeof(char));
	if (!(*data))
		return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
	(*data)[len] = '\0';
	return (STATUS_OK);
}

int	ft_parse_arg(char **s, char **data)
{
	int			status;
	int			i;
	int			j;
	t_expand	*expand;

	expand = NULL;
	status = ft_init_parsing_arg(*s, data, &expand);
	if (status != STATUS_OK)
		return (ft_clear_expand(expand), status);
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
			return (STATUS_PROG);
		i += j;
	}
	return (STATUS_OK);
}

int	ft_parse_redir(char **s, t_lexer *lexer)
{
	char	*file;

	if ((lexer->token == INPUT) || (lexer->token == OUTPUT))
		(*s)++;
	else if ((lexer->token == HERE_DOC) || (lexer->token == APPEND))
		*s += 2;
	else
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	while (ft_isspace(**s))
		(*s)++;
	file = NULL;
	if (!ft_parse_arg(s, &file))
		return (ft_fail(ERR_SYNTAX, *s), STATUS_SYNTAX);
	lexer->data = (void *)file;
	return (STATUS_OK);
}
