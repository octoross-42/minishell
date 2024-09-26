/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 15:54:14 by octoross         ###   ########.fr       */
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
	t_env	*previous;
	struct s_env	*next;
}	t_env;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

typedef struct s_minishell
{
	pid_t		last_cmd;
	t_pid		*wait_for_pids;
	int			pipe;
	bool		pipe_before;
	int			std_in;
	int			std_out;
	int			status;
	int			parsing_status;
	t_env		*env;
	char		**path;
}	t_minishell;

void	ft_add_history(char *line);
char	*ft_arg_of(t_arg *arg);
char	**ft_argv_of(t_arg **arg);

void	ft_minishell_input(t_minishell *minishell);
void	ft_exec_line(t_ast *ast, t_minishell *minishell);
void	ft_exit_minishell(t_minishell *minishell, int status);

void	ft_exec_cmd(t_ast *ast, t_minishell *minishell);
void	ft_exec_ast(t_ast *ast, t_minishell *minishell);
void	ft_redir(t_ast *ast, t_minishell *minishell);
void 	ft_do_pipe(t_ast *ast, t_minishell *minishell);

bool	ft_is_buildin(char *cmd);
void	ft_buildin(char **argv, t_minishell *minishell);

t_env	*ft_env_of_envp(char **envp);
void	ft_clear_env(t_env *env);

#endif