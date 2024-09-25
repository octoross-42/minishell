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

void	ft_input(t_ast *ast, t_minishell *minishell)
{
	int	infile;

	infile = open((char *)ast->data, O_RDONLY);
	if (infile == -1)
	{
		perror((char *)ast->data);
		ft_exit_minishell(minishell, STATUS_OPEN);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		ft_fail(ERR_DUP2, NULL);
		ft_exit_minishell(minishell, STATUS_DUP2);
	}
	close(infile);
}

void	ft_output(t_ast *ast, t_minishell *minishell)
{
	int	outfile;

	if (ast->token == APPEND)
		outfile = open((char *)ast->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open((char *)ast->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror((char *)ast->data);
		ft_exit_minishell(minishell, STATUS_OPEN);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		ft_fail(ERR_DUP2, NULL);
		ft_exit_minishell(minishell, STATUS_DUP2);
	}
	close(outfile);
}
void	ft_here_doc(t_ast *ast, t_minishell *minishell)
{
	printf("here_doc\n");
}
void	ft_redir(t_ast *ast, t_minishell *minishell)
{
	if (ft_is_output(ast->token))
		ft_output(ast, minishell);
	if (ast->token == INPUT)
		ft_input(ast, minishell);
	else if (ast->token == HERE_DOC)
		ft_here_doc(ast, minishell);
	if (ast->left)
		ft_exec_ast(ast->left, minishell);
}