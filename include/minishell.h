/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 21:50:53 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "utils.h"
# include "ast.h"
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
	char			*name;
	char			*value;
	struct s_env	*previous;
	struct s_env	*next;
}	t_env;

char	**ft_envp_of_env(t_env *env);
t_env	*ft_env_of_envp(char **envp);
void	ft_clear_env(t_env *env);

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

typedef struct s_minishell
{
	int			parsing_status;
	int			status;
	int			std_in;
	int			std_out;
	char		**path;
	t_env		*env;
	bool		pipe_before;
	int			pipe;
	pid_t		last_cmd;
	t_pid		*wait_for_pids;
}	t_minishell;

void	ft_expand(t_arg *arg, t_minishell *minishell);
void	ft_add_history(char *line);

bool	ft_is_buildin(char *cmd);
void	ft_buildin(char **argv, t_minishell *minishell);

void	ft_clear_minishell(t_minishell *minishell);
void	ft_exit_minishell(t_minishell *minishell, int status);

char	*ft_arg_of(t_arg *arg, t_minishell *minishell);
char	**ft_argv_of(t_arg **args, t_minishell *minishell);

void	ft_do_pipe(t_ast *ast, t_minishell *minishell);
void	ft_redir(t_ast *ast, t_minishell *minishell);
void	ft_exec_cmd(t_ast *ast, t_minishell *minishell);
void	ft_exec_ast(t_ast *ast, t_minishell *minishell);
void	ft_exec_line(t_ast *ast, t_minishell *minishell);
void	ft_minishell_input(t_minishell *minishell);

#endif