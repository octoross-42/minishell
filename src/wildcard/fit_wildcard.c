/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:22:30 by octoross          #+#    #+#             */
/*   Updated: 2024/09/27 21:22:30 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

bool	ft_check_ends(char **s, int *end_s, char **regex, int *end_regex)
{
	int	start;

	start = 0;
	if (!s || !regex)
		return (false);
	while ((start < *end_regex) && (*regex)[start] && ((*regex)[start] != '*'))
	{
		if ((*s)[start] != (*regex)[start])
			return (false);
		start ++;
	}
	*s += start;
	*regex += start;
	*end_regex -= start;
	*end_s = strlen(*s);
	while ((*regex)[*end_regex - 1] && ((*regex)[*end_regex - 1] != '*'))
	{
		if ((*s)[*end_s - 1] != (*regex)[*end_regex - 1])
			return (false);
		(*end_regex)--;
		(*end_s)--;
	}
	return (true);
}

bool	ft_fit_wildcard(char *s, char *regex, int end_regex)
{
	int	end_s;
	int	i;
	int	j;
	int	len_need;

	if (!s || !regex)
		return (false);
	if ((*s == '.') && (*regex != '.'))
		return (false);
	if (!ft_check_ends(&s, &end_s, &regex, &end_regex))
		return (false);
	if (!(*regex))
		return (true);
	i = 0;
	j = 0;
	while (regex[i] && (i < end_regex))
	{
		if (regex[i] == '*')
			i ++;
		else
		{
			len_need = 0;
			while (regex[i + len_need] && (regex[i + len_need] != '*') && (len_need + j <= end_s))
				len_need ++;
			while ((len_need + j <= end_s) && strncmp(s + j, regex + i, len_need))
				j ++;
			if (len_need + j > end_s)
				return (false);
			i += len_need;
		}
	}
	return (true);
}
