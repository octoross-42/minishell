/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 12:38:55 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_separator(t_ast *ast, t_minishell *minishell)
{
	if (((ast->token == OR) && (minishell->status == STATUS_OK))
			|| ((ast->token == AND) && (minishell->status != STATUS_OK)))
		ft_exec_ast(ast->left, minishell);
}

void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
{
	// printf("executing ast\n");
	if (!ast)
		return ;
	// printf("ast->token: %d\n", ast->token);
	if ((ast->token == PIPE) || minishell->pipe_before)
		ft_do_pipe(ast, minishell);
	else if (ft_is_redir(ast->token))
		ft_redir(ast, minishell);
	else if (ast->token == CMD)
		ft_exec_cmd(ast, minishell);
	else if (ft_is_separator(ast->token))
		ft_separator(ast, minishell);
	else
	{
		ft_fail(ERR_PARSING, NULL);
		ft_exit_minishell(minishell, STATUS_PROG);
	}
}

void	ft_exec_line(t_ast *ast, t_minishell *minishell)
{
	int	status;

	if (!ast)
		ft_minishell_input(minishell);
	// printf("executing line\n");
	minishell->pipe_before = false;
	minishell->last_cmd = -1;
	minishell->wait_for_pids = NULL;
	minishell->pipe = -1;
	minishell->pipe_before = false;
	ft_exec_ast(ast, minishell);
	ft_minishell_input(minishell);
	// ft_exit_minishell(minishell, STATUS_OK);
}
