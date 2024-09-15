#include "cringishell.h"

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
int	allow_all(char *s, int val)
{
	int	i;

	i = 0;
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
				s[i + 1] == '&')) && (s[i + 2] != '&' && s[i + 2] != '|'))
				return (2);
			else if (((s[i] == '|' && s[i + 1] == '|') || (s[i] == '&' &&
				s[i + 1] == '&')) && (s[i + 2] == '&' || s[i + 2] == '|'))
				return (0);
		}
	}
	if (s[i] == '>' || s[i] == '<' || s[i] == '|' )
		return (1);
	while (s[i] && s[i] != 32 && s[i] != '>' && s[i] != '|')
	{
		if (s[i] == 34 || s[i] == 39)
			i = i + allow_all(&s[i], s[i]);
		else
			i ++;
	}
	return (i);
}

//ne fonctionnera PAS pour echo (e.g. echo "<>cat|><")
char    *get_data(char *s)
{
	int     i;
	int     j;
	char    *new;

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

t_lexer *lex_new(void *cont, t_parse p)
{
	t_lexer *new;
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->data = cont;
	new->cmd_pos = p.pos;
	new->pos = p.cmd;
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

void    queue_lex(t_lexer **lex, t_lexer *add)
{
	if (!*lex)
		*lex = add;
	else
		lex_last(*lex)->next = add;
	add->next = NULL;
}

t_parse init_pars(t_parse p)
{
	p.cmd = 0;
	p.pos = 0;
	return (p);
}

t_parse incr_pars(int a, t_parse p)
{
	if (a == '&' || a == '|' || a == '>')
	{
		p.cmd ++;
		p.pos = 0;
	}
	else
		p.pos ++;
	return (p);
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
	t_parse p;
	t_lexer	*l;
	int     i;

	i = 0;
	p = init_pars(p);
	while (s[i] == ' ')
		i ++;
	while (s[i])
	{
		l = lex_new(get_data(&s[i]), p);
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
		p = incr_pars(s[i], p);
	}
	return (lex);
}

t_lexer	**lex_assign(t_lexer **lex)
{
	t_lexer	*cur;

	cur = *lex;
	while (cur)
	{
		if (!(ft_strcmp(cur->data, "<")))
			cur->token = "INPUT";
		else if (!(ft_strcmp(cur->data, ">")))
			cur->token = "OUTPUT";
		else if (!(ft_strcmp(cur->data, "|")))
			cur->token = "PIPE";
		else if (!(ft_strcmp(cur->data, "&&")))
			cur->token = "AND";
		else if (!(ft_strcmp(cur->data, "||")))
			cur->token = "OR";
		else if (!(ft_strcmp(cur->data, ">>")))//vérifie ca stp je suis pas sûr
			cur->token = "APPEND";
		else if (!(ft_strcmp(cur->data, "<<")))
			cur->token = "HERE_DOC";
		else
			cur->token = "DATA";
		cur = cur->next;
	}
	return (lex);
}
t_lexer	**change_data(t_lexer **lex)
{
	t_lexer	*cur;

	cur = *lex;
	while(cur)
	{
		if (strcmp(cur->token, "DATA"))
		{
			free(cur->data);
			cur->data = NULL;
		}
		cur = cur->next;
	}
	return (lex);
}

void	print_all(t_lexer *test)
{
	printf("content = %s\n", (char *)test->data);
	printf("token =  %s\n", test->token);
	printf("numero de la commande = %d\n", test->pos);
	printf("emplacement dans la commande = %d\n", test->cmd_pos);
	printf("fin de la node\n\n");
}

int main(void)
{
	t_lexer **lex;

	lex = malloc(8);
	if (!lex)
		exit(EXIT_FAILURE);
	*lex = NULL;
	lex = lex_values("test'ceci' av||ec des et des> et <", lex);
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