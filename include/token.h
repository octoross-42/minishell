/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:37:20 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 21:37:20 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H

# define TOKEN_H

# define SUBSHELL 1
# define PIPE 2
# define OR 3
# define AND 4
# define INPUT 5
# define OUTPUT 6
# define HERE_DOC 7
# define CMD 9
# define APPEND 8
# define END_SUBSHELL 10

bool	ft_token_good(void);

char	*ft_str_of_token(int token);
char	*ft_name_of_token(int token);
int		ft_token_of_str(char *token);

int		ft_get_next_token(char *s);
bool	ft_next_is_token(char *s);
bool	ft_char_is_quote(char c);
bool	ft_is_separator(int token);
bool	ft_is_redir(int token);
bool	ft_is_sep_or_sub(int token);

#endif
