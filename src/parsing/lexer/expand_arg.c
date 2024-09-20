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

bool	ft_add_expand(t_expand **expand, t_expand **last)
{
	t_expand	*new;

	new = (t_expand *)malloc(sizeof(t_expand));
	if (!new)
		return (ft_fail(ERR_MALLOC), false);
	new->is_expand = true;
	new->value = NULL;
	new->next = NULL;
	new->len_name = 0;
	if (*last)
		(*last)->next = new;
	else
		*expand = new;
	*last = new;
	return (true);
}

int	ft_len_expand(char **s, t_expand **expand, t_expand **last)
{
	t_expand	*new;
	int			i;
	char		*name;

	if (!expand || !last)
		return (ft_fail(ERR_PROG), -1);
	if (!ft_add_expand(expand, last))
		return (-1);
	(*s)++;
	i = 0;
	while (ft_isname((*s)[i]))
		i ++;
	if (!i)
		return ((*last)->is_expand = false, 1);
	name = (char *)malloc((i + 1) * sizeof(char));
	if (!name)
		return (ft_fail(ERR_MALLOC), -1);
	ft_strncpy(name, *s, i);
	(*last)->len_name = i;
	*s += i;
	(*last)->value = getenv(name);
	free(name);
	return (ft_strlen((*last)->value));
}

void	ft_clear_expand(t_expand *expand)
{
	if (!expand)
		return ;
	if (expand->value)
	{
		(void)expand;
		// free(expand->value);
	}
	if (expand->next)
		ft_clear_expand(expand->next);
	free(expand);
}

static void	ft_next_expand(t_expand **expand)
{
	t_expand	*next;

	next = *expand;
	*expand = (*expand)->next;
	next->next = NULL;
	ft_clear_expand(next);
}

int	ft_expand_arg(char **s, char *data, t_expand **expand)
{
	int	len;

	len = 0;
	if (!expand || !(*expand))
		return (ft_fail(ERR_PROG), -1);
	if ((*expand)->is_expand)
	{
		if (!(*expand)->value)
			return (ft_clear_expand(*expand), ft_fail(ERR_PROG), -1);
		len = ft_strlen((*expand)->value);
		ft_strcpy(data, (*expand)->value);
	}
	else
		data[len ++] = '$';
	*s += (*expand)->len_name + 1;
	ft_next_expand(expand);
	return (len);
}
