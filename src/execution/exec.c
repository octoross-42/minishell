/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:21:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 19:03:13 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_fork(t_ast *ast, t_minishell *minishell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_free_until((void **)minishell->path, -1);
		ft_clear_ast(minishell->ast);
		ft_fail(ERR_FORK, NULL);
		exit(EXIT_FORK);
	}
}

void	ft_redir(t_ast *ast)
{
	return ;
}

void	ft_exec_cmd(void)
{
	return ;
}

void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
{
	if (ft_is_fork(ast->token))
		ft_exec_fork(ast, minishell);
	else if (ft_is_redir(ast->token))
		ft_redir(ast);
	else if (ast->token == CMD)
		ft_exec_cmd();
	else
	{
		ft_free_until((void **)minishell->path, -1);
		ft_clear_ast(minishell->ast);
		ft_fail(ERR_PARSING, NULL);
		ft_exit_minishell(minishell, EXIT_TOKEN);
	}
}

void	ft_exec_line(t_minishell *minishell)
{
	printf("executez le tralala\n");
	ft_exit_minishell(minishell, STATUS_OK);
	// minishell->last_pid = fork();
}
