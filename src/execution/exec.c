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

void	ft_reset_stds(t_minishell *minishell)
{
	// TODO faire fail les dup2
	if (minishell->std_in != -1)
	{
		ft_dup2_std(minishell->std_in, IN, minishell);
	}
	if (minishell->std_out != -1)
	{
		ft_dup2_std(minishell->std_out, OUT, minishell);
	}
	minishell->std_in = -1;
	minishell->std_out = -1;
}

void	ft_do_separator(t_ast *ast, t_minishell *minishell)
{
	t_ast	*next;
	int		token;

	next = ast->left;
	token = ast->token;
	ft_clear_node_ast(ast);
	ft_reset_stds(minishell);
	if (((token == OR) && (minishell->status != STATUS_OK))
		|| ((token == AND) && (minishell->status == STATUS_OK)))
		ft_exec_ast(next, minishell);
	else
		ft_clear_ast(next);
}

void	ft_do_subshell(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	t_ast	*left;
	t_ast	*right;

	pid = fork();
	if (pid < 0)
	{
		ft_clear_ast(ast);
		ft_fail(ERR_FORK, NULL);
		minishell->status = STATUS_FORK;
		return ;
	}
	left = ast->left;
	right = ast->right;
	free(ast);
	if (!pid)
	{
		ft_change_shlvl(minishell);
		ft_clear_ast(right);
		ft_exec_ast(left, minishell);
		ft_exit_minishell(minishell, minishell->status);
	}
	ft_clear_ast(left);
	ft_waitpid(pid, minishell, true);
	ft_exec_ast(right, minishell);
}

void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
{
	ft_setup_signals(&ft_exec_signals);
	if (!ast || (g_sig == SIG_INT))
	{
		if (ast)
			ft_clear_ast(ast);
		ft_reset_stds(minishell);
		return ;
	}
	if (ast->token == SUBSHELL)
		ft_do_subshell(ast, minishell);
	else if ((ast->token == PIPE) || minishell->pipe_before)
		ft_do_pipe(ast, minishell);
	else if (ft_is_redir(ast->token))
		ft_redir(ast, minishell);
	else if (ast->token == CMD)
		ft_exec_cmd(ast, minishell);
	else if (ft_is_separator(ast->token))
		ft_do_separator(ast, minishell);
	else
	{
		ft_fail(ERR_PARSING, NULL);
		ft_clear_minishell(minishell);
		ft_reset_stds(minishell);
	}
}

void	ft_exec_line(t_ast *ast, t_minishell *minishell)
{
	g_sig = NO_SIG;
	if (!ast)
		ft_minishell_input(minishell);
	minishell->pipe_before = false;
	minishell->last_cmd = -1;
	minishell->wait_for_pids = NULL;
	minishell->pipe = -1;
	minishell->pipe_before = false;
	minishell->std_in = -1;
	minishell->std_out = -1;
	ft_exec_ast(ast, minishell);
	ft_minishell_input(minishell);
}
