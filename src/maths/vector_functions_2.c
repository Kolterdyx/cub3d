/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:33:10 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/09 04:33:10 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector_rotate(t_vector a, double angle)
{
	return ((t_vector){a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle)
		+ a.y * cos(angle)});
}

t_vector	vector_from_angle(double angle)
{
	return ((t_vector){cos(angle), sin(angle)});
}

double	vector_angle(t_vector a)
{
	return (atan2(a.y, a.x));
}

double	vector_length(t_vector a)
{
	return (sqrt(dot_product(a, a)));
}

double	vector_distance(t_vector a, t_vector b)
{
	return (vector_length(vector_sub(a, b)));
}
