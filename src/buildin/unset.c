/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:53:35 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 19:53:35 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rm_env(t_env **env, t_env *to_rm)
{
	t_env	*next;
	t_env	*previous;

	free(to_rm->name);
	if (to_rm->value)
		free(to_rm->value);
	next = to_rm->next;
	previous = to_rm->previous;
	if (next)
		next->previous = previous;
	if (previous && previous->next)
		previous->next = next;
	else
		*env = next;
	free(to_rm);
}

void	unset_var(char **arg, t_minishell *minishell)
{
	t_env	*next;

	arg ++;
	while (*arg)
	{
		next = minishell->env;
		while (next)
		{
			if (!ft_strcmp(next->name, *arg))
			{
				if (!ft_strcmp("PATH", next->name))
				{
					ft_free_until((void **)(minishell->path), -1);
					minishell->path = NULL;
				}
				if (!ft_strcmp("SHLVL", next->name))
					minishell->shlvl = 0;
				ft_rm_env(&(minishell->env), next);
				break ;
			}
			next = next->next;
		}
		arg ++;
	}
}
