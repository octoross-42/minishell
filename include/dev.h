/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:21:14 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 16:07:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H

# define DEV_H

# include "lexer.h"
# include <string.h>

char	*ft_str_of_token(int token);
int		ft_token_of_str(char *token);
void	print_ast(t_ast *ast, int n);
void	print_lexer(t_lexer *lexer);

#endif