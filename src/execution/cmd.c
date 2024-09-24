/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:59:25 by octoross          #+#    #+#             */
/*   Updated: 2024/09/22 00:59:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_executable(char const *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len ++;
	return (len);
}
char	*ft_path_of(char const *path, char const *cmd)
{
	int		len;
	int		i;
	char	*concatenated;

	len = ft_len_executable(cmd) + ft_strlen(path) + 1;
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (ft_fail(ERR_MALLOC, NULL), NULL);
	concatenated[len] = '\0';
	i = 0;
	while (path[i])
	{
		concatenated[i] = path[i];
		i ++;
	}
	concatenated[i] = '/';
	len = i;
	while (cmd[i - len] && cmd[i - len] != ' ')
	{
		concatenated[i + 1] = cmd[i - len];
		i ++;
	}
	return (concatenated);
}

char	*ft_get_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_path_of(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i ++;
	}
	return (NULL);
}

void	ft_exec_cmd(t_ast *ast, t_minishell *minishell)
{
	char	*path;
	int		i;

	path = ft_get_cmd_path(((char **)ast->data)[0], minishell->path);
	if (!path)
	{
		ft_fail(ERR_CMD, NULL);
		ft_exit_minishell(minishell, STATUS_CMD);
	}
	execve(path, ast->data, NULL);
	ft_fail(ERR_EXECVE, NULL);
	minishell->status = STATUS_EXECVE;
	ft_exit_minishell(minishell, STATUS_EXECVE);
}
