/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:26:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/16 21:12:20 by octoross         ###   ########.fr       */
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

int		ft_strlen(const char *str);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
void	ft_fail(char *err);
void	ft_free_until(void **data, int n);

char	**ft_split(char const *s, char c);

#endif