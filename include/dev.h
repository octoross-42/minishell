/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:21:14 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 21:48:24 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H

# define DEV_H

# include "minishell.h"

void	print_ast(t_ast *ast, int n);
void	print_lexer(t_lexer *lexer);

#endif