/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:41:51 by octoross          #+#    #+#             */
/*   Updated: 2024/10/04 18:17:52 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_banner(void)
{
	printf("\n\t\t    %s         ▄▄           ▄▀█\n", WHITE);
	printf("\t\t    ▄▀▀▀▄  ▄▀ █           ▀▄▀ ▄▄  \n");
	printf("\t\t    ▀▄   █▄▀▄▄▀       ▄▀▀▄  ▄▀ █ \n");
	printf("\t\t      ▀▀▄▄█▀▄         ▀▄▄ █ █ █  \n");
	printf("\t\t          █  ▀▄▄▄        ▀█ █▀    \n");
	printf("\t\t          █      ▀▀▀▀▀▀▄▄▄▄▄▄▄▄▄▄▄▄ \n");
	printf("\t\t          █                        ▀▄\n");
	printf("\t\t           █                        █\n");
	printf("\t\t            █              %s▄▄%s       █\n", WHITE, WHITE);
	printf("\t\t             ▀▀▄▄          %s▀%s▀%s      ▄▀\n",
		BLUE, WHITE, WHITE);
	printf("\t\t             ▄▀  ▄▀▄▄▄          ▄▄▄▀\n");
	printf("\t\t              ▀▀▀     ▀▀▀▀▀▀▀▀▀▀\n\n");
	printf("\t\t█▀▄  ▄▀█ █ █▀▄   █ █ ▄▀▀▀▀▀ █    █ ▄▀▀▀▀ █    █\n");
	printf("\t\t█  ▀▀  █ █ █  ▀▄ █ █  ▀▀▀▀▄ █ ▀▀▀█ █▀▀▀  █    █\n");
	printf("\t\t▀      ▀ ▀ ▀    ▀▀ ▀ ▀▀▀▀▀▀ ▀    ▀  ▀▀▀▀ ▀▀▀▀ ▀▀▀▀\n");
	printf("\t\t──────────────────────────────────────────────────\n");
	printf("\t\t%sBy: jermarti                          %sBy: octoross%s\n\n",
		BLUE, CYAN, END);
}
