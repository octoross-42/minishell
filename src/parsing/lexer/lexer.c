/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:38 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 17:49:59 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_set_lexer(char **s, t_lexer *lexer, int *subshell)
{
	lexer->token = ft_get_next_token(*s);
	if ((lexer->token == OR) || (lexer->token == AND))
		return (*s = *s + 2, STATUS_OK);
	else if (lexer->token == PIPE)
		return (*s = *s + 1, STATUS_OK);
	else if (lexer->token == CMD)
		return (ft_parse_cmd(s, lexer));
	else if ((lexer->token == INPUT) || (lexer->token == OUTPUT))
		return ((*s)++, ft_parse_redir(s, lexer));
	else if ((lexer->token == HERE_DOC) || (lexer->token == APPEND))
		return ((*s += 2), ft_parse_redir(s, lexer));
	else if (lexer->token == SUBSHELL)
		return ((*subshell)++, (*s)++, STATUS_OK);
	else if (lexer->token == END_SUBSHELL)
		return ((*subshell)--, (*s)++, STATUS_OK);
	else
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
}

int	ft_is_compatible(t_lexer *l, t_lexer *previous, int subshell)
{
	if (!l)
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	if (subshell < 0)
		return (ft_fail(ERR_SYNTAX, ")"), STATUS_SYNTAX);
	if (!previous && (ft_is_separator(l->token)))
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(l->token)), STATUS_SYNTAX);
	if (!previous)
		return (STATUS_OK);
	if ((previous->token == END_SUBSHELL) && (l->token == CMD))
		return (ft_fail(ERR_SYNTAX, (((t_arg **)(l->data))[0])->str), \
			STATUS_SYNTAX);
	if (!ft_is_separator(previous->token) && (l->token == SUBSHELL))
		return (ft_fail(ERR_SYNTAX, "("), STATUS_SYNTAX);
	if ((l->token == CMD) && (previous->token == CMD))
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	else if ((l->token == CMD) || (previous->token == CMD))
		return (STATUS_OK);
	else if (ft_is_separator(l->token) && ft_is_separator(previous->token))
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(previous->token)),
			STATUS_SYNTAX);
	else
		return (STATUS_OK);
}

t_lexer	*ft_end_lexer(t_lexer *top, t_lexer *lexer, int *status, int subshell)
{
	if (lexer && (ft_is_separator(lexer->token) || (subshell != 0)))
	{
		ft_fail(ERR_SYNTAX, "newline");
		ft_clear_lexer(top, 1);
		*status = STATUS_SYNTAX;
		return (NULL);
	}
	return (top);
}

void	ft_init_lexer(t_lexer **lexer, t_lexer **top, \
	int *subshell, int *status)
{
	*lexer = NULL;
	*top = NULL;
	*subshell = 0;
	*status = STATUS_OK;
}

t_lexer	*ft_lexer(char *line, int *status)
{
	t_lexer	*top;
	t_lexer	*lexer;
	int		subshell;

	ft_init_lexer(&lexer, &top, &subshell, status);
	while (line && line[0])
	{
		while (ft_isspace(*line))
			line ++;
		if (!line[0])
			return (top);
		if (!ft_add_lexer(&top, &lexer))
			return (*status = STATUS_MALLOC, NULL);
		*status = ft_set_lexer(&line, lexer, &subshell);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
		*status = ft_merge_cmds_between_redir(&lexer);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
		*status = ft_is_compatible(lexer, lexer->previous, subshell);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
	}
	return (ft_end_lexer(top, lexer, status, subshell));
}
