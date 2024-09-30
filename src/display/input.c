/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:31:32 by octoross          #+#    #+#             */
/*   Updated: 2024/09/30 22:39:23 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy_prompt(char *prompt, char wd[BSIZE], bool err)
{
	int	i;

	ft_strcpy(prompt, CYAN);
	i = ft_strlen(CYAN);
	ft_strcpy(&prompt[i], "🐳 minishell:");
	i += ft_strlen("🐳 minishell:");
	if (!err)
	{
		ft_strcpy(&prompt[i], BLUE);
		i += ft_strlen(BLUE);
		ft_strcpy(&prompt[i], wd);
		i += ft_strlen(wd);
		ft_strcpy(&prompt[i], END);
		i += ft_strlen(END);
	}
	else
	{
		ft_strcpy(&prompt[i], END);
		i += ft_strlen(END);
		ft_strcpy(&prompt[i], ERR_GETCWD);
		i += ft_strlen(ERR_GETCWD);
	}
	ft_strcpy(&prompt[i], "> ");
}

char	*ft_get_prompt(void)
{
	char	wd[BSIZE];
	char	*prompt;
	int		len;
	bool	err;

	len = ft_strlen("🐳 minishell:") + ft_strlen(CYAN) + ft_strlen(END) + 2;
	err = false;
	if (!getcwd(wd, BSIZE))
	{
		len += ft_strlen(ERR_GETCWD);
		err = true;
	}
	else
		len += ft_strlen(wd) + ft_strlen(BLUE);
	prompt = (char *)malloc(sizeof(char) * (len + 1));
	if (!prompt)
		return (ft_fail(ERR_MALLOC, "no prompt"), NULL);
	prompt[len] = '\0';
	ft_strcpy_prompt(prompt, wd, err);
	return (prompt);
}

#include "dev.h"

void	ft_minishell_input(t_minishell *minishell)
{
	char	*prompt;
	char	*line;
	t_lexer	*lexer;
	t_ast	*ast;

	prompt = ft_get_prompt();
	if (!prompt)
		line = readline("🐳 minishell> ");
	else
	{
		line = readline(prompt);
		free(prompt);
	}
	if (!line)
		ft_minishell_input(minishell);
	ft_add_history(line);
	lexer = ft_lexer(line, &(minishell->parsing_status));
	free(line);
	if (minishell->parsing_status != STATUS_OK)
		minishell->status = minishell->parsing_status;
	if (!lexer || (minishell->parsing_status != STATUS_OK))
		ft_minishell_input(minishell);
	ast = ft_ast(lexer, &(minishell->parsing_status));
	ft_clear_lexer(lexer, 0);
	if (!ast || (minishell->parsing_status != STATUS_OK))
	{
		minishell->status = minishell->parsing_status;
		ft_minishell_input(minishell);
	}
	// print_ast(ast, 0);
	ft_exec_line(ast, minishell);
}
