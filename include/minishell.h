/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:55 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 02:45:49 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "utils.h"
# include "ast.h"
# include "display.h"
# include "wildcard.h"

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

# define IN 1
# define OUT 0

int		ft_dup2_std(int fd, bool in, t_minishell *minishell);
void	ft_reset_stds(t_minishell *minishell);


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
void	ft_init_minishell(char **envp);


void	print_echo(char **arg);
void	print_env(t_env *ep);
int		print_wd(t_env *ep);
int		change_dir(char **arg, t_env *env);

typedef struct s_wildcard_arg
{
	void					*data;
	bool					is_single;
	struct s_wildcard_arg	*next;
}	t_wildcard_arg;

void	ft_clear_wildcard_arg(t_wildcard_arg *wildcards);
bool	ft_add_wildcard_arg(void *data, t_wildcard_arg **wildcards, t_wildcard_arg **last);

t_wildcard_arg	*ft_wilcard_arg(char *arg);
int	ft_add_new_wildcard_arg(t_arg *data, t_minishell *minishell, t_wildcard_arg **wildcards, t_wildcard_arg **last);
char			*ft_file_arg(t_arg *data, t_minishell *minishell);


int	ft_fill_argv_wildcard(char **argv, t_wildcard *wildcard);
int	ft_argv_add_wildcard(char **argv, t_wildcard_arg **wildcards);
bool	ft_argv_add_arg(char **argv, t_arg **args, int i, t_minishell *minishell);

#endif