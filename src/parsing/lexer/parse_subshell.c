/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:31:31 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 21:31:31 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "dev.h"

int	ft_parse_subshell(char **s, t_lexer **lexer)
{
	int		status;
	t_lexer	*next;

	if ((*lexer)->previous && !ft_is_separator((*lexer)->previous->token))
		return (ft_fail(ERR_SYNTAX, "("), STATUS_SYNTAX);
	(*lexer)->next = ft_lexer(*s, &status, true);;
	if ((!(*lexer)->next) || (status != STATUS_OK))
	{
		if (status == STATUS_OK)
		{
			ft_fail(ERR_SYNTAX, "newline");
			status = STATUS_SYNTAX;
		}
		return (status);
	}
	if ((*lexer)->next->token == END_SUBSHELL)
		return (ft_fail(ERR_SYNTAX, ")"), STATUS_SYNTAX);
	next = *lexer;
	while (next->next)
		next = next->next;
	if (next->token != END_SUBSHELL)
		return (ft_fail(ERR_SYNTAX, "newline"), STATUS_SYNTAX);
	*s = (char *)(next->data);
	next->data = (char *)NULL;
	*lexer = next;
	return (STATUS_OK);
}
