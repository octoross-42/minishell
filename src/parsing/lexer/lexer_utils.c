/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:28:19 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 22:28:19 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_clear_lexer(t_lexer *lexer, int erase_data)
{
	if (!lexer)
		return ;
	if (lexer->next)
		ft_clear_lexer(lexer->next, erase_data);
	if (erase_data)
	{
		if (lexer->token == CMD)
			ft_clear_args((t_arg **)(lexer->data), -1);
		else if (ft_is_redir(lexer->token))
			ft_clear_arg((t_arg *)lexer->data);
	}
	free(lexer);
}

bool	ft_add_lexer(t_lexer **top, t_lexer **last)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
	{
		ft_clear_lexer(*top, 1);
		ft_fail(ERR_MALLOC, "no parsing");
		return (false);
	}
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
