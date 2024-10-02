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

typedef struct s_wildcard_data
{
	char	*regex;
	int		end;
	int		end_slash;
	int		slash;
	int		entry_is_dir;
	char	*name;
	int		end_name;
	char	*path;
} t_wildcard_data;

bool	ft_check_ends(t_wildcard_data *data);
bool	ft_fit_wildcard(t_wildcard_data data);

typedef struct s_wildcard
{
	char				*file;
	struct s_wildcard	*next;
	struct s_wildcard	*last;
}	t_wildcard;

t_wildcard	*ft_new_wildcard(t_wildcard_data data);
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
