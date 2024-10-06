/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:41:02 by octoross          #+#    #+#             */
/*   Updated: 2024/09/24 01:41:02 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup2_std(int fd, bool in, t_minishell *minishell)
{
	if (fd < 0)
		return (STATUS_OK);
	if (in)
	{
		if (minishell->std_in < 0)
			minishell->std_in = dup(STDIN_FILENO);
		if (minishell->std_in < 0)
			return (ft_fail(ERR_FAIL, "dup"), STATUS_DUP);
		if (dup2(fd, STDIN_FILENO) < 0)
			return (close(fd), ft_fail(ERR_FAIL, "dup2"), STATUS_DUP2);
	}
	else
	{
		if (minishell->std_out < 0)
			minishell->std_out = dup(STDOUT_FILENO);
		if (minishell->std_out < 0)
			return (ft_fail(ERR_FAIL, "dup"), STATUS_DUP);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), ft_fail(ERR_FAIL, "dup2"), STATUS_DUP2);
	}
	close(fd);
	return (STATUS_OK);
}

int	ft_input(char *arg, t_minishell *minishell)
{
	int	infile;

	infile = open(arg, O_RDONLY);
	if (infile == -1)
	{
		perror(arg);
		return (STATUS_OPEN);
	}
	return (ft_dup2_std(infile, IN, minishell));
}

int	ft_output(int token, char *arg, t_minishell *minishell)
{
	int	outfile;

	if (token == APPEND)
		outfile = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(arg);
		return (STATUS_OPEN);
	}
	return (ft_dup2_std(outfile, OUT, minishell));
}

int	ft_exec_redir(char *arg, t_ast *ast, t_minishell *minishell)
{
	if (ast->token == HERE_DOC)
		return (ft_here_doc(arg, minishell));
	else if (ft_is_output(ast->token))
		return (ft_output(ast->token, arg, minishell));
	else if (ast->token == INPUT)
		return (ft_input(arg, minishell));
	return (STATUS_PROG);
}

void	ft_redir(t_ast *ast, t_minishell *minishell)
{
	int		status;
	char	*arg;
	t_ast	*next;

	arg = ft_file_arg((t_arg *)ast->data, minishell);
	if (!arg)
	{
		ft_clear_ast(ast->left);
		free(ast);
		return ;
	}
	status = ft_exec_redir(arg, ast, minishell);
	next = ast->left;
	free(ast);
	free(arg);
	if (status == STATUS_OK)
		ft_exec_ast(next, minishell);
	else
	{
		minishell->status = status;
		ft_clear_ast(next);
	}
}
