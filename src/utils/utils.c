/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:30:08 by octoross          #+#    #+#             */
/*   Updated: 2024/09/18 18:36:55 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void	ft_fail(char *err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, err, ft_strlen(err));
}

char	*ft_err(char *err, char *s)
{
	char	*error;
	int		i;
	int		j;

	i = 0;
	while (err[i] && (err[i] != '%'))
		i ++;
	j = i;
	if (err[i] != 's')
		return (err);
	error = (char *)malloc(sizeof(char) * (i + 1));
	if (!err)
		return (ft_fail(ERR_MALLOC), err);
	return (error);
}