/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	if (str)
	{
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}

static int	ft_putptr(unsigned long long ptr)
{
	char	*numstr;
	int		size;

	numstr = ft_itoa_base(ptr, 0, "0123456789abcdef");
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(numstr, 1);
	size = ft_strlen(numstr) + 2;
	free(numstr);
	return (size);
}

static int	ft_format(va_list ap, const char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 'i' || c == 'd')
		return (printf_putnbr(va_arg(ap, int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(ap, int), c));
	else if (c == 'u')
		return (ft_putunbr(va_arg(ap, unsigned int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(ap, unsigned long long)));
	else if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;
	int		n;

	count = 0;
	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			n = ft_format(ap, str[i + 1]);
			if (n < 0)
				return (n);
			count += n;
			i++;
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
