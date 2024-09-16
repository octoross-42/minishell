/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:31:32 by octoross          #+#    #+#             */
/*   Updated: 2024/09/16 20:12:13 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(void)
{
	char	wd[PATH_SIZE];
	char	*prompt;
	int		len;
	int		err;

	len = ft_strlen("🐳 minishell:") + ft_strlen(CYAN) + ft_strlen(END) + 2;
	err = 0;
	if (!getcwd(wd, PATH_SIZE))
	{
		len += ft_strlen(ERR_GETCWD);
		err = 1;
	}
	else
		len += ft_strlen(wd) + ft_strlen(BLUE);
	prompt = (char *)malloc(sizeof(char) * (len + 1));
	if (!prompt)
		return (ft_fail(ERR_MALLOC), NULL);
	prompt[len] = '\0';
	ft_strcpy(prompt, CYAN);
	len = ft_strlen(CYAN);
	ft_strcpy(&prompt[len], "🐳 minishell:");
	len += ft_strlen("🐳 minishell:");
	if (!err)
	{
		ft_strcpy(&prompt[len], BLUE);
		len += ft_strlen(BLUE);
		ft_strcpy(&prompt[len], wd);
		len += ft_strlen(wd);
		ft_strcpy(&prompt[len], END);
		len += ft_strlen(END);
	}
	else
	{
		ft_strcpy(&prompt[len], END);
		len += ft_strlen(END);
		ft_strcpy(&prompt[len], ERR_GETCWD);
		len += ft_strlen(ERR_GETCWD);
	}
	ft_strcpy(&prompt[len], "> ");
	return (prompt);
}

void	ft_input_minishell(void)
{
	char	*prompt;
	char	*line;

	prompt = ft_get_prompt();
	if (!prompt)
		exit (EXIT_FAILURE);
	line = readline(prompt);
	free(prompt);
	free(line);
}
