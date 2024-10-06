/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:31:18 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 17:31:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*ft_get_cmd_before_redirs(t_lexer *lexer)
{
	if (lexer->token != CMD)
		return (NULL);
	lexer = lexer->previous;
	if (!ft_is_redir(lexer->token))
		return (NULL);
	while (lexer && ft_is_redir(lexer->token))
		lexer = lexer->previous;
	if (!lexer)
		return (NULL);
	if (lexer->token == CMD)
		return (lexer);
	return (NULL);
}

void	ft_fill_merge_cmds(t_arg **merged, t_arg **cmd1, t_arg **cmd2)
{
	int	i;
	int	j;

	i = 0;
	while (cmd1[i])
	{
		merged[i] = cmd1[i];
		i++;
	}
	j = 0;
	while (cmd2[j])
	{
		merged[i] = cmd2[j];
		i++;
		j++;
	}
	merged[i] = NULL;
}

int	ft_merge_cmds_between_redir(t_lexer **lexer)
{
	t_lexer	*cmd1;
	t_arg	**merged;
	int		len;
	t_lexer	*prev;

	if (!((*lexer)->previous) || !((*lexer)->previous->previous))
		return (STATUS_OK);
	cmd1 = ft_get_cmd_before_redirs(*lexer);
	if (!cmd1)
		return (STATUS_OK);
	len = ft_ptrslen((void **)(cmd1->data)) \
		+ ft_ptrslen((void **)((*lexer)->data));
	merged = (t_arg **)malloc(sizeof(t_arg *) * (len + 1));
	if (!merged)
		return (ft_fail(ERR_MALLOC, "no parsing"), STATUS_MALLOC);
	ft_fill_merge_cmds(merged, \
		(t_arg **)(cmd1->data), (t_arg **)((*lexer)->data));
	free(cmd1->data);
	free((*lexer)->data);
	cmd1->data = (void *)merged;
	prev = (*lexer)->previous;
	free(*lexer);
	prev->next = NULL;
	*lexer = prev;
	return (STATUS_OK);
}
