/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:08:57 by octoross          #+#    #+#             */
/*   Updated: 2024/09/27 21:08:57 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H

# define WILDCARD_H

# include "minishell.h"

# include <dirent.h>
# include <sys/stat.h>

typedef struct s_str
{
	char	*s;
	int		end;
}	t_str;

bool			ft_check_ends(char **s, int *end_s, \
		char **regex, int *end_regex);
bool			ft_fit_wildcard(char *s, char *regex, int end_regex);

typedef struct s_wildcard
{
	char				*file;
	struct s_wildcard	*next;
	struct s_wildcard	*last;
}	t_wildcard;

t_wildcard	*ft_new_wildcard(char *name, char *path, bool dir);
void		ft_add_wildcard(t_wildcard **wildcard, t_wildcard *new);
void		ft_clear_wildcard(t_wildcard *wildcard);
int			ft_len_wildcard(t_wildcard *wildcard);
t_wildcard	*ft_wildcard(char *regex, char *path);
char		**ft_argv_wildcard(t_wildcard *wildcard);

typedef struct s_wildcards
{
	char				**files;
	struct s_wildcards	*next;
}	t_wildcards;

void	ft_clear_wildcards(t_wildcards *wildcards);
bool	ft_add_wildcards(char **argv, t_wildcards **wildcards, t_wildcards **last);

#endif
