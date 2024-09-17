/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:26:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/17 11:30:22 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ERR_MALLOC "malloc failed\n"
# define ERR_FORK "fork failed\n"
# define ERR_PATH "No PATH retrieved : malloc failed\n"

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_fail(char *err);
void	ft_free_until(void **data, int n);

char	**ft_split(char const *s, char c);

#endif