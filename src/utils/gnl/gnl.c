/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:33:02 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 18:00:30 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

#include <stdio.h>

t_gnl	*ft_read_line(int fd)
{
	t_gnl	*line;
	int		i;

	line = (t_gnl *)malloc(sizeof(t_gnl));
	if (!line)
		return (NULL);
	line->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(line->content))
		return (free(line), NULL);
	line->start = 0;
	line->len = read(fd, line->content, BUFFER_SIZE);
	if (line->len <= 0)
		return (free(line->content), free(line), NULL);
	i = line->len;
	while (i <= BUFFER_SIZE)
		line->content[i ++] = '\0';
	i = 0;
	while (i < line->len && line->content[i] != '\n')
		i ++;
	line->eof = (line->len < BUFFER_SIZE);
	line->eol = -1 + (i + 1) * (i < line->len);
	line->next = NULL;
	line->size = (line->eol + 1) * (line->eol >= 0)
		+ line->len * (line->eol < 0);
	return (line);
}

int	ft_read(t_gnl **leftovers, int fd)
{
	t_gnl	*next;

	if (!(*leftovers))
		*leftovers = ft_read_line(fd);
	if (!(*leftovers))
		return (1);
	next = *leftovers;
	while (next->eol < 0 && !(next->eof))
	{
		next->next = ft_read_line(fd);
		if (!(next->next))
			next->eof = 1;
		else
		{
			next = next->next;
			(*leftovers)->size += next->size;
		}
	}
	return (0);
}

char	*ft_lst_to_str(t_gnl **l)
{
	char	*return_line;
	int		i;
	int		j;
	int		eol_reached;

	return_line = (char *)malloc(sizeof(char) * ((*l)->size + 1));
	if (!return_line)
		return (NULL);
	return_line[(*l)->size] = '\0';
	i = 0;
	eol_reached = 0;
	while (!eol_reached)
	{
		j = (*l)->start;
		while (j <= (*l)->eol || (((*l)->eol < 0) && j < (*l)->len))
			return_line[i ++] = (*l)->content[j ++];
		(*l)->start = j;
		while (j < (*l)->len && (*l)->content[j] != '\n')
			j ++;
		eol_reached = ((*l)->eol >= 0 || (*l)->eof);
		(*l)->size = (j + (j < (*l)->len) - (*l)->start) * ((*l)->eol >= 0);
		(*l)->eol = -1 + (j + 1) * (j < (*l)->len);
		ft_clean_and_next_lst(l);
	}
	return (return_line);
}

char	*gnl(int fd)
{
	static t_gnl	*leftovers = NULL;
	char			*return_line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (ft_clear_leftovers(&leftovers), NULL);
	if (ft_read(&leftovers, fd))
		return (ft_clear_leftovers(&leftovers), NULL);
	return_line = ft_lst_to_str(&leftovers);
	if (!return_line)
		return (ft_clear_leftovers(&leftovers), NULL);
	return (return_line);
}
