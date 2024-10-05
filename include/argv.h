/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:55:50 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 21:55:50 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H

# define ARGV_H

#include <stdbool.h>

typedef struct s_arg		t_arg;
typedef struct s_wildcard	t_wildcard;
typedef struct s_minishell	t_minishell;

void			ft_expand(t_arg *arg, t_minishell *minishell);
char			*ft_arg_of(t_arg *arg, t_minishell *minishell);
char			**ft_argv_of(t_arg **args, t_minishell *minishell);

typedef struct s_wildcard_arg
{
	void					*data;
	bool					is_single;
	struct s_wildcard_arg	*next;
}	t_wildcard_arg;

void			ft_clear_wildcard_arg(t_wildcard_arg *wildcards);
bool			ft_add_wildcard_arg(void *data, t_wildcard_arg **wildcards, t_wildcard_arg **last);

t_wildcard_arg	*ft_wilcard_arg(char *arg);
int				ft_add_new_wildcard_arg(t_arg *data, t_minishell *minishell, \
					t_wildcard_arg **wildcards, t_wildcard_arg **last);
char			*ft_file_arg(t_arg *data, t_minishell *minishell);


int				ft_fill_argv_wildcard(char **argv, t_wildcard *wildcard);
int				ft_argv_add_wildcard(char **argv, t_wildcard_arg **wildcards);
bool			ft_argv_add_arg(char **argv, t_arg **args, int i, t_minishell *minishell);

#endif