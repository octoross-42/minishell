/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:15:32 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 16:31:49 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(t_env **env)
{
	char	*buffer;
	int		bsize;

	bsize = BSIZE;
	if (bsize <= 0)
		bsize = 1;
	buffer = malloc(sizeof(char) * (bsize + 1));
	if (!buffer)
		return (ft_fail(ERR_MALLOC, "no pwd"), NULL);
	while (!getcwd(buffer, bsize))
	{
		free(buffer);
		if (errno == ERANGE)
		{
			bsize += 4096;
			buffer = malloc(sizeof(char) * (bsize + 1));
			if (!buffer)
				return (ft_fail(ERR_MALLOC, "no pwd"), NULL);
		}
		else
			return (perror("pwd"), NULL);
	}
	ft_add_env(env, ft_strdup("PWD"), buffer);
	return (buffer);
}

int	print_wd(t_env **ep)
{
	char	*pwd;

	pwd = ft_get_env_value("PWD", *ep);
	if (!pwd)
		pwd = ft_getcwd(ep);
	if (!pwd)
		return (STATUS_MALLOC);
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (STATUS_OK);
}
