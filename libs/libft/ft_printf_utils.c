/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_count_digits(unsigned long long n, int neg, int base)
{
	int	i;

	i = neg + 1;
	n *= ((-1 * neg) + !neg);
	while (n >= (unsigned long long)base)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	ft_putunbr(unsigned int num)
{
	char	*numstr;
	int		size;

	numstr = ft_itoa_base(num, 0, "0123456789");
	ft_putstr_fd(numstr, 1);
	size = ft_strlen(numstr);
	free(numstr);
	return (size);
}

int	printf_putnbr(int num)
{
	char	*numstr;
	int		size;

	numstr = ft_itoa_base(num, num < 0, "0123456789");
	ft_putstr_fd(numstr, 1);
	size = ft_strlen(numstr);
	free(numstr);
	return (size);
}

char	*ft_itoa_base(unsigned long long n, int neg, char *base)
{
	char	*buffer;
	int		b_size;
	int		n_size;
	int		i;

	i = 0;
	b_size = ft_strlen(base);
	n_size = printf_count_digits(n, neg, b_size);
	buffer = ft_calloc(n_size + 2, sizeof(char));
	i = n_size;
	if (neg)
	{
		buffer[0] = '-';
		n *= -1;
	}
	while (i > neg)
	{
		buffer[i - 1] = base[n % b_size];
		n = n / b_size;
		i--;
	}
	return (buffer);
}
