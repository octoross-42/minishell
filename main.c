#include "cringishell.h"

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
	new->cmd_pos = p.cmd;
	new->pos = p.pos;
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

t_lexer **lex_values(char *s, t_lexer **lex)
{
	t_parse p;
	int     i;

	i = 0;
	p = init_pars(p);
	while (s[i] == ' ')
		i ++;
	while (s[i])
	{
		queue_lex(lex, lex_new(get_data(&s[i]), p));//add une fn qui free tout si fail
		i = i + move_i(&s[i], 0);
		if (s[i] == 0)
			break ;
		while (s[i] == ' ')
			i ++;
		p = incr_pars(s[i], p);
	}
	return (lex);
}

// void	print_all(t_lexer *test)
// {
// 	printf("content = $$%s$$\n", (char *)test->data);
// 	printf("numero de la commande = %d\n", test->pos);
// 	printf("emplacement dans la commande = %d\n", test->cmd_pos);
// 	printf("fin de la node\n\n");
// }

// int main(void)
// {
// 	t_lexer **lex;

// 	lex = malloc(8);
// 	if (!lex)
// 		exit (EXIT_FAILURE);
// 	*lex = NULL;
// 	lex = lex_values("test av|ec des et des> et <", lex);
// 	t_lexer	*test = *lex;
// 	while (test)
// 	{
// 		print_all(test);
// 		test = test->next;
// 	}
// 	return (0);
// }