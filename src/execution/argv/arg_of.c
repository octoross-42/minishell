/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:01:32 by octoross          #+#    #+#             */
/*   Updated: 2024/10/03 22:01:32 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_arg(t_arg *arg, t_minishell *minishell)
{
	int		len;

	len = 0;
	while (arg)
	{
		if (arg->expand)
			ft_expand(arg, minishell);
		if (arg->str)
			len += ft_strlen(arg->str);
		arg = arg->next;
	}
	return (len);
}

char	*ft_arg_of(t_arg *arg, t_minishell *minishell)
{
	t_arg	*to_free;
	char	*str;
	int		len;
	int		i;

	len = ft_len_arg(arg, minishell);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (ft_fail(ERR_MALLOC, "no arg"), NULL);
	str[len] = '\0';
	len = 0;
	while (arg)
	{
		i = 0;
		while (arg->str && arg->str[i])
			str[len ++] = arg->str[i ++];
		if (arg->str && !arg->expand)
			free(arg->str);
		to_free = arg;
		arg = arg->next;
		free(to_free);
	}
	return (str);
}
