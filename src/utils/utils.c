/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 00:18:49 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexer.h"

void	ft_free_until(void **data, int n)
{
	int		i;
	char	**str;

	if (!data)
		return ;
	i = 0;
	if (n == -1)
	{
		str = (char **)data;
		while (str[i])
			free(str[i ++]);
		free(str);
		return ;
	}
	while (i < n)
		free(data[i ++]);
	free(data);
}

void	ft_fail(char *err, void *err_value)
{
	char	*str;

	write(STDERR_FILENO, "minishell: ", 11);
	while (*err && (*err != '%'))
		write(STDERR_FILENO, err++, 1);
	if (*err == '%')
	{
		err ++;
		if (*(err ++) == 's')
		{
			str = (char *)err_value;
			while (str && *str)
				write(STDERR_FILENO, str++, 1);
		}
	}
	if (*err)
		write(STDERR_FILENO, err, ft_strlen(err));
}

char	*ft_str_of_token(int token)
{
	if (token == PIPE)
		return ("PIPE");
	if (token == OR)
		return ("OR");
	if (token == AND)
		return ("AND");
	if (token == INPUT)
		return ("INPUT");
	if (token == OUTPUT)
		return ("OUTPUT");
	if (token == HERE_DOC)
		return ("HERE_DOC");
	if (token == APPEND)
		return ("APPEND");
	if (token == CMD)
		return ("CMD");
	else
		return (NULL);
}

int	ft_token_of_str(char *token)
{
	if (!ft_strcmp(token, "PIPE"))
		return (PIPE);
	if (!ft_strcmp(token, "OR"))
		return (OR);
	if (!ft_strcmp(token, "AND"))
		return (AND);
	if (!ft_strcmp(token, "INPUT"))
		return (INPUT);
	if (!ft_strcmp(token, "OUTPUT"))
		return (OUTPUT);
	if (!ft_strcmp(token, "HERE_DOC"))
		return (HERE_DOC);
	if (!ft_strcmp(token, "APPEND"))
		return (APPEND);
	if (!ft_strcmp(token, "CMD"))
		return (CMD);
	else
		return (0);
}
