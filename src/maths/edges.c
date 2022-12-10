/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:59 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 23:24:54 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	edges_intersect(t_edge a, t_edge b, t_vector *intersection)
{
	double	denominator;
	double	t;
	double	u;

	denominator = (b.end.y - b.start.y) * (a.end.x - a.start.x) - (b.end.x
			- b.start.x) * (a.end.y - a.start.y);
	if (denominator == 0)
		return (0);
	t = ((b.end.x - b.start.x) * (a.start.y - b.start.y) - (b.end.y - b.start.y)
			* (a.start.x - b.start.x)) / denominator;
	u = ((a.end.x - a.start.x) * (a.start.y - b.start.y) - (a.end.y - a.start.y)
			* (a.start.x - b.start.x)) / denominator;
	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		*intersection = (t_vector){a.start.x + t * (a.end.x - a.start.x),
			a.start.y + t * (a.end.y - a.start.y)};
		return (1);
	}
	return (0);
}

int	edge_intersects_circle(t_edge a, t_vector center, double radius,
							t_vector *closest_point)
{
	t_vector	abc[2];
	double		ab2;
	double		ac2;
	double		t;
	t_vector	closest;

	abc[0] = vector_sub(a.end, a.start);
	ab2 = vector_dot(abc[0], abc[0]);
	abc[1] = vector_sub(center, a.start);
	ac2 = vector_dot(abc[1], abc[1]);
	t = vector_dot(abc[1], abc[0]) / ab2;
	if (t < 0)
		closest = a.start;
	else if (t > 1)
		closest = a.end;
	else
		closest = vector_add(a.start, vector_scale(abc[0], t));
	*closest_point = closest;
	return (vector_distance(center, closest) < radius);
}

t_vector	find_intersection(t_edge a, t_edge b)
{
	t_vector	intersection;

	if (edges_intersect(a, b, &intersection))
		return (intersection);
	return ((t_vector){0, 0});
}

t_edge	*edge_alloc(t_vector start, t_vector end, int dir)
{
	t_edge	*new;

	new = ft_calloc(1, sizeof(t_edge));
	new->start = start;
	new->end = end;
	new->dir = dir;
	return (new);
}
