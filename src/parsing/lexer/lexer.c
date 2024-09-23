/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:38 by octoross          #+#    #+#             */
/*   Updated: 2024/09/23 17:26:12 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_clear_lexer(t_lexer *lexer, int erase_data)
{
	if (!lexer)
		return ;
	if ((lexer)->next)
		ft_clear_lexer(lexer->next, erase_data);
	if (erase_data)
	{
		if (lexer->token == CMD)
			ft_free_until((void **)lexer->data, -1);
		else if (ft_is_redir(lexer->token))
			free(lexer->data);
	}
	free(lexer);
}

static int	ft_set_lexer(char **s, t_lexer *lexer)
{
	// if (!ft_strncmp(*s, "||", 2))
	// 	return (lexer->token = OR, *s = *s + 2, STATUS_OK);
	// else if (!ft_strncmp(*s, "&&", 2))
	// 	return (lexer->token = AND, *s = *s + 2, STATUS_OK);
	// else if (!ft_strncmp(*s, "|", 1))
	// 	return (lexer->token = PIPE, *s = *s + 1, STATUS_OK);
	// else if (!ft_strncmp(*s, "<<", 2))
	// 	return (lexer->token = HERE_DOC, ft_parse_redir(s, lexer));
	// else if (!ft_strncmp(*s, ">>", 2))
	// 	return (lexer->token = APPEND, ft_parse_redir(s, lexer));
	// else if (!ft_strncmp(*s, "<", 1))
	// 	return (lexer->token = INPUT, ft_parse_redir(s, lexer));
	// else if (!ft_strncmp(*s, ">", 1))
	// 	return (lexer->token = OUTPUT, ft_parse_redir(s, lexer));
	// else
	// 	return (ft_parse_cmd(s, lexer));
	lexer->token = ft_get_next_token(*s);
	if ((lexer->token == OR) || (lexer->token == AND))
		return (*s = *s + 2, STATUS_OK);
	else if (lexer->token == PIPE)
		return (*s = *s + 1, STATUS_OK);
	else if (lexer->token == CMD)
		return ft_parse_cmd(s, lexer);
	else if ((lexer->token == INPUT) || (lexer->token == OUTPUT))
		(*s)++;
	else if ((lexer->token == HERE_DOC) || (lexer->token == APPEND))
		*s += 2;
	else
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	return (ft_parse_redir(s, lexer));
}

bool	ft_add_lexer(t_lexer **top, t_lexer **last)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (ft_clear_lexer(*top, 1), ft_fail(ERR_MALLOC, NULL), false);
	new->data = NULL;
	new->next = NULL;
	new->previous = *last;
	new->token = 0;
	if (!(*top))
		*top = new;
	else
		(*last)->next = new;
	*last = new;
	return (true);
}

int	ft_is_compatible(t_lexer *l, t_lexer *previous)
{
	if (!l)
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	if (ft_is_fork(l->token) && !previous)
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(l->token)), STATUS_SYNTAX);
	if (!previous)
		return (STATUS_OK);
	if ((l->token == CMD) && (previous->token == CMD))
		return (ft_fail(ERR_PARSING, NULL), STATUS_PROG);
	else if ((l->token == CMD) || (previous->token == CMD))
		return (STATUS_OK);
	else if (ft_is_fork(l->token) && ft_is_fork(previous->token))
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(previous->token)), STATUS_SYNTAX);
	else
		return (STATUS_OK);
}
#include "dev.h"

t_lexer	*ft_lexer(char *line, int *status)
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
		*status = ft_set_lexer(&line, lexer);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
		*status = ft_is_compatible(lexer, lexer->previous);
		if (*status != STATUS_OK)
			return (ft_clear_lexer(top, 1), NULL);
	}
	if (lexer && ft_is_fork(lexer->token))
		return (ft_clear_lexer(top, 1), ft_fail(ERR_SYNTAX, "newline"), NULL);
	return (top);
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
