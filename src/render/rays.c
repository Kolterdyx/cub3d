/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:59:40 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 01:29:40 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ray(t_data *data, int dir, t_vector inter)
{
	(void)data;
	(void)dir;
	(void)inter;
}

void	cast_and_draw_ray(t_data *data, t_edge ray_edge)
{
	t_list		*edge_node;
	t_edge		edge;
	t_vector	inter;
	int			dir;

	edge_node = data->edges;
	while (edge_node)
	{
		edge = *(t_edge *)edge_node->content;
		if (edges_intersect(ray_edge, edge, &inter)
			&& (vector_distance(inter, data->player_pos)
				< vector_distance(ray_edge.end, data->player_pos)))
		{
			ray_edge.end = inter;
			dir = edge.dir;
		}
		edge_node = edge_node->next;
	}
	render_ray(data, dir, ray_edge.end);
	draw_line(data->minimap, ray_edge, 0x0000FFFF);
}

void	rays(t_data *data)
{
	t_edge		ray_edge;
	t_vector	ray_vec;
	t_list		*ray_node;

	ray_node = data->rays;
	while (ray_node)
	{
		ray_vec = *((t_vector *)ray_node->content);
		ray_edge = (t_edge){data->player_pos, vector_add(data->player_pos,
				vector_rotate(vector_scale(ray_vec, RAY_LENGTH
						* MINIMAP_SCALE), data->player_angle)), 0};
		cast_and_draw_ray(data, ray_edge);
		ray_node = ray_node->next;
	}
}