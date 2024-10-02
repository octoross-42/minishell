/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:43:07 by octoross          #+#    #+#             */
/*   Updated: 2024/10/01 17:09:39 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_build_cd_path(char *pwd, char *cd)
{
	int		len;
	int		i;
	int		end;

	if (!pwd || !cd)
		return (NULL);
	len = 0;
	i = 0;
	end = len - 1;
	while (cd[i])
	{
		if (!ft_strncmp(&cd[i], "./", 2))
			i += 2;
		else if (!ft_strncmp(&cd[i], "../", 3))
		{
			if (i == 0)
			{
				if ((end > 0) && pwd[end] == '/')
					end --;
				while ((end > 0) && pwd[end] != '/')
					end --;
			}
			else
			{
				if (cd[i - 1] == '/')
					i --;
			}
		}
	}
	return (NULL);
}

int	change_dir(char **arg, t_env *env)
{
	(void)env;
	if (!arg[1])
		return (ft_fail("Error: cd: specify a path\n", NULL), 1);
	if (arg[2])
		return (ft_fail("cd : too many arguments\n", NULL), 1);
	if (chdir(arg[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}

