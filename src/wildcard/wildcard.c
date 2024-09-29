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

DIR	*ft_init_wildcard(char *regex, int *end_regex, char **path)
{
    DIR				*dir;

	if (!regex)
		return (NULL);
	if (!(*path) && regex && (regex[0] == '/'))
	{
		(*path) = strdup("/");
		if (!(*path))
			return (ft_fail(ERR_MALLOC, "no wildcard"), NULL);
		regex ++;
	}
	if (!(*path))
		dir = opendir(".");
	else
		dir = opendir((*path));
	if (!dir)
		return (perror("opendir"), NULL);
	*end_regex = 0;
	while (regex[*end_regex] && (regex[*end_regex] != '/'))
		(*end_regex)++;
	return (dir);
}

t_wildcard	*ft_wildcard(char *regex, char *path)
{
	t_wildcard		*wildcard;
	t_wildcard		*new;
    DIR				*dir;
    struct dirent	*entry;
	int				end_regex;
	int				is_dir;
	char			*next_path;

	dir = ft_init_wildcard(regex, &end_regex, &path);
	if (!dir)
		return (NULL);
	wildcard = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
		{
			entry = readdir(dir);
			continue ;
		}
		is_dir = ft_entry_is_dir(entry);
		if (is_dir < 0)
			return (ft_clear_wildcard(wildcard), NULL);
		if (!regex[end_regex] || ((regex[end_regex] == '/') && is_dir))
		{
			if (ft_fit_wildcard(entry->d_name, regex, end_regex))
			{
				if ((regex[end_regex] == '/') && regex[end_regex + 1])
				{
					if (path)
						next_path = ft_build_dir_path(path, entry->d_name);
					else
						next_path = ft_build_dir_path("", entry->d_name);
					if (!next_path)
						return (ft_fail(ERR_MALLOC, "no wildcard"), ft_clear_wildcard(wildcard), NULL);
					ft_add_wildcard(&wildcard, ft_wildcard(regex + end_regex + 1, next_path));
				}
				else
				{
					new = ft_new_wildcard(entry->d_name, path, regex[end_regex] == '/');
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

int	main(int argc, char **argv)
{
	t_wildcard	*wildcard;
	t_wildcard	*next;

	if (argc < 2)
		return (1);
	wildcard = ft_wildcard(argv[1], NULL);
	next = wildcard;
	while (next)
	{
		printf("%s\n", next->file);
		next = next->next;
	}
	ft_clear_wildcard(wildcard);
	return (0);
}
