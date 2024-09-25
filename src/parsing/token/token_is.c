/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:46:03 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 13:59:35 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_char_is_token(char c)
{
	return ((c == '<') || (c == '>') || (c == '|') || (c == '&'));
}

bool	ft_is_fork(int token)
{
	return ((token == PIPE));
}

bool	ft_is_separator(int token)
{
	return ((token == OR) || (token == AND) || ft_is_fork(token));
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
