/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*substr;

	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	size = ft_min(len, ft_strlen(s));
	substr = ft_calloc(size + 1, sizeof(char));
	if (!substr)
		return (ft_calloc(1, sizeof(char)));
	i = 0;
	while (i < size)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}
