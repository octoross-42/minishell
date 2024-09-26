#include "builtins.h"

// int	compare_built(char *s)
// {
// 	if (!s)
// 		return (8);
// 	if (!(ft_strcmp(s, "echo")))
// 		return (1);
// 	else if (!(ft_strcmp(s, "cd")))
// 		return (2);
// 	else if (!(ft_strcmp(s, "pwd")))
// 		return (3);
// 	else if (!(ft_strcmp(s, "export")))
// 		return (4);
// 	else if (!(ft_strcmp(s, "unset")))
// 		return (5);
// 	else if (!(ft_strcmp(s, "env")))
// 		return (6);
// 	else if (!(ft_strcmp(s, "exit")))
// 		return (7);
// 	else
// 		return (0);
// }

int	change_dir(char **arg)
{
	if (!arg[1])
		return (write(STDERR_FILENO, "Error: cd: specify a path\n", 26), 1);
	if (chdir(arg[1]) == -1)
	{
		return (write(STDERR_FILENO, "Error: cd: \
		failed to access path\n", 33), 1);
	}
	else
	{
		printf("Changed directory to %s\n", arg[1]); // a remove
		return (0);
	}
}

int	print_env(t_env *ep)
{
	t_env	*cur;

	cur = ep;
	while (cur)
	{
		write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
		cur = cur->next;
	}
	return (0);
}

void	modify_ptrs(int i, t_env *ep, t_env *cur, t_env *prev)
{
	if (!i)
		*ep = &cur->next;
	else
		prev->next = cur->next;
	free(cur->name);
	free(cur->value);
	free(cur);
}

int	unset_var(char **arg, t_env *ep)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	if (!arg[1])
		return (0);
	cur = ep;
	i = 0;
	while (cur)
	{
		if (ft_strncmp(arg[1], cur->value, ft_strlen(arg[1])))
		{
			prev = cur;
			cur = cur->next;
		}
		else
		{
			modifiy_ptrs(i, ep, cur, prev);
			return (0);
		}
	}
	return (0);
}

char	*get_env_name(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(s[i] && s[i] != '=')
		i ++;
	if(!i)
		return(NULL);//message d'erreur!!!!!!!(pas de name à export)
	ret = malloc((sizeof(char) * i) + 2);
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = s[j];
		j ++;
	}
	ret[j] = '=';
	ret[j + 1] = '\0';
	return (ret);
}

char	*get_env_value(char *s)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = ft_strlen(s);
	k = 0;
	while (s[i] && s[i] != '=')
		i ++;
	i ++;
	if (s[i] == '"' || s[i] == '\'')
	{
		i ++;
		j --;
	}
	ret = malloc((sizeof(char) * (j - i)) + 1);
	if (!ret)
		return (NULL);
	while (i < j)
		ret[k ++] = s[i ++];
	ret[k] = '\0';
	return (ret);
}

int	print_echo(char **arg)
{
	if (!arg[1])
		return (write(STDOUT_FILENO, "\n", 1), 0);
	if (!ft_strcmp(arg[1], "-n") && !arg[2])
		return (0);
	else if (!ft_strcmp(arg[1], "-n") && arg[2])
		arg += 2;
	else
		arg ++;
	while (*arg)
	{
		write(STDOUT_FILENO, *arg, ft_strlen(*arg));
		if (*arg)
			write(STDOUT_FILENO, " ", 1);
		arg ++;
	}
	if (ft_strcmp(arg[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

void	free_them(char *s, char *st)
{
	free(s);
	free(st);
}

int	add__env_var(char **arg, t_env *env)
{
	char	*name;
	char	*val;
	int		status;

	if (!arg[1])
	{
		write(STDERR_FILENO, "Export error: specify a name and a value\n", 41);
		return (1);
	}
	name = get_env_name(arg[1]);
	val = get_env_value(arg[1]);
	if (!name || !val)
		return (write(STDERR_FILENO, "Malloc error\n", 14), 137);
	status = ft_add_env(&env, name, val);
	if (status != STATUS_OK)
	{
		free_them(name, val);
		return (status);
	}
	return (0);
}

int	go_to_getcwd(void)
{
	char	*buff;
	int		i;

	i = 1;
	buff = malloc(sizeof(char) * BSIZE * i);
	if (!buff)
		return (printf("Malloc error\n"), 137);
	while (getcwd(buff, BSIZE * i) == NULL)
	{
		if (errno == ERANGE)
		{
			i ++;
			buff = malloc(sizeof(char) * BSIZE * i);
			if (!buff)
				return (printf("Malloc error\n"), 137);
		}
		else
		{
			printf("Can't access directory\n");
			return (1);
		}
	}
	write(STDOUT_FILENO, buff, ft_strlen(buff));
	return (0);
}

int	print_wd(t_env *ep)
{
	int		i;
	t_env	*cur

	i = 0;
	cur = ep;
	while (cur)
	{
		if (ft_strncmp(cur->name, "PWD=", 4))
			cur = cur->next;
		else
		{
			write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
			return i;
		}
	}
	i = go_to_getcwd();
	return (i);
}

// int	main(int ac, char **av, char **ep)
// {
	// unset_var(av, ep);
	// print_env(ep);
	// print_wd(ep);
	// change_dir(av);
// }