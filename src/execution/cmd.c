/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 12:38:49 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

char	*ft_path_of(char const *path, char const *cmd)
{
	int		len;
	int		i;
	char	*concatenated;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		len --;
	len += ft_strlen(cmd) + 1;
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (NULL);
	concatenated[len] = '\0';
	i = 0;
	while (path[i])
	{
		concatenated[i] = path[i];
		i ++;
	}
	if (concatenated[i - 1] != '/')
		concatenated[i ++] = '/';
	len = i;
	while (cmd[i - len])
	{
		concatenated[i] = cmd[i - len];
		i ++;
	}
	return (concatenated);
}

char	*ft_get_cmd_path(char *cmd, t_minishell *minishell)
{
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (ft_fail(ERR_MALLOC, NULL), minishell->status = STATUS_MALLOC, NULL);
	}
	if (!minishell->path)
			return (ft_fail(ERR_CMD, NULL), minishell->status = STATUS_CMD, NULL);
	i = 0;
	while (minishell->path[i])
	{
		path = ft_path_of(minishell->path[i], cmd);
		if (!path)
			return (ft_fail(ERR_MALLOC, NULL), minishell->status = STATUS_MALLOC, NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i ++;
	}
	return (NULL);
}

void	ft_cmd(char **argv, t_minishell *minishell)
{
	char	*path;
	int		i;

	minishell->last_cmd = fork();
	if (minishell->last_cmd == -1)
	{
		ft_fail(ERR_FORK, NULL);
		minishell->status = STATUS_FORK;
		return ;
	}
	if (!minishell->last_cmd)
	{
		path = ft_get_cmd_path(argv[0], minishell);
		if (!path)
			ft_exit_minishell(minishell, minishell->status);
		execve(path, argv, NULL);
		ft_fail(ERR_EXECVE, NULL);
		// TODO refaire message erreur
		minishell->status = STATUS_EXECVE;
		ft_exit_minishell(minishell, minishell->status);
	}
	waitpid(minishell->last_cmd, &minishell->status, 0);
}

void	ft_exec_cmd(t_ast *ast, t_minishell *minishell)
{
	t_ast	*next;
	char	**argv;
	int		i;
	
	next = ast->left;
	argv = ft_argv_of((t_arg **)ast->data);
	free(ast);
	if (!argv)
	{
		ft_fail(ERR_MALLOC, NULL);
		minishell->status = STATUS_MALLOC;
		return ;
	}
	i = 0;
	while (argv[i])
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i ++;
	}
	if (ft_is_buildin(argv[0]))
	{
		ft_buildin(argv, minishell);
		ft_free_until((void **)argv, -1);
	}
	else
		ft_cmd(argv, minishell);
	if (next)
		ft_exec_ast(next, minishell);
}
