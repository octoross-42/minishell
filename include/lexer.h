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

# define PIPE 1
# define OR 2
# define AND 3
# define INPUT 4
# define OUTPUT 5
# define HERE_DOC 6
# define APPEND 7
# define CMD 8

typedef struct s_lexer
{
	void			*data;
	char			token;
	struct	s_lexer	*next;
}	t_lexer;

// AST tree
typedef struct t_ast
{
	int				token;
	void			*data;
	t_lexer_tree	*left;
	t_lexer_tree	*right;
}	t_ast;

#endif
