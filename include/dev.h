/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:21:14 by octoross          #+#    #+#             */
/*   Updated: 2024/09/15 20:07:54 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H

# define DEV_H

# include "lexer.h"
# include <string.h>

char	*str_of_token(int token);
int		token_of_str(char *token);
void	print_ast(t_ast *ast, int n);
void	printf_lexer(t_lexer *lexer);

#endif