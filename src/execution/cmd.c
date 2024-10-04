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

char	*ft_get_cmd_path(char *cmd, t_minishell *mini)
{
	char	*path;
	int		i;

	if (cmd[0] && access(cmd, F_OK | X_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (ft_fail(ERR_MALLOC, "no path for cmd"), \
				mini->status = STATUS_MALLOC, NULL);
		return (path);
	}
	i = 0;
	while (cmd[0] && mini->path && mini->path[i])
	{
		path = ft_build_path(mini->path[i ++], cmd, 0);
		if (!path)
			return (ft_fail(ERR_MALLOC, "no path for cmd"), \
				mini->status = STATUS_MALLOC, NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	ft_fail(ERR_CMD, cmd);
	mini->status = STATUS_CMD;
	return (NULL);
}

void	ft_execve(char **argv, t_ast *next, t_minishell *minishell)
{
	char	*path;
	char	**envp;

	path = ft_get_cmd_path(argv[0], minishell);
	if (!path)
	{
		ft_clear_ast(next);
		ft_free_until((void **)argv, -1);
		ft_exit_minishell(minishell, minishell->status);
	}
	envp = ft_envp_of_env(minishell->env);
	ft_clear_minishell(minishell);
	execve(path, argv, envp);
	free(path);
	ft_free_until((void **)argv, -1);
	ft_free_until((void **)envp, -1);
	ft_reset_stds(minishell);
	perror("minishell : execve");
	minishell->status = STATUS_EXECVE;
	exit(minishell->status);
}

void	ft_cmd(char **argv, t_ast *next, t_minishell *minishell)
{
	int		status;

	minishell->last_cmd = fork();
	if (minishell->last_cmd == -1)
	{
		ft_fail(ERR_FORK, NULL);
		minishell->status = STATUS_FORK;
		return ;
	}
	if (!minishell->last_cmd)
		ft_execve(argv, next, minishell);
	waitpid(minishell->last_cmd, &status, 0);
	minishell->status = WEXITSTATUS(status);
	// TODO WEXISTATUS si exit normal
}

void	ft_exec_cmd(t_ast *ast, t_minishell *minishell)
{
	t_ast	*next;
	char	**argv;

	next = ast->left;
	argv = ft_argv_of((t_arg **)ast->data, minishell);
	free(ast);
	if (!argv)
	{
		minishell->status = STATUS_MALLOC;
		return ;
	}
	if (ft_is_buildin(argv[0]))
		ft_buildin(argv, minishell);
	else
		ft_cmd(argv, next, minishell);
	ft_free_until((void **)argv, -1);
	ft_exec_ast(next, minishell);
}
