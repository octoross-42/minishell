/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:26:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/29 17:48:07 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define PIPE 1
# define OR 2
# define AND 3
# define INPUT 4
# define OUTPUT 5
# define HERE_DOC 6
# define APPEND 7
# define CMD 8
# define SUBSHELL 9

# define STATUS_OK 0
# define STATUS_PROG 1
# define STATUS_REDIR 1
# define STATUS_SYNTAX 2
# define STATUS_FORK 71
# define STATUS_DUP2 71
# define STATUS_PIPE 71
# define STATUS_OPEN 66
# define STATUS_CMD 126
# define STATUS_EXECVE 127
# define STATUS_MALLOC 137

# define ERR_MALLOC "malloc failed : %s\n"
# define ERR_REDIR "ambiguous redirection\n"
# define ERR_FAIL "%s failed\n"
# define ERR_FORK "fork failed\n"
# define ERR_PIPE "Pipe failed\n"
# define ERR_DUP2 "dup2 failed\n"
# define ERR_CMD "%s: command not found\n"
# define ERR_EXPAND "%s could not be expanded : malloc failed\n"
# define ERR_PATH "No PATH retrieved : malloc failed\n"
# define ERR_ENV "Warning : No env retrieved\n"
# define ERR_PARSING_ENV "Error : env is badly parsed\n"
# define ERR_PROG "Bad programming happenned :(\n"

size_t	ft_strlen(const char *s);
size_t	ft_ptrslen(void **s);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
char	*ft_strncpy(char *restrict dst, const char *restrict src, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	ft_isdigit(int c);
bool	ft_isalpha(int c);
bool	ft_isspace(char c);
bool	ft_isname(char c);

char	*ft_itoa(int n);

void	ft_fail(char *err, void *err_value);
void	ft_free_until(void **data, int n);

char	**ft_split(char const *s, char c);
char	*ft_err(char *err, char *s);

bool	ft_char_is_quote(char c);
bool	ft_char_is_token(char c);
char	*ft_str_of_token(int token);
char	*ft_name_of_token(int token);
int		ft_token_of_str(char *token);
int		ft_get_next_token(char *s);

char	*ft_build_path(char const *path, char const *file);
char	*ft_build_dir_path(char const *path, char const *file);

#endif