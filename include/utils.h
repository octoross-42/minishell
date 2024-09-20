/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:26:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/19 20:50:24 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define EXIT_MALLOC 1
# define EXIT_FORK 1
# define EXIT_AST 1
# define EXIT_TOKEN 1
# define EXIT_SUCCESS 0

# define ERR_PROG "Bad programming happenned :(\n"
# define ERR_MALLOC "malloc failed\n"
# define ERR_FORK "fork failed\n"
# define ERR_PATH "No PATH retrieved : malloc failed\n"

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
char	*ft_strncpy(char *restrict dst, const char *restrict src, size_t n);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	ft_isdigit(int c);
bool	ft_isalpha(int c);
bool	ft_isspace(char c);
bool	ft_isname(char c);

void	ft_fail(char *err);
void	ft_free_until(void **data, int n);

char	**ft_split(char const *s, char c);
char	*ft_err(char *err, char *s);

bool	ft_char_is_quote(char c);
bool	ft_char_is_token(char c);

#endif