/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:15:32 by octoross          #+#    #+#             */
/*   Updated: 2024/09/30 22:40:37 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_getcwd(void)
{
	char	*buff;
	int		i;

	i = 1;
	buff = malloc(sizeof(char) * BSIZE * i);
	if (!buff)
		return (ft_fail(ERR_MALLOC, "no pwd"), STATUS_MALLOC);
	while (getcwd(buff, BSIZE * i) == NULL)
	{
		free(buff);
		if (errno == ERANGE)
		{
			i ++;
			buff = malloc(sizeof(char) * BSIZE * i);
			if (!buff)
				return (ft_fail(ERR_MALLOC, "no pwd"), STATUS_MALLOC);
		}
		else
			return (perror("pwd"), 1);
	}
	write(STDOUT_FILENO, buff, ft_strlen(buff));
	write(STDERR_FILENO, "\n", 1);
	free(buff);
	return (0);
}

int	print_wd(t_env *ep)
{
	t_env	*cur;

	cur = ep;
	while (cur)
	{
		if (ft_strcmp(cur->name, "PWD"))
			cur = cur->next;
		else
		{
			write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
			write(STDERR_FILENO, "\n", 1);
			return (0);
		}
	}
	return (go_to_getcwd());
}

