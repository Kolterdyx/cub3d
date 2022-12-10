/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:51 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/09 04:32:51 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y});
}

t_vector	vector_add(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y});
}

t_vector	vector_scale(t_vector a, double b)
{
	return ((t_vector){a.x * b, a.y * b});
}

t_vector	vector_normalize(t_vector a)
{
	return (vector_scale(a, 1. / sqrt(vector_dot(a, a))));
}
