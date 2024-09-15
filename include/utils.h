/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:26:55 by octoross          #+#    #+#             */
/*   Updated: 2024/09/15 20:10:54 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_MALLOC "malloc failed\n"

int		ft_strlen(const char *str);
void	ft_fail(char *err);

#endif