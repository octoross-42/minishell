/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/29 02:32:55 by octoross         ###   ########.fr       */
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

char	*ft_build_path(char const *path, char const *file)
{
	int		len;
	int		i;
	char	*concatenated;

	if (!path && !file)
		return (NULL);
	len = ft_strlen(path);
	if (path && path[len - 1] != '/')
		len ++;
	len += ft_strlen(file);
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (NULL);
	concatenated[len] = '\0';
	i = 0;
	while (path && path[i])
	{
		concatenated[i] = path[i];
		i ++;
	}
	if (path && *path && concatenated[i - 1] != '/')
		concatenated[i ++] = '/';
	len = i;
	while (file[i - len])
	{
		concatenated[i] = file[i - len];
		i ++;
	}
	return (concatenated);
}

char	*ft_build_dir_path(char const *path, char const *file)
{
	int		len;
	int		i;
	char	*concatenated;

	len = ft_strlen(path);
	if (path && (len > 0) && path[len - 1] != '/')
		len ++;
	len += ft_strlen(file) + 1;
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (NULL);
	concatenated[len - 1] = '/';
	concatenated[len] = '\0';
	i = 0;
	while (path && path[i])
	{
		concatenated[i] = path[i];
		i ++;
	}
	if (path && *path && concatenated[i - 1] != '/')
		concatenated[i ++] = '/';
	len = i;
	while (file[i - len])
	{
		concatenated[i] = file[i - len];
		i ++;
	}
	return (concatenated);
}
