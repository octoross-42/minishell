/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:56:56 by octoross          #+#    #+#             */
/*   Updated: 2024/09/06 14:56:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# define UNDEFINED 0
# define QUOTE 1
# define DOUBLE 2
# define EXPAND 3
# define PIPE 4
# define INPUT 5
# define OUTPUT 6
# define HERE_DOC 7
# define APPEND 8
# define FILE 9
# define CMD 10
# define ARG 11

typedef struct s_lexer
{
	void			*data;
	char			token;
	struct	s_lexer	*next;
}	t_lexer;

// AST tree
typedef struct s_lexer_tree
{
	int				token;
	void			*data;
	t_lexer_tree	*left;
	t_lexer_tree	*right;
}	t_lexer_tree;

#endif