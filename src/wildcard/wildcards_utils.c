/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:41:03 by octoross          #+#    #+#             */
/*   Updated: 2024/09/29 16:41:03 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

bool	ft_add_wildcards(char **argv, t_wildcards **wildcards, t_wildcards **last)
{
	t_wildcards	*new;

	new = (t_wildcards *)malloc(sizeof(t_wildcards));
	if (!new)
		return (ft_fail(ERR_MALLOC, "no arg"), false);
	new->next = NULL;
	new->files = argv;
	if (*wildcards)
		(*last)->next = new;
	else
		*wildcards = new;
	*last = new;
	return (true);
}

void	ft_clear_wildcards(t_wildcards *wildcards)
{
	if (!wildcards)
		return ;
	ft_clear_wildcards(wildcards->next);
	if (wildcards->files)
		ft_free_until((void **)wildcards->files, -1);
	free(wildcards);
}
