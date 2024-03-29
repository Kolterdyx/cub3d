/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 22:36:27 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/27 20:03:56 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_collisions(t_data *data, t_list *node)
{
	t_edge	edge;
	t_vec	point;
	double	dist;

	while (node)
	{
		edge = *((t_edge *)node->content);
		if (edge_intersects_circle(edge, data->player_pos, PLAYER_HITBOX_RADIUS
				* TILE_SIZE, &point))
		{
			dist = PLAYER_HITBOX_RADIUS * TILE_SIZE - vec_len(sub_vec(point,
						data->player_pos));
			data->player_pos = sub_vec(data->player_pos,
					vec_scl(vec_unit(sub_vec(point, data->player_pos)), dist));
		}
		node = node->next;
	}
}

void	door_collisions(t_data *data, t_list *node)
{
	t_door	door;
	t_vec	point;
	double	dist;

	while (node)
	{
		door = *((t_door *)node->content);
		if (!door.open && edge_intersects_circle(door.edge, data->player_pos,
				PLAYER_HITBOX_RADIUS * TILE_SIZE, &point))
		{
			dist = PLAYER_HITBOX_RADIUS * TILE_SIZE - vec_len(sub_vec(point,
						data->player_pos));
			data->player_pos = sub_vec(data->player_pos,
					vec_scl(vec_unit(sub_vec(point, data->player_pos)), dist));
		}
		node = node->next;
	}
}

void	collisions(t_data *data)
{
	wall_collisions(data, data->wall_edges);
	door_collisions(data, data->doors);
}

t_vec	calc_velocity(t_data *data, double angle)
{
	t_vec	vel;

	vel = vec_from_rad(data->player_angle + angle);
	vel = vec_scl(vel, PLAYER_SPEED * TILE_SIZE);
	return (vel);
}
