/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:02:34 by octoross          #+#    #+#             */
/*   Updated: 2024/09/19 18:02:34 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_arg_expand(char **s, t_arg *arg)
{
	int			i;
	char		*name;

	(*s)++;
	arg->expand = true;
	i = 0;
	while (ft_isname((*s)[i]))
		i ++;
	name = (char *)malloc((i + 1) * sizeof(char));
	if (!name)
		return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
	ft_strncpy(name, *s, i);
	arg->str = name;
	*s += i;
	return (STATUS_OK);
}
