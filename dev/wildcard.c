/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:19:33 by octoross          #+#    #+#             */
/*   Updated: 2024/09/29 00:19:33 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

void	print_fit_type(char *regex, char *name, bool win, int n)
{
	int	len;

	len = 0;
	while (len++ < n)
		printf("\t");
	printf("%s\t%s", regex, name);
	len = strlen(name);
	while (len ++ < 30)
		printf(" ");
	if (win)
		printf("%s\n", "✅");
	else
		printf("%s\n", "❌");
}

void	print_fit_wildcard(char *name, bool win, int n)
{
	int	len;

	len = 0;
	while (len++ < n)
		printf("\t");
	printf("\t%s↪ %s%s", CYAN, name, END);
	len = strlen(name);
	while (len ++ < 28 - (win * 3))
		printf(" ");
	if (win)
		printf("%s\n", "🎉 👍 🎉");
	else
		printf("%s\n", "👎");
}
