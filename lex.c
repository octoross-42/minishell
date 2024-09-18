#include "lexer.h"

//à comenter pour push final
void	print_all(t_lexer *test)
{
	printf("content = %s\n", (char *)test->data);
	printf("token =  %d\n", test->token);
	printf("fin de la node\n\n");
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (s1[i] - s2[i]);
	}
	if (!s1[i] && !s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

t_lexer	*lex_new(void *cont)
{
	t_lexer *new;
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->data = cont;
	new->next = NULL;
	return (new);
}

t_lexer	*lex_last(t_lexer *check)
{
	if (!check)
		return (NULL);
	while (check->next)
		check = check->next;
	return (check);
}

void	queue_lex(t_lexer **lex, t_lexer *add)
{
	if (!*lex)
		*lex = add;
	else
		lex_last(*lex)->next = add;
	add->next = NULL;
}

t_lexer	**lex_assign(t_lexer **lex)
{
	t_lexer	*cur;

	cur = *lex;
	while (cur)
	{
		if (!(ft_strcmp(cur->data, "<")))
			cur->token = INPUT;
		else if (!(ft_strcmp(cur->data, ">")))
			cur->token = OUTPUT;
		else if (!(ft_strcmp(cur->data, "|")))
			cur->token = PIPE;
		else if (!(ft_strcmp(cur->data, "&&")))
			cur->token = AND;
		else if (!(ft_strcmp(cur->data, "||")))
			cur->token = OR;
		else if (!(ft_strcmp(cur->data, ">>")))
			cur->token = APPEND;
		else if (!(ft_strcmp(cur->data, "<<")))
			cur->token = HERE_DOC;
		else
			cur->token = CMD;
		cur = cur->next;
	}
	return (lex);
}
int	allow_all(char *s, int val)
{
	int	i;

	i = 1;
	while(s[i] && s[i] != val)
		i ++;
	return (i + 1);
}

int move_i(char *s, int i)
{
	if (s[i] && s[i + 1])
	{
		if (s[i + 2])
		{
			if (((s[i] == '|' && s[i + 1] == '|') || (s[i] == '&' &&
				s[i + 1] == '&')) && (s[i + 2] != '&' && s[i + 2] != '|')
				|| (s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' 
				&& s[i + 1] == '>'))
				return (2);
			else if (((s[i] == '|' && s[i + 1] == '|') || (s[i] == '&' &&
				s[i + 1] == '&')) && (s[i + 2] == '&' || s[i + 2] == '|'))
				return (0);
		}
	}
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		return (1);
	while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '|' && s[i] != '<'
		&& s[i] != '&')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = i + allow_all(&s[i], s[i]);
		else
			i ++;
	}
	return (i);
}

char	*get_data(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = move_i(s, 0);
	if (!j)
		return (NULL);
	new = malloc(j + 1);
	if (!new)
		return (NULL);
	while (i < j)
	{
		new[i] = s[i];
		i ++;
	}
	new[i] = 0;
	return (new);
}

void	*error_lex(t_lexer **lex, int i)
{
	t_lexer	*cur;
	t_lexer	*next;

	cur = *lex;
	next = cur->next;
	while (cur)
	{
		free(cur->data);
		cur = cur->next;
	}
	cur = *lex;
	while (next)
	{
		free(cur);
		cur = next;
		next = next->next;
	}
	free(cur);
	free(lex);
	if (i == 1)
		write(2, "Malloc error when processing data\n", 34);
	if (i == 2)
		write(2, "Parsing error, bad input detected\n", 34);
	return (NULL);
}

t_lexer **lex_values(char *s, t_lexer **lex)
{
	t_lexer	*l;
	int     i;

	i = 0;
	while (s[i] == ' ')
		i ++;
	while (s[i])
	{
		l = lex_new(get_data(&s[i]));
		if (!l)
			return (error_lex(lex, 1));
		queue_lex(lex, l);
		i = i + move_i(&s[i], 0);
		if (!lex_last(*lex)->data)
			return (error_lex(lex, 2));
		if (s[i] == 0)
			break ;
		while (s[i] == ' ')
			i ++;
	}
	return (lex);
}

t_lexer	**change_data(t_lexer **lex)
{
	t_lexer	*cur;

	cur = *lex;
	while(cur)
	{
		if (cur->token != CMD)
		{
			free(cur->data);
			cur->data = NULL;
		}
		cur = cur->next;
	}
	return (lex);
}

int main(int argc, char **argv)
{
	t_lexer **lex;

	lex = malloc(8);
	if (!lex)
		exit(EXIT_FAILURE);
	*lex = NULL;
	lex = lex_values("test'ceci' av||ec d&es et des>> et < ec&&ho \"<>cat|>&<\"eza", lex);
	if (!lex)
		exit(EXIT_FAILURE);
	lex = lex_assign(lex);
	lex = change_data(lex);
	t_lexer	*test = *lex;
	while (test)
	{
		print_all(test);
		test = test->next;
	}
	lex = error_lex(lex, 0);
	return (0);
}