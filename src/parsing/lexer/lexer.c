/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:38 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 00:15:51 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_clear_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if ((lexer)->next)
		ft_clear_lexer(lexer->next);
	if (lexer->token == CMD)
		ft_free_until((void **)lexer->data, -1);
	else if (ft_is_redir(lexer->token))
		free(lexer->data);
	free(lexer);
}

bool	ft_parse_redir(char **s, t_lexer *lexer)
{
	char	*file;

	if ((lexer->token == INPUT) || (lexer->token == OUTPUT))
		(*s)++;
	else if ((lexer->token == HERE_DOC) || (lexer->token == APPEND))
		*s += 2;
	else
		return (ft_fail(ERR_PROG, NULL), false);
	while (ft_isspace(**s))
		(*s)++;
	file = NULL;
	if (!ft_parse_arg(s, &file))
		return (ft_fail(ERR_SYNTAX, *s), false);
	lexer->data = (void *)file;
	return (true);
}

static bool	ft_set_lexer(char **s, t_lexer *lexer)
{
	if (!ft_strncmp(*s, "||", 2))
		return (lexer->token = OR, *s = *s + 2, true);
	else if (!ft_strncmp(*s, "&&", 2))
		return (lexer->token = AND, *s = *s + 2, true);
	else if (!ft_strncmp(*s, "|", 1))
		return (lexer->token = PIPE, *s = *s + 1, true);
	else if (!ft_strncmp(*s, "<<", 2))
		return (lexer->token = HERE_DOC, ft_parse_redir(s, lexer));
	else if (!ft_strncmp(*s, ">>", 2))
		return (lexer->token = APPEND, ft_parse_redir(s, lexer));
	else if (!ft_strncmp(*s, "<", 1))
		return (lexer->token = INPUT, ft_parse_redir(s, lexer));
	else if (!ft_strncmp(*s, ">", 1))
		return (lexer->token = OUTPUT, ft_parse_redir(s, lexer));
	else
		return (ft_parse_cmd(s, lexer));
}

bool	ft_add_lexer(t_lexer **top, t_lexer **last)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (ft_clear_lexer(*top), ft_fail(ERR_MALLOC, NULL), false);
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

bool	ft_is_compatible(t_lexer *l1, t_lexer *l2)
{
	if (!l2 || !l1)
		return (true);
	if ((l1->token == CMD) && (l2->token == CMD))
		return (ft_fail(ERR_PROG, NULL), false);
	else if ((l1->token == CMD) || (l2->token == CMD))
		return (true);
	else if (ft_is_fork(l1->token) && ft_is_fork(l2->token))
		return (ft_fail(ERR_SYNTAX, ft_str_of_token(l2->token)), false);
	else
		return (true);
}

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*top;
	t_lexer	*lexer;

	lexer = NULL;
	top = NULL;
	while (line && line[0])
	{
		while (ft_isspace(*line))
			line ++;
		if (!line[0])
			return (top);
		if (!ft_add_lexer(&top, &lexer))
			return (NULL);
		if (!ft_set_lexer(&line, lexer))
			return (ft_clear_lexer(top), NULL);
		if (!ft_is_compatible(lexer, lexer->previous))
			return (ft_clear_lexer(top), NULL);
	}
	return (top);
}

#include "dev.h"

int	main(int ac, char **av)
{
	t_lexer	*lexer;

	if (ac != 2)
		return (1);
	lexer = ft_lexer(av[1]);
	if (!lexer)
		return (1);
	print_lexer(lexer);
	ft_clear_lexer(lexer);
	return (0);
}
