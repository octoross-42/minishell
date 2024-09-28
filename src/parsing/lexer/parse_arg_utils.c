/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:01:09 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 22:01:09 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_clear_arg(t_arg *arg)
{
	if (!arg)
		return ;
	if (arg->next)
		ft_clear_arg(arg->next);
	if (arg->str)
		free(arg->str);
	free(arg);
}

void	ft_clear_args(t_arg **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (!(args[i]))
	{
		free(args);
		return ;
	}
	while (args[i])
		ft_clear_arg(args[i ++]);
	free(args);
}

int	ft_add_new_arg(t_arg **last, t_arg **top)
{
	t_arg	*new;

	if (!last || !top)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
	{
		ft_clear_arg(*top);
		return (ft_fail(ERR_MALLOC, "no parsing"), STATUS_MALLOC);
	}
	new->str = NULL;
	new->next = NULL;
	new->wildcard = false;
	new->expand = false;
	new->previous = *last;
	if (*last && (*last)->wildcard)
		new->wildcard = true;
	if (!(*top))
		*top = new;
	if (*last)
		(*last)->next = new;
	*last = new;
	return (STATUS_OK);
}
