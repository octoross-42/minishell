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

int	ft_add_new_arg(t_arg **last, t_arg **top)
{
	t_arg	*new;

	if (!last || !top)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
	{
		ft_clear_arg(*top);
		return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
	}
	new->str = NULL;
	new->next = NULL;
	new->wildcard = false;
	new->expand = false;
	new->previous = *last;
	if (*last && (*last)->wildcard)
		new->wildcard = true;
	if (!(*top))
		*top = new;
	if (*last)
		(*last)->next = new;
	*last = new;
	return (STATUS_OK);
}

int	ft_len_t_arg(char *s, char quote, int *status)
{
	int	len;
	int	len_quotes;

	len = 0;
	*status = STATUS_OK;
	while (*s && !ft_isspace(*s) && !ft_char_is_token(*s))
	{	
		if ((*s == '$') && (ft_isname(*(s + 1)) || (*(s + 1) == '?')) && (quote != '\''))
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

int	ft_fill_arg(char **s, t_arg *arg, char *quote)
{
	int		i;
	int		status;
	char	*str;
	t_arg	*previous;

	str = arg->str;
	while (**s && !ft_isspace(**s) && !ft_char_is_token(**s))
	{	
		if ((**s == '$') && (ft_isname(*(*s + 1)) || (*(*s + 1) == '?')) && (*quote != '\''))
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
		if (**s == '*' && (!*quote))
		{
			if (!arg->wildcard)
			{
				previous = arg;
				while (previous)
				{
					previous->wildcard = true;
					previous = previous->previous;
				}

			}
		}
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
	if ((**s == '$') && (ft_isname(*(*s + 1)) || (*(*s + 1) == '?')) && (*quote != '\''))
		return (ft_arg_expand(s, arg));
	else
	{
		len = ft_len_t_arg(*s, *quote, &status);
		if (len < 0)
			return (status);
		arg->str = (char *)malloc((len + 1) * sizeof(char));
		if (!arg->str)
			return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
		arg->str[len] = 0;
		status = ft_fill_arg(s, arg, quote);
		if (status != STATUS_OK)
			return (status);
	}
}

void	ft_clear_arg(t_arg *arg)
{
	if (!arg)
		return ;
	if (arg->next)
		ft_clear_arg(arg->next);
	if (arg->str)
		free(arg->str);
	free(arg);
}

void	ft_clear_args(t_arg **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (!(args[i]))
	{
		free(args);
		return ;
	}
	while (args[i])
		ft_clear_arg(args[i ++]);
	free(args);
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

int	ft_parse_redir(char **s, t_lexer *lexer)
{
	t_arg	*file;
	int		status;

	while (ft_isspace(**s))
		(*s)++;
	if (!(**s))
		return (ft_fail(ERR_SYNTAX, "newline"), STATUS_SYNTAX);
	else if (ft_char_is_token(**s))
	{
		ft_fail(ERR_SYNTAX, ft_str_of_token(ft_get_next_token(*s)));
		return (STATUS_SYNTAX);
	}
	file = NULL;
	status = ft_parse_arg(s, &file);
	if (status != STATUS_OK)
		return (status);
	lexer->data = (void *)file;
	return (STATUS_OK);
}
