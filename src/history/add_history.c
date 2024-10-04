/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:29:43 by octoross          #+#    #+#             */
/*   Updated: 2024/09/25 12:29:43 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_history(char *line, int history)
{
	if (!line || !(*line))
		return ;
	add_history(line);
	if (history < 0)
		return ;
	write(history, line, ft_strlen(line));
	write(history, "\n", 1);
}

void	print_history_restory(void)
{
	printf("%s%s * %s History restored  %s\n", BLACK, BG_WHITE, BG_CYAN, END);
}

char	*gnl_without_newline(int history)
{
	char	*line;

	line = gnl(history);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	ft_restore_history(t_minishell *minishell)
{
	char	*line;

	line = gnl_without_newline(minishell->history);
	while (line)
	{
		add_history(line);
		free(line);
		line = gnl_without_newline(minishell->history);
	}
	close(minishell->history);
	print_history_restory();
}

void	ft_load_history(t_minishell *minishell)
{
	char	*history_path;
	char	*home_path;

	home_path = ft_get_env_value("HOME", minishell->env);
	history_path = ft_build_path(home_path, HISTORY_FILE, 0);
	minishell->history = open(history_path, O_RDONLY | O_CREAT, 0644);
	if (minishell->history < 0)
	{
		free(history_path);
		ft_fail(ERR_HISTORY, NULL);
		return ;
	}
	ft_restore_history(minishell);
	minishell->history = open(history_path, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(history_path);
	if (minishell->history < 0)
		ft_fail(ERR_HISTORY_WRITE, NULL);
}
