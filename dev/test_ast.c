#include "dev.h"

int	profondeur_ast(t_ast * ast)
{
	int	left;
	int	right;

	if (ast)
	{
		left = profondeur_ast(ast->left);
		right = profondeur_ast(ast->right);
		if (left < right)
			return (right + 1);
		else
			return (left + 1);
	}
	else
		return (0);
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

int	main(int argc, char **argv)
{
	int	i;
	t_lexer	*lexer;
	t_lexer	*next;
	t_ast	*ast;

	i = 1;
	lexer = NULL;
	while (2 *i < argc)
	{
		if (!lexer)
		{
			lexer = ft_lexerof(atoi(argv[2 * i - 1]), argv[2 * i]);
			next = lexer;
		}
		else
		{
			next->next = ft_lexerof(atoi(argv[2 * i - 1]), argv[2 * i]);
			next = next->next;
		}
		i ++;
	}
	printf_lexer(lexer);
	ast = ft_ast(lexer);
	while (lexer)
	{
		next = lexer->next;
		free(lexer);
		lexer = next;
	}
	print_ast(ast, 0);
	ft_clear_ast(ast);
}
