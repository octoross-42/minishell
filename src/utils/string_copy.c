/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:28:38 by octoross          #+#    #+#             */
/*   Updated: 2024/09/28 22:28:38 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strncpy(char *restrict dst, const char *restrict src, size_t n)
{
	size_t	i;

	if (!dst)
		return (NULL);
	if (!src)
		return (dst);
	i = 0;
	while (src[i] && (i < n))
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcpy(char *restrict dst, const char *restrict src)
{
	int	i;

	if (!dst)
		return (NULL);
	if (!src)
		return (dst);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		i;
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	duplicate = (char *)malloc(sizeof(char) * (len + 1));
	if (!duplicate)
		return (0);
	duplicate[len] = '\0';
	i = 0;
	while (s[i])
	{
		duplicate[i] = s[i];
		i ++;
	}
	return (duplicate);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*duplicate;
	size_t	i;

	if (!s)
		return (0);
	duplicate = (char *)malloc(sizeof(char) * (n + 1));
	if (!duplicate)
		return (0);
	duplicate[n] = '\0';
	i = 0;
	while (s[i] && (i < n))
	{
		duplicate[i] = s[i];
		i ++;
	}
	return (duplicate);
}
