/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:48 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 17:40:34 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H

# define GNL_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_gnl
{
	int				size;
	char			*content;
	int				eof;
	int				eol;
	int				len;
	int				start;
	struct s_gnl	*next;
}		t_gnl;

void	ft_clear_leftovers(t_gnl **leftovers);
void	ft_clean_and_next_lst(t_gnl **line);

char	*gnl(int fd);

#endif