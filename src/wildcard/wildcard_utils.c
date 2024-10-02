/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:25:01 by octoross          #+#    #+#             */
/*   Updated: 2024/09/29 01:25:01 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_wildcard	*ft_new_wildcard(char *name, char *path, bool dir)
{
	t_wildcard	*new;

	new = (t_wildcard *)malloc(sizeof(t_wildcard));
	if (!new)
		return (ft_fail(ERR_MALLOC, "no wildcard"), NULL);
	if (dir)
		new->file = ft_build_dir_path(path, name);
	else
		new->file = ft_build_path(path, name);
	if (!new->file)
		return (ft_fail(ERR_MALLOC, "no wildcard"), free(new), NULL);
	new->next = NULL;
	new->last = new;
	return (new);
}

void	ft_add_wildcard(t_wildcard **wildcard, t_wildcard *new)
{
	t_wildcard	*tmp;

	if (!new)
		return ;
	if (!(*wildcard))
		*wildcard = new;
	else
	{
		tmp = (*wildcard)->last;
		(*wildcard)->last->next = new;
		(*wildcard)->last = new->last;
		new->last = tmp;
	}
}

void	ft_clear_wildcard(t_wildcard *wildcard)
{
	if (!wildcard)
		return ;
	if (wildcard->next)
		ft_clear_wildcard(wildcard->next);
	if (wildcard->file)
		free(wildcard->file);
	free(wildcard);
}

int	ft_len_wildcard(t_wildcard *wildcard)
{
	int			len;

	len = 0;
	while (wildcard)
	{
		len ++;
		wildcard = wildcard->next;
	}
	return (len);
}
