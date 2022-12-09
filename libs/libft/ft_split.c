/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *s, char c)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	if (!ft_strlen(s))
		return (0);
	i = 0;
	count = s[i] != c;
	while (s[i])
	{
		count += (s[i] == c && s[i + 1] != c && s[i + 1] != '\0');
		i++;
	}
	return (count);
}

void	*panik(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	w;
	size_t	i;
	size_t	len;
	size_t	j;

	w = 0;
	i = 0;
	split = ft_calloc(count_words((char *)s, c) + 1, sizeof(char *));
	while (w < count_words((char *)s, c) && split)
	{
		j = 0;
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		split[w] = ft_calloc(len + 1, sizeof(char));
		if (!split[w])
			return (panik(split));
		while (s[i] != c && s[i] != '\0')
			split[w][j++] = s[i++];
		split[w++][j] = '\0';
	}
	return (split);
}
