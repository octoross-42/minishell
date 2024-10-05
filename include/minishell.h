/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 22:15:28 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "argv.h"
# include "ast.h"
# include "buildin.h"
# include "display.h"
# include "err.h"
# include "gnl.h"
# include "lexer.h"
# include "token.h"
# include "utils.h"
# include "wildcard.h"

# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell	t_minishell;

void	ft_add_history(char *line, int history);
void	ft_load_history(t_minishell *minishell);

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*previous;
	struct s_env	*next;
}	t_env;

bool	ft_parse_envp(char **name, char **value, char *envp);
int		ft_add_env(t_env **env, char *name, char *value);
char	*ft_get_env_value(char *name, t_env *env);
char	**ft_envp_of_env(t_env *env);
t_env	*ft_env_of_envp(char **envp);
void	ft_clear_env(t_env *env);
char	*ft_getcwd(t_env **env);

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

void	ft_add_pid_to_wait(pid_t pid, t_minishell *minishell);
void	ft_last_pipe_wait(t_minishell *minishell);
void	ft_waitpid(pid_t pid, t_minishell *minishell, \
	bool register_status);

typedef struct s_minishell
{
	int			history;
	int			parsing_status;
	int			status;
	int			std_in;
	int			std_out;
	int			shlvl;
	char		**path;
	t_env		*env;
	bool		pipe_before;
	int			pipe;
	pid_t		last_cmd;
	t_pid		*wait_for_pids;
}	t_minishell;

void	ft_clear_minishell(t_minishell *minishell);
void	ft_exit_minishell(t_minishell *minishell, int status);

void	ft_do_pipe(t_ast *ast, t_minishell *minishell);
int		ft_here_doc(char *limiter, t_minishell *minishell);
void	ft_redir(t_ast *ast, t_minishell *minishell);
void	ft_exec_cmd(t_ast *ast, t_minishell *minishell);
void	ft_exec_ast(t_ast *ast, t_minishell *minishell);
void	ft_exec_line(t_ast *ast, t_minishell *minishell);
void	ft_minishell_input(t_minishell *minishell);
void	ft_init_minishell(char **envp);

# define IN 1
# define OUT 0
# define HERE_DOC_FILE "/tmp/here_doc.tmp"
# define HISTORY_FILE ".minishell_history"

int		ft_dup2_std(int fd, bool in, t_minishell *minishell);
void	ft_reset_stds(t_minishell *minishell);

#endif