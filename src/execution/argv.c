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

int	ft_len_arg(t_arg *arg, t_minishell *minishell)
{
	int		len;

	len = 0;
	while (arg)
	{
		if (arg->expand)
			ft_expand(arg, minishell);
		if (arg->str)
			len += ft_strlen(arg->str);
		arg = arg->next;
	}
	return (len);
}

char	*ft_arg_of(t_arg *arg, t_minishell *minishell)
{
	t_arg	*to_free;
	char	*str;
	int		len;
	int		i;

	len = ft_len_arg(arg, minishell);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (ft_fail(ERR_MALLOC, "no arg"), NULL);
	str[len] = '\0';
	len = 0;
	while (arg)
	{
		i = 0;
		while (arg->str && arg->str[i])
			str[len ++] = arg->str[i ++];
		if (arg->str && !arg->expand)
			free(arg->str);
		to_free = arg;
		arg = arg->next;
		free(to_free);
	}
	return (str);
}

int	ft_len_argv(t_arg **args, t_wildcards **wildcards, t_minishell *minishell)
{
	int			len;
	int			i;
	char		**argv;
	char		*path;
	t_wildcards	*last;
	t_arg		*targ;

	len = 0;
	i = 0;
	last = NULL;
	*wildcards = NULL;
	while (args[i])
	{
		if (args[i]->wildcard)
		{
			path = ft_arg_of(args[i], minishell);
			args[i] = NULL;
			if (!path)
				return (ft_clear_wildcards(*wildcards), -1);
			argv = ft_argv_wildcard(ft_wildcard(path, NULL));
			if (!argv)
				return (free(path), ft_clear_wildcards(*wildcards), -1);
			if (!(*argv))
			{
				targ = NULL;
				if (!ft_add_new_arg(&targ, &targ))
					return (free(path), ft_clear_wildcards(*wildcards), -1);
				targ->str = path;
				args[i] = targ;
				free(argv);
				len ++;
			}
			else
			{
				free(path);
				if (!ft_add_wildcards(argv, wildcards, &last))
					return (ft_clear_wildcards(*wildcards), ft_free_until((void **)argv, -1), -1);
				len += ft_ptrslen((void **)last->files);
			}
		}
		else	
			len ++;
		i ++;
	}
	return (len);
}

char	**ft_argv_of(t_arg **args, t_minishell *minishell)
{
	char		**argv;
	t_wildcards	*wildcards;
	t_wildcards	*next;
	int			i;
	int			j;
	int			len_args;
	int			len_argv;

	len_args = ft_ptrslen((void **)args);
	len_argv = ft_len_argv(args, &wildcards, minishell);
	if (len_argv < 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (len_argv + 1));
	if (!argv)
		return (ft_fail(ERR_MALLOC, "no arg"), NULL);
	argv[len_argv] = NULL;
	len_argv = 0;
	i = 0;
	while (i < len_args)
	{
		if (args[i])
		{
			argv[len_argv] = ft_arg_of(args[i], minishell);
			if (!argv[len_argv])
			{
				ft_free_until((void **)argv, i);
				while (args[i])
					ft_clear_arg(args[i ++]);
				free(args);
				return (NULL);
			}
			len_argv ++;
		}
		else
		{
			next = wildcards->next;
			j = 0;
			while (wildcards->files[j])
				argv[len_argv ++] = wildcards->files[j ++];
			free(wildcards->files);
			free(wildcards);
			wildcards = next;
		}
		i ++;
	}
	free(args);
	return (argv);
}
