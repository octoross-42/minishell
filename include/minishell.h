/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 13:51:58 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "lexer.h"
# include "display.h"

# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	pid_t		last_pid;
	pid_t		last_cmd;
	int			pipe;
	int			previous_fork;
	int			status;
	int			parsing_status;
	t_env		*env;
	char		**path;
	t_ast		*ast;
}	t_minishell;

void	ft_add_history(char *line);
char	**ft_get_argv(t_arg **arg);

void	ft_minishell_input(t_minishell *minishell);
void	ft_exec_line(t_ast *ast, t_minishell *minishell);
void	ft_exit_minishell(t_minishell *minishell, int status);

void	ft_exec_cmd(t_ast *ast, t_minishell *minishell);
void	ft_exec_ast(t_ast *ast, t_minishell *minishell);
void	ft_exec_fork(t_ast *ast, t_minishell *minishell);
void	ft_wait_previous(t_ast *ast, t_minishell *minishell);
void	ft_do_previous_pipe(t_minishell *minishell);
void	ft_redir(t_ast *ast, t_minishell *minishell);

#endif