/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:59:40 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/14 19:33:53 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_cast(t_data *data, t_edge *ray_edge, t_vec *inter, int ray_index)
{
	t_list	*sprite_node;
	t_edge	sprite;

	sprite_node = data->sprites;
	while (sprite_node)
	{
		sprite = *(t_edge *)sprite_node->content;
		if (edges_intersect(*ray_edge, sprite, inter)
			&& (vec_dist(*inter, data->player_pos)
				< vec_dist(ray_edge->end, data->player_pos)))
		{
			ray_edge->end = *inter;
			render_ray(data, sprite.tex_index, ray_edge->end, ray_index);
		}
		sprite_node = sprite_node->next;
	}
}

void	door_cast(t_data *data, t_edge *ray_edge, t_vec *inter, int *tex_index)
{
	t_list	*door_node;
	t_door	door;

	door_node = data->doors;
	while (door_node)
	{
		door = *(t_door *)door_node->content;
		if (!door.open && edges_intersect(*ray_edge, door.edge, inter)
			&& (vec_dist(*inter, data->player_pos)
				< vec_dist(ray_edge->end, data->player_pos)))
		{
			*tex_index = 4;
			ray_edge->end = *inter;
		}
		door_node = door_node->next;
	}
}

void	wall_cast(t_data *data, t_edge *ray_edge, t_vec *inter, int *tex_index)
{
	t_edge	edge;
	t_list	*edge_node;

	edge_node = data->wall_edges;
	while (edge_node)
	{
		edge = *(t_edge *)edge_node->content;
		if (edges_intersect(*ray_edge, edge, inter)
			&& (vec_dist(*inter, data->player_pos)
				< vec_dist(ray_edge->end, data->player_pos)))
		{
			ray_edge->end = *inter;
			*tex_index = edge.tex_index;
		}
		edge_node = edge_node->next;
	}
}