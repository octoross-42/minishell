/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:30:07 by octoross          #+#    #+#             */
/*   Updated: 2024/09/17 12:31:09 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_is_fork(int token)
{
	return ((token == PIPE) || (token == OR) || (token == AND));
}

bool	ft_is_output(int token)
{
	return ((token == OUTPUT) || (token == APPEND));
}

bool	ft_is_redir(int token)
{
	return ((token == INTPUT) || (token == HERE_DOC)
		|| ft_is_output(token));
}
