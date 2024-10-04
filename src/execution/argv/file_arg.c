/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:49:56 by octoross          #+#    #+#             */
/*   Updated: 2024/10/03 21:49:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_file_arg(t_arg *data, t_minishell *minishell)
{
	char			*arg;
	t_wildcard_arg	*wildcard_arg;
	bool			is_wildcard;

	is_wildcard = data->wildcard;
	arg = ft_arg_of(data, minishell);
	if (!arg)
		return (minishell->status = STATUS_MALLOC, NULL);
	if (is_wildcard)
	{
		wildcard_arg = ft_wilcard_arg(arg);
		if (!wildcard_arg)
			return (minishell->status = STATUS_MALLOC, NULL);
		if (!(wildcard_arg->is_single))
		{
			ft_fail(ERR_REDIR, NULL);
			ft_clear_wildcard_arg(wildcard_arg);
			minishell->status = STATUS_REDIR;
			return (NULL);
		}
		arg = (char *)wildcard_arg->data;
		return (free(wildcard_arg), arg);
	}
	else
		return (arg);
}
