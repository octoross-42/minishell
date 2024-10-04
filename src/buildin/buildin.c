/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:58:51 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 00:58:51 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_buildin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	if (!ft_strcmp(cmd, "pwd"))
		return (true);
	if (!ft_strcmp(cmd, "export"))
		return (true);
	if (!ft_strcmp(cmd, "unset"))
		return (true);
	if (!ft_strcmp(cmd, "env"))
		return (true);
	if (!ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	ft_buildin(char **argv, t_minishell *minishell)
{
	int	status;

	status = STATUS_OK;
	if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, minishell);
	if (!ft_strcmp(argv[0], "echo"))
		print_echo(argv);
	if (!ft_strcmp(argv[0], "env"))
		print_env(minishell->env, false);
	if (!ft_strcmp(argv[0], "pwd"))
		minishell->status = print_wd(&(minishell->env));
	if (!ft_strcmp(argv[0], "cd"))
		minishell->status = change_dir(argv, &(minishell->env));
	if (!ft_strcmp(argv[0], "export"))
		status = ft_export(argv, minishell);
	if (!ft_strcmp(argv[0], "unset"))
		unset_var(argv, minishell);
	minishell->status = status;
}
