/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:53 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 14:10:16 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_vector_empty(t_vector a)
{
	return (a.x == 0 && a.y == 0);
}

t_vector	*vector_alloc(double x, double y)
{
	t_vector	*new;

	new = ft_calloc(1, sizeof(t_vector));
	new->x = x;
	new->y = y;
	return (new);
}

t_vector	*vector_copy(t_vector a)
{
	t_vector	*new;

	new = ft_calloc(1, sizeof(t_vector));
	new->x = a.x;
	new->y = a.y;
	return (new);
}
