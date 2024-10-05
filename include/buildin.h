/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:45:44 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 21:45:44 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H

# define BUILDIN_H

typedef struct s_ast t_ast;
typedef struct s_env t_env;
typedef struct s_minishell t_minishell;

bool	ft_is_buildin(char *cmd);
void	ft_buildin(char **argv, t_ast *next, t_minishell *minishell);

void	print_echo(char **arg);
void	print_env(t_env *ep, bool export);
int		print_wd(t_env **ep);
int		change_dir(char **arg, t_env **env);
int		ft_export(char **arg, t_minishell *minishell);
void	unset_var(char **arg, t_minishell *minishell);
void	ft_exit(char **argv, t_ast *next, t_minishell *minishell);

#endif