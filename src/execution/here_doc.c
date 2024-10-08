/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:48:20 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 12:48:20 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reset_stds_for_readline(int *prev_stdout, t_minishell *minishell)
{
	if (minishell->std_in >= 0)
	{
		if (dup2(minishell->std_in, STDIN_FILENO) < 0)
			return (ft_fail(ERR_FAIL, "dup2"), STATUS_DUP2);
	}
	if (minishell->std_out < 0)
		return (*prev_stdout = -1, STATUS_OK);
	*prev_stdout = dup(STDOUT_FILENO);
	if (*prev_stdout < 0)
		return (ft_fail(ERR_FAIL, "dup"), STATUS_DUP);
	if (dup2(minishell->std_out, STDOUT_FILENO) < 0)
		return (ft_fail(ERR_FAIL, "dup2"), STATUS_DUP2);
	return (STATUS_OK);
}

int	ft_here_doc_stds(int prev_stdout, t_minishell *minishell)
{
	int	status;
	int	here_doc_tmp;

	if (prev_stdout >= 0)
	{
		status = ft_dup2_std(prev_stdout, OUT, minishell);
		if (status != STATUS_OK)
			return (status);
	}
	here_doc_tmp = open(HERE_DOC_FILE, O_RDONLY);
	if (here_doc_tmp < 0)
		return (perror(HERE_DOC_FILE), STATUS_OPEN);
	unlink(HERE_DOC_FILE);
	return (ft_dup2_std(here_doc_tmp, IN, minishell));
}

void	ft_readline_here_doc(int here_doc_tmp, char *limiter)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, limiter) && (g_sig != SIG_INT))
	{
		write(here_doc_tmp, line, ft_strlen(line));
		write(here_doc_tmp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(here_doc_tmp);
	if (line)
		free(line);
	else if (g_sig != SIG_INT)
		ft_fail(ERR_HERE_DOC, limiter);
}

int	ft_read_here_doc(int here_doc_tmp, char *limiter, int prev_stdout)
{
	int		dup_stdin;

	dup_stdin = dup(STDIN_FILENO);
	if (dup_stdin < 0)
	{
		if (prev_stdout >= 0)
			close(prev_stdout);
		return (STATUS_DUP);
	}
	ft_setup_signals(&ft_here_doc_signals);
	ft_readline_here_doc(here_doc_tmp, limiter);
	if (g_sig == SIG_INT)
	{
		if (dup2(dup_stdin, STDIN_FILENO) < 0)
		{	
			if (prev_stdout >= 0)
				close(prev_stdout);
			return (STATUS_DUP2);
		}
	}
	close(dup_stdin);
	return (STATUS_OK);
}

int	ft_here_doc(char *limiter, t_minishell *minishell)
{
	int		here_doc_tmp;
	int		prev_stdout;
	int		status;

	status = ft_reset_stds_for_readline(&prev_stdout, minishell);
	if (status != STATUS_OK)
		return (status);
	here_doc_tmp = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_tmp < 0)
		return (perror(HERE_DOC_FILE), STATUS_OPEN);
	status = ft_read_here_doc(here_doc_tmp, limiter, prev_stdout);
	if (status != STATUS_OK)
		return (status);
	return (ft_here_doc_stds(prev_stdout, minishell));
}
