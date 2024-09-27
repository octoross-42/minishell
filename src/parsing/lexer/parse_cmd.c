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

static int	ft_init_parsing_cmd(char *s, t_arg ***args)
{
	int	nbr_args;

	if (!args)
		return (ft_fail(ERR_PROG, NULL), STATUS_PROG);
	nbr_args = ft_nbr_args(&s);
	if (nbr_args < 0)
		return (ft_fail(ERR_SYNTAX, "newline"), STATUS_SYNTAX);
	*args = (t_arg **)malloc((nbr_args + 1) * sizeof(t_arg *));
	if (!(*args))
		return (ft_fail(ERR_MALLOC, NULL), STATUS_MALLOC);
	(*args)[nbr_args] = NULL;
	return (STATUS_OK);
}

int	ft_parse_cmd(char **s, t_lexer *lexer)
{
	int			status;
	int			nbr_args;
	t_arg		**args;

	lexer->token = CMD;
	args = NULL;
	status = ft_init_parsing_cmd(*s, &args);
	if (status != STATUS_OK)
		return (status);
	nbr_args = 0;
	while (**s && !ft_char_is_token(**s))
	{
		status = ft_parse_arg(s, &(args[nbr_args]));
		if (status != STATUS_OK)
			return (status);
		while (ft_isspace(**s))
			(*s)++;
		nbr_args ++;
	}
	lexer->data = (void *)args;
	return (STATUS_OK);
}
