/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/10/02 20:07:57 by octoross         ###   ########.fr       */
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

char	*ft_build_path(char const *path, char const *file, int slash)
{
	int		len;
	int		len_path;
	int		len_file;
	int		i;
	char	*concatenated;

	if (!path && !file)
		return (NULL);
	len_path = ft_strlen(path);
	len_file = ft_strlen(file);
	len = len_file + len_path;
	if (path && path[len_path - 1] != '/')
		len ++;
	len += slash;
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (NULL);
	concatenated[len] = '\0';
	len = 0;
	ft_strncpy(concatenated, path, len_path);
	len += len_path;
	if (path && *path && concatenated[len - 1] != '/')
		concatenated[len ++] = '/';
	ft_strncpy(&concatenated[len], file, len_file);
	len += len_file;
	i = 0;
	while (i < slash)
	{
		concatenated[len ++] = '/';
		i ++;
	}
	return (concatenated);
}
