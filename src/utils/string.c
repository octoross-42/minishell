/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:41 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 19:42:41 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

size_t	ft_ptrslen(void **s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len ++;
	return (len);
}

int	ft_strcmp(const char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i ++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && i < n && s1[i] == s2[i])
		i ++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	atoied;
	int	i;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	atoied = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i ++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i ++;
	}
	while (ft_isdigit(nptr[i]))
	{
		atoied = atoied * 10 + (nptr[i] - '0');
		i ++;
	}
	return (atoied * sign);
}
