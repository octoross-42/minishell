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
	char	*expand;

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
// clean arg en même temps
{
	t_arg	*to_free;
	char	*str;
	int		len;
	int		i;

	if (arg->wildcard)
		return (ft_fail(ERR_PROG, NULL), NULL);
	len = ft_len_arg(arg, minishell);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (ft_fail(ERR_MALLOC, NULL), NULL);
	str[len] = '\0';
	len = 0;
	while (arg)
	{
		// printf("arg->str = %s\n", arg->str);
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

char	**ft_argv_of(t_arg **args, t_minishell *minishell)
// clean arg en même temps
{
	char	**argv;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (args[i])
	{
		// TODO add wildcard here
		if (!args[i]->wildcard)
			len ++;
		i++;
	}
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (ft_fail(ERR_MALLOC, NULL), NULL);
	argv[i] = NULL;
	i = 0;
	while (args[i])
	{
		if (!args[i]->wildcard)
		{
			argv[i] = ft_arg_of(args[i], minishell);
			if (!argv[i])
			{
				ft_free_until((void **)argv, i);
				while (args[i])
					ft_clear_arg(args[i ++]);
				free(args);
				return (NULL);
			}
		}
		i++;
	}
	free(args);
	return (argv);
}
