/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_nfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:56:21 by apena-ba          #+#    #+#             */
/*   Updated: 2023/01/30 20:58:01 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void	*ft_charpp_nfree(char **to_free, size_t n)
{
	size_t	pos;

	pos = 0;
	if (to_free == NULL)
		return (NULL);
	while (pos < n)
	{
		free(to_free[pos]);
		pos++;
	}
	free(to_free);
	return (NULL);
}
