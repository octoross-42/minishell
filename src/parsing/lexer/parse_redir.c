/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:59:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 21:59:08 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
