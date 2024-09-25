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
		minishell->status = STATUS_OPEN;
		return ;
	}
	if (minishell->std_in == -1)
		minishell->std_in = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		ft_fail(ERR_DUP2, NULL);
		minishell->status = STATUS_DUP2;
		return ;
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
		minishell->status = STATUS_OPEN;
		return ;
	}
	if (minishell->std_out == -1)
		minishell->std_out = dup(STDOUT_FILENO);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		ft_fail(ERR_DUP2, NULL);
		minishell->status = STATUS_DUP2;
		return ;
	}
	close(outfile);
}
void	ft_here_doc(t_ast *ast, t_minishell *minishell)
{
	printf("here_doc\n");
}
void	ft_redir(t_ast *ast, t_minishell *minishell)
{
	t_ast	*next;
	char	**args;
	// TODO : transformer la data d'ast en arg

	if (true)
		printf("naha\n");
	else if (ft_is_output(ast->token))
		ft_output(ast, minishell);
	else if (ast->token == INPUT)
		ft_input(ast, minishell);
	else if (ast->token == HERE_DOC)
		ft_here_doc(ast, minishell);
	next = ast->left;
	ft_clear_node_ast(ast);
	if (next && (minishell->status == STATUS_OK))
		ft_exec_ast(next, minishell);
	else
		ft_clear_ast(next);
}