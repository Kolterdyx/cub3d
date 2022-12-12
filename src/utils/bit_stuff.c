/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:01:37 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 19:50:54 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	revert_bits(uint32_t set, int count)
{
	uint32_t	reverted;
	int			i;

	i = 0;
	reverted = 0;
	while (i < count)
	{
		reverted |= (set & 1) << (count - i - 1);
		set >>= 1;
		i++;
	}
	return (reverted);
}
