/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:57:23 by octoross          #+#    #+#             */
/*   Updated: 2024/09/26 17:19:14 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_nbr_digits(unsigned long nbr)
{
	size_t	nbr_digits;

	nbr_digits = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		nbr_digits ++;
	}
	return (nbr_digits);
}

long	ft_abs(long nbr, int *sign)
{
	if (nbr < 0)
	{
		nbr *= -1;
		*sign = 1;
	}
	else
		*sign = 0;
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*itoaed;
	int		sign;
	size_t	nbr_digits;
	int		i;

	nbr = ft_abs((long)n, &sign);
	nbr_digits = ft_nbr_digits(nbr);
	itoaed = (char *)malloc(sizeof(char) * (sign + nbr_digits + 1));
	if (!itoaed)
		return (0);
	itoaed[sign + nbr_digits] = '\0';
	i = (int)nbr_digits + sign;
	while (i > sign)
	{
		i --;
		itoaed[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign)
		itoaed[0] = '-';
	return (itoaed);
}

// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 	{
// 		int n = atoi(argv[1]);
// 		char *return_type = ft_itoa(n);
// 		printf("return : %s", return_type);
// 		free(return_type);
// 	}
// 	return (0);
// }