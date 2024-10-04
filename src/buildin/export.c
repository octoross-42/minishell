/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:27:05 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 18:27:05 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **arg, t_minishell *minishell)
{
	char	*name;
	char	*value;
	int		status;

	if (!arg[1])
		return (print_env(minishell->env, true), STATUS_OK);
	arg ++;
	while (*arg)
	{
		if (!ft_parse_envp(&name, &value, *arg))
			return (STATUS_MALLOC);
		status = ft_add_env(&(minishell->env), name, value);
		if (status != STATUS_OK)
			return (status);
		if (!ft_strcmp("PATH", name))
			minishell->path = ft_get_path(value);
		arg ++;
	}
	return (STATUS_OK);
}
