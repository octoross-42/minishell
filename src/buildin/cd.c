/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:43:07 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 15:56:36 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char **arg, t_env **env)
{
	(void)env;
	if (!arg[1])
		return (ft_fail(ERR_CD, NULL), STATUS_BUILDIN);
	if (arg[2])
		return (ft_fail(ERR_TMA, "cd"), STATUS_BUILDIN);
	if (chdir(arg[1]) == -1)
		return (perror(arg[1]), STATUS_CHDIR);
	if (!ft_getcwd(env))
		return (STATUS_MALLOC);
	return (STATUS_OK);
}
