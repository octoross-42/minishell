/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/21 21:56:16 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexer.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len ++;
	return (len);
}

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
