/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:52:05 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 19:52:05 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv, t_ast *next, t_minishell *minishell)
{
	ft_free_until((void **)argv, -1);
	ft_clear_ast(next);
	ft_exit_minishell(minishell, minishell->status);
}
