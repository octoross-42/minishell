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

void	ft_exec_ast(t_ast *ast, t_minishell *minishell)
{
	if (ast->token == PIPE)
	{

	}
}

void	ft_exec_line(t_ast *ast, t_minishell *minishell)
{
	int	status;

	if (!ast)
		ft_minishell_input(minishell);
	printf("executing line\n");
	minishell->previous_fork = CMD;
	minishell->last_pid = -1;
	minishell->last_cmd = -1;
	minishell->pipe = -1;
	ft_exec_ast(ast, minishell);
	ft_minishell_input(minishell);
	// ft_exit_minishell(minishell, STATUS_OK);
}
