/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 12:29:55 by octoross         ###   ########.fr       */
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

char	*ft_init_build_path(char const *path, \
	int len_path, int len_file, int slash)
{
	int		len;
	char	*new_path;

	len = len_file + len_path;
	if (path && path[len_path - 1] != '/')
		len ++;
	len += slash;
	new_path = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_path)
		return (NULL);
	new_path[len] = '\0';
	return (new_path);
}

char	*ft_build_path(char const *path, char const *file, int slash)
{
	int		len;
	int		len_path;
	int		len_file;
	int		i;
	char	*new_path;

	len_path = ft_strlen(path);
	len_file = ft_strlen(file);
	new_path = ft_init_build_path(path, len_path, len_file, slash);
	if (!new_path)
		return (NULL);
	len = 0;
	ft_strncpy(new_path, path, len_path);
	len += len_path;
	if (path && *path && new_path[len - 1] != '/')
		new_path[len ++] = '/';
	ft_strncpy(&new_path[len], file, len_file);
	len += len_file;
	i = 0;
	while (i < slash)
	{
		new_path[len ++] = '/';
		i ++;
	}
	return (new_path);
}
