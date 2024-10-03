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

void ft_input(char *arg, t_minishell *minishell)
{
	int infile;
	int	status;

	infile = open(arg, O_RDONLY);
	if (infile == -1)
	{
		perror(arg);
		minishell->status = STATUS_OPEN;
		return;
	}
	status = ft_dup2_std(infile, IN, minishell);
	if (status != STATUS_OK)
	{
		minishell->status = status;
		return;
	}
}

void ft_output(int token, char *arg, t_minishell *minishell)
{
	int outfile;

	if (token == APPEND)
		outfile = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(arg);
		minishell->status = STATUS_OPEN;
		return;
	}
	status = ft_dup2_std(outfile, OUT, minishell);
	if (status != STATUS_OK)
	{
		minishell->status = status;
		return;
	}
}

void ft_here_doc(char *limiter, t_minishell *minishell)
{
	char *line;

	fd = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
        perror("open");
		minishell->status = STATUS_OPEN;
		return;
	}
	// signal(SIGINT, sig_handler_here_doc);
	line = readline("> ");
	while (line && ft_strcmp(line, limiter))
	{
		// if (g_sigint == 1)
		// {
		// 	close_if(fd);
		// 	unlink(FILE_HEREDOC);
		// 	return ;
		// }
		write(here_doc, line, ft_strlen(line));
		write(here_doc, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
		ft_fail(ERR_HERE_DOC, limiter);
}

void ft_redir(t_ast *ast, t_minishell *minishell)
{
	t_ast *next;
	char *arg;
	char **args;
	int token;
	bool wildcard;

	wildcard = ((t_arg *)ast->data)->wildcard;
	arg = ft_arg_of((t_arg *)ast->data, minishell);
	token = ast->token;
	next = ast->left;
	free(ast);
	if (!arg)
	{
		ft_clear_ast(next);
		minishell->status = STATUS_MALLOC;
		return;
	}
	if (wildcard)
	{
		args = ft_argv_wildcard(ft_wildcard(arg, NULL));
		if (!args)
		{
			free(arg);
			ft_clear_ast(next);
			minishell->status = STATUS_MALLOC;
			return;
		}
		if (!(*args))
			free(args);
		else if (args[1])
		{
			free(arg);
			ft_free_until((void **)args, -1);
			ft_fail(ERR_REDIR, NULL);
			ft_clear_ast(next);
			minishell->status = STATUS_REDIR;
			return;
		}
		else
		{
			free(arg);
			arg = args[0];
			free(args);
		}
	}
	if (ft_is_output(token))
		ft_output(token, arg, minishell);
	else if (token == INPUT)
		ft_input(arg, minishell);
	else if (token == HERE_DOC)
		ft_here_doc(arg, minishell);
	free(arg);
	if (minishell->status == STATUS_OK)
		ft_exec_ast(next, minishell);
	else
		ft_clear_ast(next);
}
