/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:52:10 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 18:10:35 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H

# define DISPLAY_H

# define END "\033[0m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define BG_BLACK "\e[40m"
# define BG_RED "\e[41m"
# define BG_GREEN "\e[42m"
# define BG_YELLOW "\e[43m"
# define BG_BLUE "\e[44m"
# define BG_MAGENTA "\e[45m"
# define BG_CYAN "\e[46m"
# define BG_WHITE "\e[47m"

# define BSIZE 4096

# define ERR_GETCWD "(no pwd :()"

void	ft_print_banner(void);

#endif