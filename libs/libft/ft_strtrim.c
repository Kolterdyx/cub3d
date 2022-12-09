/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strhas(const char *str, char c)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_offset;
	size_t	end_offset;

	if (!s1 || !set)
		return (NULL);
	start_offset = 0;
	end_offset = ft_strlen(s1);
	while (strhas(set, s1[start_offset]))
		start_offset++;
	while (strhas(set, s1[end_offset - 1]))
		end_offset--;
	if (end_offset - start_offset == 0)
		return (ft_calloc(1, sizeof(char)));
	return (ft_substr(s1, start_offset, end_offset - start_offset));
}
