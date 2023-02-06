/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:05:53 by apena-ba          #+#    #+#             */
/*   Updated: 2023/01/18 20:06:05 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void	*ft_charpp_free(char **to_free)
{
	int	pos;

	pos = 0;
	if (to_free == NULL)
		return (NULL);
	while (to_free[pos] != NULL)
	{
		free(to_free[pos]);
		pos++;
	}
	free(to_free);
	return (NULL);
}
