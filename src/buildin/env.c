/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:10:23 by octoross          #+#    #+#             */
/*   Updated: 2024/09/30 22:14:01 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *ep)
{
	t_env	*cur;

	cur = ep;
	while (cur)
	{
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
}
