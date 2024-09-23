/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/22 00:52:03 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "lexer.h"
# include "display.h"

# include <errno.h>
# include <stdbool.h>

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	pid_t		last_pid;
	int			status;
	char		**envp;
	char		**path;
	t_ast		*ast;
}	t_minishell;

void	ft_minishell_input(t_minishell *minishell);
void	ft_exec_line(t_minishell *minishell);
void	ft_exit_minishell(t_minishell *minishell, int status);

#endif