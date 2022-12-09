/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:33:25 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/09 01:43:56 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arradd_back(char **arr, char *value)
{
	char **new;
	int i;

	i = 0;
	while (arr && arr[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (arr && arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = value;
	free(arr);
	return (new);
}