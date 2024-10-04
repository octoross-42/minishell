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
			return (ft_fail(ERR_DUP, NULL), STATUS_DUP);
		if (dup2(fd, STDIN_FILENO) < 0)
			return (close(fd), ft_fail(ERR_DUP2, NULL), STATUS_DUP2);
	}
	else
	{
	if (minishell->std_out < 0)
			minishell->std_out = dup(STDOUT_FILENO);
		if (minishell->std_out < 0)
			return (ft_fail(ERR_DUP, NULL), STATUS_DUP);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), ft_fail(ERR_DUP2, NULL), STATUS_DUP2);
	}
	close(fd);
	return (STATUS_OK);
}

int ft_input(char *arg, t_minishell *minishell)
{
	int infile;

	infile = open(arg, O_RDONLY);
	if (infile == -1)
	{
		perror(arg);
		return (STATUS_OPEN);
	}
	return (ft_dup2_std(infile, IN, minishell));
}

int ft_output(int token, char *arg, t_minishell *minishell)
{
	int outfile;

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

int	ft_reset_stds_for_readline(int *prev_out, t_minishell *minishell)
{
	if (minishell->std_in >= 0)
	{
		if (dup2(minishell->std_in, STDIN_FILENO) < 0)
			return (ft_fail(ERR_DUP2, NULL), STATUS_DUP2);
	}
	if (minishell->std_out < 0)
		return (*prev_out = -1, STATUS_OK);
	*prev_out = dup(STDOUT_FILENO);
	if (*prev_out < 0)
		return (ft_fail(ERR_DUP, NULL), STATUS_DUP);
	if (dup2(minishell->std_out, STDOUT_FILENO) < 0)
		return (ft_fail(ERR_DUP2, NULL), STATUS_DUP2);
	return (STATUS_OK);
}

int ft_here_doc(char *limiter, t_minishell *minishell)
{
	char *line;
	int	here_doc_tmp;
	int	prev_out;
	int	status;

	here_doc_tmp = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_tmp < 0)
		return (perror(HERE_DOC_FILE), STATUS_OPEN);
	ft_reset_stds_for_readline(&prev_out, minishell);
	line = readline("> ");
	while (line && ft_strcmp(line, limiter))
	{
		write(here_doc_tmp, line, ft_strlen(line));
		write(here_doc_tmp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
		ft_fail(ERR_HERE_DOC, limiter);
	close(here_doc_tmp);
	if (prev_out >= 0)
	{
		status = ft_dup2_std(prev_out, OUT, minishell);
		if (status != STATUS_OK)
			return (status);
	}
	here_doc_tmp = open(HERE_DOC_FILE, O_RDONLY);
	if (here_doc_tmp < 0)
		return (perror(HERE_DOC_FILE), STATUS_OPEN);
	// unlink(HERE_DOC_FILE);
	return (ft_dup2_std(here_doc_tmp, IN, minishell));
}

void ft_redir(t_ast *ast, t_minishell *minishell)
{
	int	status;
	t_ast *next;
	char *arg;
	
	arg = ft_file_arg((t_arg *)ast->data, minishell);
	if (!arg)
	{
		ft_clear_ast(ast->left);
		free(ast);
		return ;
	}
	status = STATUS_OK;
	if (ast->token == HERE_DOC)
		status = ft_here_doc(arg, minishell);
	else if (ft_is_output(ast->token))
		status = ft_output(ast->token, arg, minishell);
	else if (ast->token == INPUT)
		status = ft_input(arg, minishell);
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
