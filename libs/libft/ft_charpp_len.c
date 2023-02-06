/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:26:00 by apena-ba          #+#    #+#             */
/*   Updated: 2023/01/19 19:26:01 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charpp_len(char **charpp)
{
	int	i;

	i = 0;
	if (charpp == NULL)
		return (0);
	while (charpp[i] != NULL)
		i++;
	return (i);
}
