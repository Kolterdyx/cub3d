/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:51 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:43:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y);
}

t_vec	sub_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y});
}

t_vec	add_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y});
}

t_vec	vec_scl(t_vec a, double b)
{
	return ((t_vec){a.x * b, a.y * b});
}

t_vec	vec_unit(t_vec a)
{
	return (vec_scl(a, 1. / sqrt(vec_dot(a, a))));
}
