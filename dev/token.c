/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:45:24 by octoross          #+#    #+#             */
/*   Updated: 2024/09/13 23:45:44 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_token_of(int token)
{
	if (token == PIPE)
		return ("PIPE");
	if (token == OR)
		return ("OR");
	if (token == AND)
		return ("AND");
	if (token == INPUT)
		return ("INPUT");
	if (token == OUTPUT)
		return ("OUTPUT");
	if (token == HERE_DOC)
		return ("HERE_DOC");
	if (token == APPEND)
		return ("APPEND");
	if (token == CMD)
		return ("CMD");
}
