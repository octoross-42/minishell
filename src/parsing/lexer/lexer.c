/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:38 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 01:12:05 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_set_lexer(char **s, t_lexer **lexer)
{
	(*lexer)->token = ft_get_next_token(*s);
	if (((*lexer)->token == OR) || ((*lexer)->token == AND))
		return (*s = *s + 2, STATUS_OK);
	else if ((*lexer)->token == PIPE)
		return (*s = *s + 1, STATUS_OK);
	else if ((*lexer)->token == CMD)
		return (ft_parse_cmd(s, *lexer));
	else if (((*lexer)->token == INPUT) || ((*lexer)->token == OUTPUT))
		return ((*s)++, ft_parse_redir(s, *lexer));
	else if (((*lexer)->token == HERE_DOC) || ((*lexer)->token == APPEND))
		return (*s += 2), ft_parse_redir(s, *lexer);
	else if ((*lexer)->token == SUBSHELL)
		return ((*s)++, ft_parse_subshell(s, lexer));
	else if ((*lexer)->token == END_SUBSHELL)
		return ((*s)++, (*lexer)->data = *s, STATUS_OK);
	else
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
}

int	ft_is_compatible(t_lexer *l, t_lexer *previous, bool subshell)
{
	if (!l)
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	if (!subshell && (l->token == END_SUBSHELL) && ((char *)(l->data)))
		return (ft_fail(ERR_SYNTAX, ")"), STATUS_SYNTAX);
	if (!previous && (ft_is_separator(l->token) || (l->token == END_SUBSHELL)))
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(l->token)), STATUS_SYNTAX);
	if (!previous)
		return (STATUS_OK);
	if ((previous->token == END_SUBSHELL) && (l->token == CMD))
		return (ft_fail(ERR_SYNTAX, (((t_arg **)(l->data))[0])->str), STATUS_SYNTAX);
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

t_lexer	*ft_end_lexer(t_lexer *top, t_lexer *lexer, int *status, bool subshell)
{
	if (lexer && (ft_is_separator(lexer->token)
		|| ((lexer->token != END_SUBSHELL) && subshell)
		|| (lexer->token == SUBSHELL)))
	{
		ft_fail(ERR_SYNTAX, "newline");
		ft_clear_lexer(top, 1);
		*status = STATUS_SYNTAX;
		return (NULL);
	}
	return (top);
}

#include "dev.h"

t_lexer	*ft_lexer(char *line, int *status, bool subshell)
{
	t_lexer	*top;
	t_lexer	*lexer;

	lexer = NULL;
	top = NULL;
	*status = STATUS_OK;
	while (line && line[0])
	{
		while (ft_isspace(*line))
			line ++;
		if (!line[0])
			return (top);
		if (!ft_add_lexer(&top, &lexer))
			return (*status = STATUS_MALLOC, NULL);
		*status = ft_set_lexer(&line, &lexer);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
		*status = ft_is_compatible(lexer, lexer->previous, subshell);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
		if ((lexer->token == END_SUBSHELL) && subshell)
			return (top);
	}
	return (ft_end_lexer(top, lexer, status, subshell));
}

// #include "dev.h"

// int	main(int ac, char **av)
// {
// 	t_lexer	*lexer;

// 	if (ac != 2)
// 		return (1);
// 	lexer = ft_lexer(av[1]);
// 	if (!lexer)
// 		return (1);
// 	print_lexer(lexer);
// 	ft_clear_lexer(lexer);
// 	return (0);
// }
