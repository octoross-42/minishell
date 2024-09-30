/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 06:06:15 by octoross          #+#    #+#             */
/*   Updated: 2024/09/27 06:06:15 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	ft_entry_is_dir(struct dirent *entry)
{
    struct stat file_stat;

	if (entry->d_type == DT_UNKNOWN)
	{
		if (lstat(entry->d_name, &file_stat) == 0)
			return (S_ISDIR(file_stat.st_mode));
		else
			return (perror("lstat error"), -1);
	}
	else
		return (entry->d_type == DT_DIR);
}

DIR	*ft_init_wildcard(t_str *r, char *regex, char **path)
{
    DIR				*dir;

	if (!regex)
		return (NULL);
	if (!(*path) && (regex[0] == '/'))
	{
		*path = ft_strdup("/");
		if (!(*path))
			return (ft_fail(ERR_MALLOC, "no wildcard"), NULL);
		regex ++;
	}
	if (!(*path))
		dir = opendir(".");
	else
		dir = opendir(*path);
	if (!dir)
		return (perror("opendir"), NULL);
	r->end = 0;
	while (regex[r->end] && (regex[r->end] != '/'))
		(r->end)++;
	r->s = regex;
	return (dir);
}

t_wildcard	*ft_wildcard(char *regex, char *path)
{
	t_wildcard		*wildcard;
	t_wildcard		*new;
    DIR				*dir;
    struct dirent	*entry;
	int				is_dir;
	char			*next_path;
	t_str			r;

	dir = ft_init_wildcard(&r, regex, &path);
	if (!dir)
		return (NULL);
	wildcard = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
		{
			// TODO pas les ignorer pour remonter le path
			entry = readdir(dir);
			continue ;
		}
		is_dir = ft_entry_is_dir(entry);
		if (is_dir < 0)
			return (ft_clear_wildcard(wildcard), NULL);
		if (!r.s[r.end] || ((r.s[r.end] == '/') && is_dir))
		{
			if (ft_fit_wildcard(entry->d_name, r.s, r.end))
			{
				if ((r.s[r.end] == '/') && r.s[r.end + 1])
				{
					if (path)
						next_path = ft_build_dir_path(path, entry->d_name);
					else
						next_path = ft_build_dir_path("", entry->d_name);
					if (!next_path)
						return (ft_fail(ERR_MALLOC, "no wildcard"), ft_clear_wildcard(wildcard), NULL);
					ft_add_wildcard(&wildcard, ft_wildcard(r.s + r.end + 1, next_path));
				}
				else
				{
					new = ft_new_wildcard(entry->d_name, path, r.s[r.end] == '/');
					if (!new)
						return (ft_clear_wildcard(wildcard), NULL);
					ft_add_wildcard(&wildcard, new);
				}
			}
		}
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (perror("closedir"), NULL);
	if (path)
		free(path);
	return (wildcard);
}

char	**ft_argv_wildcard(t_wildcard *wildcard)
{
	char	**argv;
	int		len;
	t_wildcard	*next;

	len = ft_len_wildcard(wildcard);
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (ft_fail(ERR_MALLOC, "no wildcard"), NULL);
	argv[len] = NULL;
	len = 0;
	while (wildcard)
	{
		argv[len ++] = wildcard->file;
		next = wildcard->next;
		free(wildcard);
		wildcard = next;
	}
	return (argv);
}

// int	main(int argc, char **argv)
// {
// 	t_wildcard	*wildcard;
// 	int			i;
// 	char		**argv_wildcard;

// 	if (argc < 2)
// 		return (1);
// 	wildcard = ft_wildcard(argv[1], NULL);
// 	argv_wildcard = ft_argv_wildcard(wildcard);
// 	if (!argv_wildcard)
// 		return (1);
// 	i = 0;
// 	while (argv_wildcard[i])
// 	{
// 		printf("%s\n", argv_wildcard[i]);
// 		free(argv_wildcard[i ++]);
// 	}
// 	free(argv_wildcard);
// 	return (0);
// }
