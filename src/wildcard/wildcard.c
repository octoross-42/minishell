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
	struct stat	file_stat;

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

bool	ft_explore_path(t_wildcard_data data, t_wildcard **wildcard)
{
	char			*next_path;

	next_path = ft_build_path(data.path, data.name, data.slash);
	if (!next_path)
	{
		ft_fail(ERR_MALLOC, "no wildcard");
		ft_clear_wildcard(*wildcard);
		return (false);
	}
	ft_add_wildcard(wildcard, \
		ft_wildcard(data.regex + data.end_slash, next_path));
	return (true);
}

bool	ft_check_entry(t_wildcard_data data, t_wildcard **wildcard)
{
	t_wildcard		*new;

	if ((!ft_strcmp(data.name, ".") || !ft_strcmp(data.name, ".."))
		&& (ft_strncmp(data.regex, ".", data.end)
			&& ft_strncmp(data.regex, "..", data.end)))
		return (true);
	if ((data.regex[data.end] == '/') && !(data.entry_is_dir))
		return (true);
	if (!ft_fit_wildcard(data))
		return (true);
	data.end_slash = data.end;
	while (data.regex[data.end_slash] == '/')
		data.end_slash ++;
	data.slash = data.end_slash - data.end;
	if (!(data.regex[data.end_slash]))
	{
		new = ft_new_wildcard(data);
		if (!new)
			return (ft_clear_wildcard(*wildcard), false);
		ft_add_wildcard(wildcard, new);
		return (true);
	}
	else
		ft_explore_path(data, wildcard);
	return (true);
}

DIR	*ft_init_wildcard(t_wildcard_data *data, char *regex, char **path)
{
	DIR	*dir;

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
	data->path = *path;
	data->end = 0;
	while (regex[data->end] && (regex[data->end] != '/'))
		data->end ++;
	data->regex = regex;
	return (dir);
}

t_wildcard	*ft_wildcard(char *regex, char *path)
{
	t_wildcard		*wildcard;
	t_wildcard_data	data;
	DIR				*dir;
	struct dirent	*entry;

	dir = ft_init_wildcard(&data, regex, &path);
	if (!dir)
		return (NULL);
	wildcard = NULL;
	entry = readdir(dir);
	while (entry)
	{
		data.entry_is_dir = ft_entry_is_dir(entry);
		if (data.entry_is_dir < 0)
			return (ft_clear_wildcard(wildcard), NULL);
		data.name = entry->d_name;
		if (!ft_check_entry(data, &wildcard))
			return (NULL);
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (perror("closedir"), NULL);
	if (data.path)
		free(data.path);
	return (wildcard);
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
