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

bool			ft_check_ends(char **s, int *end_s, \
		char **regex, int *end_regex);
bool			ft_fit_wildcard(char *s, char *regex, int end_regex);

typedef struct s_wildcard
{
	char				*file;
	struct s_wildcard	*next;
}	t_wildcard;

typedef struct s_wildcards
{
	t_wildcard			*files;
	struct s_wildcards	*next;
}	t_wildcards;

#endif
