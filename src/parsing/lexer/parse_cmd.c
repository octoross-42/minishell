/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:35:45 by octoross          #+#    #+#             */
/*   Updated: 2024/09/18 21:35:45 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_nbr_args(char **s)
{
	int		nbr_args;
	char	quote;
	int		i;

	i = 0;
	nbr_args = 0;
	while ((*s)[i] && !ft_char_is_token((*s)[i]))
	{
		nbr_args ++;
		while ((*s)[i] && !ft_isspace((*s)[i]) && !ft_char_is_token((*s)[i]))
		{
			if (ft_char_is_quote((*s)[i ++]))
			{
				quote = (*s)[i - 1];
				while ((*s)[i] && ((*s)[i] != quote))
					i ++;
				if ((*s)[i ++] != quote)
					return (*s += (i - 1), -1);
			}
		}
		while (ft_isspace((*s)[i]))
			i ++;
	}
	return (nbr_args);
}

bool	ft_init_parsing_cmd(char *s, char ***args)
{
	int	nbr_args;

	if (!args)
		return (ft_fail(ERR_PROG, NULL), false);
	nbr_args = ft_nbr_args(&s);
	if (nbr_args <= 0)
		return (ft_fail(ERR_SYNTAX, s), false);
	*args = (char **)malloc((nbr_args + 1) * sizeof(char *));
	if (!(*args))
		return (ft_fail(ERR_MALLOC, NULL), false);
	(*args)[nbr_args] = NULL;
	return (true);
}

bool	ft_parse_cmd(char **s, t_lexer *lexer)
{
	int			nbr_args;
	int			len;
	char		**args;

	lexer->token = CMD;
	args = NULL;
	if (!ft_init_parsing_cmd(*s, &args))
		return (false);
	nbr_args = 0;
	while (**s && !ft_char_is_token(**s))
	{
		if (!ft_parse_arg(s, &(args[nbr_args])))
			return (ft_free_until((void **)args, nbr_args), false);
		while (ft_isspace(**s))
			(*s)++;
		nbr_args ++;
	}
	lexer->data = (void *)args;
	return (true);
}
