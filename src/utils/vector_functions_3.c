/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:53 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:43:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_vector_empty(t_vec a)
{
	return (a.x == 0 && a.y == 0);
}

t_vec	*vector_alloc(double x, double y)
{
	t_vec	*new;

	new = ft_calloc(1, sizeof(t_vec));
	new->x = x;
	new->y = y;
	return (new);
}

t_vec	*vec_cpy(t_vec a)
{
	t_vec	*new;

	new = ft_calloc(1, sizeof(t_vec));
	new->x = a.x;
	new->y = a.y;
	return (new);
}
