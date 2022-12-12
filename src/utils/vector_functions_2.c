/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:33:10 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:43:07 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	vec_rotate(t_vec a, double angle)
{
	return ((t_vec){a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle)
		+ a.y * cos(angle)});
}

t_vec	vec_from_rad(double angle)
{
	return ((t_vec){cos(angle), sin(angle)});
}

double	vec_rad(t_vec a)
{
	return (atan2(a.y, a.x));
}

double	vec_len(t_vec a)
{
	return (sqrt(vec_dot(a, a)));
}

double	vec_dist(t_vec a, t_vec b)
{
	return (vec_len(sub_vec(a, b)));
}
