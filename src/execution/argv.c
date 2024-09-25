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

char	*ft_env(char *name)
{
	return ("TO_EXPAND");
}

int	ft_len_targ(t_arg *arg)
{
	int		len;
	char	*expand;

	len = 0;
	while (arg)
	{
		if (arg->expand)
		{
			expand = ft_env(arg->str);
			free(arg->str);
			arg->str = expand;
		}
		if (arg->str)
			len += ft_strlen(arg->str);
		arg = arg->next;
	}
	return (len);
}

char	*ft_arg_of(t_arg *arg)
// clean arg en même temps
{
	t_arg	*to_free;
	char	*str;
	int		len;
	int		i;

	if (arg->wildcard)
		return (ft_fail(ERR_PROG, NULL), NULL);
	len = ft_len_targ(arg);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (ft_fail(ERR_MALLOC, NULL), NULL);
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

char	**ft_argv_of(t_arg **arg)
// clean arg en même temps
{
	char	**argv;
	int		i;

	i = 0;
	while (arg[i])
	{
		// TODO add wildcard here
		i++;
	}
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (ft_fail(ERR_MALLOC, NULL), NULL);
	argv[i] = NULL;
	i = 0;
	while (arg[i])
	{
		argv[i] = ft_arg_of(arg[i]);
		if (!argv[i])
		{
			ft_free_until((void **)argv, i);
			while (arg[i])
				ft_clear_arg(arg[i ++]);
			free(arg);
			return (NULL);
		}
		i++;
	}
	free(arg);
	return (argv);
}
