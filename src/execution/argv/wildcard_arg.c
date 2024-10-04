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

#include "minishell.h"

void	ft_clear_wildcard_arg(t_wildcard_arg *wildcards)
{
	if (!wildcards)
		return ;
	ft_clear_wildcard_arg(wildcards->next);
	if (wildcards->data && wildcards->is_single)
		free((char *)wildcards->data);
	else if (wildcards->data)
		ft_clear_wildcard((t_wildcard *)wildcards->data);
	free(wildcards);
}

t_wildcard_arg	*ft_init_wildcard_arg(char *arg)
{
	t_wildcard_arg	*wildcard_arg;

	wildcard_arg = (t_wildcard_arg *)malloc(sizeof(t_wildcard_arg));
	if (!wildcard_arg)
		return (free(arg), ft_fail(ERR_MALLOC, "no arg"), NULL);
	wildcard_arg->next = NULL;
	wildcard_arg->is_single = false;
	return (wildcard_arg);
}

t_wildcard_arg	*ft_wilcard_arg(char *arg)
{
	t_wildcard_arg	*wildcard_arg;
	t_wildcard		*wildcard;

	wildcard_arg = ft_init_wildcard_arg(arg);
	if (!wildcard_arg)
		return (NULL);
	wildcard = ft_wildcard(arg, NULL);
	if (!wildcard)
	{
		wildcard_arg->is_single = true;
		wildcard_arg->data = (void *)arg;
	}
	else
	{
		free(arg);
		if (wildcard->next)
			wildcard_arg->data = (void *)wildcard;
		else
		{
			wildcard_arg->is_single = true;
			wildcard_arg->data = (void *)wildcard->file;
			free(wildcard);
		}
	}
	return (wildcard_arg);
}

int	ft_wildcard_len(t_wildcard *list)
{
	int		len;

	len = 0;
	while (list)
	{
		len ++;
		list = list->next;
	}
	return (len);
}

int	ft_add_new_wildcard_arg(t_arg *data, t_minishell *minishell, \
	t_wildcard_arg **wildcards, t_wildcard_arg **last)
{
	t_wildcard_arg	*new;
	char			*arg;

	arg = ft_arg_of(data, minishell);
	if (!arg)
	{
		minishell->status = STATUS_MALLOC;
		ft_clear_wildcard_arg(*wildcards);
		return (-1);
	}
	new = ft_wilcard_arg(arg);
	if (!new)
	{
		minishell->status = STATUS_MALLOC;
		ft_clear_wildcard_arg(*wildcards);
		return (-1);
	}
	if (*wildcards)
		(*last)->next = new;
	else
		*wildcards = new;
	*last = new;
	if (new->is_single)
		return (1);
	return (ft_wildcard_len((t_wildcard *)(new->data)));
}
