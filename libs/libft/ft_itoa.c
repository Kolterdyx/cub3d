/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	c;

	if (!n)
		return (1);
	c = 0;
	if (n < 0)
	{
		n *= -1;
		c++;
	}
	while (n)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	num;
	int		i;

	num = n;
	num = (num * (num >= 0)) + (num * -(num < 0));
	size = count_digits(n);
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < size)
	{
		str[(size - i - 1)] = (num % 10) + 48;
		num /= 10;
		i++;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
