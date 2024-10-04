/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:45:49 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 12:45:49 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_argv(t_arg **args, int len_args, \
	t_wildcard_arg **wildcards, t_minishell *minishell)
{
	int				len;
	int				len_wildcard;
	int				i;
	t_wildcard_arg	*last;

	len = 0;
	i = 0;
	last = NULL;
	*wildcards = NULL;
	while (i < len_args)
	{
		if (args[i]->wildcard)
		{
			len_wildcard = ft_add_new_wildcard_arg(args[i], \
								minishell, wildcards, &last);
			args[i] = NULL;
			if (len_wildcard < 0)
				return (ft_clear_args(args, len_args), -1);
			len += len_wildcard;
		}
		else	
			len ++;
		i ++;
	}
	return (len);
}

char	**ft_init_argv(t_arg **args, int *len_args, t_wildcard_arg **wildcards, t_minishell *minishell)
{
	int		len_argv;
	char	**argv;

	*len_args = ft_ptrslen((void **)args);
	len_argv = ft_len_argv(args, *len_args, wildcards, minishell);
	if (len_argv < 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (len_argv + 1));
	if (!argv)
		return (ft_fail(ERR_MALLOC, "no arg"), NULL);
	argv[len_argv] = NULL;
	return (argv);
}

char	**ft_argv_of(t_arg **args, t_minishell *minishell)
{
	char			**argv;
	t_wildcard_arg	*wildcards;
	int				i;
	int				j;
	int				len_args;

	argv = ft_init_argv(args, &len_args, &wildcards, minishell);
	i = 0;
	j = 0;
	while (i < len_args)
	{
		if (args[i])
		{
			if (!ft_argv_add_arg(&argv[j ++], args, i, minishell))
				return (ft_free_until((void **)argv, j - 1), NULL);
		}
		else
			j += ft_argv_add_wildcard(argv + j, &wildcards);
		i ++;
	}
	free(args);
	return (argv);
}
