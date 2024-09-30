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

void	ft_input(char *arg, t_minishell *minishell)
{
	int	infile;

	infile = open(arg, O_RDONLY);
	if (infile == -1)
	{
		perror(arg);
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

void	ft_output(int token, char *arg, t_minishell *minishell)
{
	int	outfile;

	if (token == APPEND)
		outfile = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(arg);
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

void	ft_here_doc(char *arg, t_minishell *minishell)
{
	(void)arg;
	(void)minishell;
	printf("here_doc\n");
}
void	ft_redir(t_ast *ast, t_minishell *minishell)
{
	t_ast	*next;
	char	*arg;
	char	**args;
	int		token;
	bool	wildcard;
	
	wildcard = ((t_arg *)ast->data)->wildcard;
	arg = ft_arg_of((t_arg *)ast->data, minishell);
	token = ast->token;
	next = ast->left;
	free(ast);
	if (!arg)
	{
		ft_clear_ast(next);
		minishell->status = STATUS_MALLOC;
		return ;
	}
	if (wildcard)
	{
		args = ft_argv_wildcard(ft_wildcard(arg, NULL));
		if (!args)
		{
			free(arg);
			ft_clear_ast(next);
			minishell->status = STATUS_MALLOC;
			return ;
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
			return ;
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
	if ((minishell->status == STATUS_OK))
		ft_exec_ast(next, minishell);
	else
		ft_clear_ast(next);
}
