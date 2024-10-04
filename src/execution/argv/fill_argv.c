/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 02:44:41 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 02:44:41 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_argv_wildcard(char **argv, t_wildcard *wildcard)
{
	t_wildcard		*next;
	int				i;

	i = 0;
	while (wildcard)
	{
		argv[i ++] = wildcard->file;
		next = wildcard->next;
		free(wildcard);
		wildcard = next;
	}
	return (i);
}

int	ft_argv_add_wildcard(char **argv, t_wildcard_arg **wildcards)
{
	t_wildcard_arg	*next;
	t_wildcard_arg	*to_free;
	int				i;

	next = *wildcards;
	*wildcards = (*wildcards)->next;
	i = 0;
	while (next)
	{
		to_free = next;
		next = next->next;
		if (to_free->is_single)
			argv[i ++] = (char *)to_free->data;
		else
			i += ft_fill_argv_wildcard(argv + i, (t_wildcard *)(to_free->data));
		free(to_free);
	}
	return (i);
}

bool	ft_argv_add_arg(char **argv, t_arg **args, int i, t_minishell *minishell)
{
	*argv = ft_arg_of(args[i], minishell);
	if (!(*argv))
	{
		while (args[i])
			ft_clear_arg(args[i ++]);
		free(args);
		return (false);
	}
	return (true);
}
