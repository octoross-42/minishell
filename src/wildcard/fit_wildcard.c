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

bool	ft_check_ends(t_wildcard_data *data)
{
	while (*(data->regex) && (*(data->regex) != '*') && (data->end > 0))
	{
		if (*(data->name ++) != *(data->regex ++))
			return (false);
		data->end --;
	}
	data->end_name = ft_strlen(data->name);
	while ((data->end_name > 0) && (data->end > 0)
		&& ((data->regex)[data->end - 1] != '*'))
	{
		if ((data->name)[data->end_name - 1] != (data->regex)[data->end - 1])
			return (false);
		(data->end)--;
		(data->end_name)--;
	}
	if (!data->end_name && (data->end > 0))
		return (false);
	return (true);
}

bool	ft_fit_word(t_wildcard_data *data)
{
	int	len_need;

	len_need = 0;
	while ((data->regex)[len_need]
		&& ((data->regex)[len_need] != '*') && (data->end_name >= len_need))
		len_need ++;
	while ((data->end_name >= len_need)
		&& ft_strncmp(data->name, data->regex, len_need))
	{
		(data->name)++;
		(data->end_name)--;
	}
	if (data->end_name < len_need)
		return (false);
	return (true);
}

bool	ft_fit_wildcard(t_wildcard_data data)
{
	if (!(data.name) || !data.regex)
		return (false);
	if ((*(data.name) == '.') && (*data.regex != '.'))
		return (false);
	if (!ft_check_ends(&data))
		return (false);
	if (!(*(data.regex)))
		return (true);
	while (*(data.regex) && (data.end > 0))
	{
		if (*(data.regex) == '*')
		{
			data.regex ++;
			data.end --;
		}
		else
		{
			if (!ft_fit_word(&data))
				return (false);
		}
	}
	return (true);
}
