/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:31:32 by octoross          #+#    #+#             */
/*   Updated: 2024/09/16 21:23:32 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy_prompt(char *prompt, char wd[PATH_SIZE], bool err)
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
	char	wd[PATH_SIZE];
	char	*prompt;
	int		len;
	bool	err;

	len = ft_strlen("🐳 minishell:") + ft_strlen(CYAN) + ft_strlen(END) + 2;
	err = false;
	if (!getcwd(wd, PATH_SIZE))
	{
		len += ft_strlen(ERR_GETCWD);
		err = true;
	}
	else
		len += ft_strlen(wd) + ft_strlen(BLUE);
	prompt = (char *)malloc(sizeof(char) * (len + 1));
	if (!prompt)
		return (ft_fail(ERR_MALLOC), NULL);
	prompt[len] = '\0';
	ft_strcpy_prompt(prompt, wd, err);
	return (prompt);
}

t_lexer	*ft_lexerof(int token, void *data)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->token = token;
	if (ft_is_fork(lexer->token))
		lexer->data = NULL;
	else
		lexer->data = data;
	lexer->next = NULL;
	return (lexer);
}

#include "dev.h"

t_lexer	*ft_tmp_lexer(char **argv)
{
	int		i;
	t_lexer	*lexer;
	t_lexer	*next;
	char	*data;

	i = 0;
	lexer = NULL;
	while (argv[i])
	{
		if (ft_is_fork(token_of_str(argv[i])))
			data = NULL;
		else
			data = argv[i + 1];
		if (!lexer)
		{
			lexer = ft_lexerof(token_of_str(argv[i]), data);
			next = lexer;
		}
		else
		{
			next->next = ft_lexerof(token_of_str(argv[i]), data);
			next = next->next;
		}
		if (data)
			i ++;
		i ++;
	}
	return (lexer);
}

void	ft_input_minishell(t_minishell *minishell)
{
	char	*prompt;
	char	*line;
	char	**splited;
	t_lexer	*lexer;
	t_lexer	*next;
	t_ast	*ast;

	prompt = ft_get_prompt();
	if (!prompt)
		exit (EXIT_FAILURE);
	line = readline(prompt);
	free(prompt);
	if (!line || ft_strlen(line) <= 0)
		exit(EXIT_SUCCESS);
	// TODO remplacer par parsing de Jerome
	splited = ft_split(line, ' ');
	free(line);
	lexer = ft_tmp_lexer(splited);
	ft_free_until((void **)splited, -1);
	// jusqu'ici
	// TODO rajouter un exit failure dans le parsing pour qu'ici on n'arrive que si ya succes (penser à free line dedans)
	if (!lexer)
		exit(EXIT_SUCCESS);
	ast = ft_ast(lexer);
	while (lexer)
	{
		next = lexer->next;
		free(lexer);
		lexer = next;
	}
	// TODO remplacer boucle pour free par fonction
	print_ast(ast, 0);
	minishell->ast = ast;
	ft_exec_ast(minishell);
}
