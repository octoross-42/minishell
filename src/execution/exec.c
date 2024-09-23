/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:21:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/23 00:35:14 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
// {
// 	if (ft_is_fork(ast->token))
// 		ft_exec_fork(ast, minishell);
// 	else if (ft_is_redir(ast->token))
// 		ft_redir(ast, minishell);
// 	else if (!ast->last)
// 		ft_exec_cmd(ast, minishell);
// 	else
// 		ft_exec_last(ast, minishell);
	
// }

// void	ft_exec_last(t_ast *ast, t_minishell *minishell)
// {
// 	minishell->last_pid = fork();
// 	if (minishell->last_pid == -1)
// 	{
// 		ft_fail(ERR_FORK, NULL);
// 		ft_exit_minishell(minishell, STATUS_FORK);
// 	}
// 	if (!minishell->last_pid)
// 		ft_exec_ast(minishell->ast, minishell);
// 	waitpid(minishell->last_pid, status, 0);
// 	minishell->status = WEXITSTATUS(status);
// 	while (wait(NULL) != -1)
// 		;
// 	ft_minishell_input(minishell);
// }

void	ft_exec_line(t_minishell *minishell)
{
	int	status;

	if (!minishell->ast)
		ft_minishell_input(minishell);
	// ft_exec_ast(minishell->ast, minishell);
	ft_minishell_input(minishell);
	ft_exit_minishell(minishell, STATUS_OK);
}


	// waitpid(minishell->last_pid, &status, 0);
	// while (wait(NULL) != -1)
	// 	;
	// exit(WEXITSTATUS(status));