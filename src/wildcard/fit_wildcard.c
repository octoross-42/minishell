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

bool	ft_check_ends(t_str *file, t_str *regex)
{
	int	start;

	start = 0;
	if (!file->s || !regex->s)
		return (false);
	while ((start < regex->end) && (regex->s)[start] && ((regex->s)[start] != '*'))
	{
		if ((file->s)[start] != (regex->s)[start])
			return (false);
		start ++;
	}
	file->s += start;
	regex->s += start;
	regex->end -= start;
	file->end = ft_strlen(file->s);
	while ((regex->s)[regex->end - 1] && ((regex->s)[regex->end - 1] != '*'))
	{
		if ((file->s)[file->end - 1] != (regex->s)[regex->end - 1])
			return (false);
		(regex->end)--;
		(file->s)--;
	}
	return (true);
}

bool	ft_fit_wildcard(char *filestr, t_str regex)
{
	t_str	file;
	int		r;
	int		f;
	int		len_need;

	file.s = filestr;
	if (!file.s || !regex.s)
		return (false);
	if ((*file.s == '.') && (*regex.s != '.'))
		return (false);
	if (!ft_check_ends(&file, &regex))
		return (false);
	if (!(*regex.s))
		return (true);
	r = 0;
	f = 0;
	while (regex.s[r] && (r < regex.end))
	{
		if (regex.s[r] == '*')
			r ++;
		else
		{
			len_need = 0;
			while (regex.s[r + len_need] && (regex.s[r + len_need] != '*') && (len_need + f <= file.end))
				len_need ++;
			while ((len_need + f <= file.end) && ft_strncmp(file.s + f, regex.s + r, len_need))
				f ++;
			if (len_need + f > file.end)
				return (false);
			r += len_need;
		}
	}
	return (true);
}
