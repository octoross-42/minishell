/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:46:03 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 17:29:05 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_next_is_token(char *s)
{
	if (!s || !(*s))
		return (false);
	return ((*s == '(') || (*s == ')')
		|| (*s == '<') || (*s == '>')
		|| ((*s == '|'))
		|| ((*s == '&') && (*(s + 1) == '&')));
}

bool	ft_is_separator(int token)
{
	return ((token == OR) || (token == AND) || (token == PIPE));
}

bool	ft_is_sep_or_sub(int token)
{
	return ((token == SUBSHELL) || (token == END_SUBSHELL)
		|| ft_is_separator(token));
}

bool	ft_is_output(int token)
{
	return ((token == OUTPUT) || (token == APPEND));
}

bool	ft_is_redir(int token)
{
	return ((token == INPUT) || (token == HERE_DOC)
		|| ft_is_output(token));
}
