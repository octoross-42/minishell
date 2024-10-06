/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:10:23 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 17:09:14 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *ep, bool export)
{
	t_env	*cur;

	cur = ep;
	while (cur)
	{
		if (export)
			write(STDOUT_FILENO, "export ", 7);
		if (cur->value || export)
		{
			write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
			if (cur->value)
			{
				write(STDOUT_FILENO, "=", 1);
				if (export)
					write(STDOUT_FILENO, "\"", 1);
				write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
				if (export)
					write(STDOUT_FILENO, "\"", 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		cur = cur->next;
	}
}
