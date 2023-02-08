/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:59:40 by cigarcia          #+#    #+#             */
/*   Updated: 2023/01/17 17:54:43 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	door_pos(t_vec pos)
{
	double	x;
	double	y;

	x = fmod(pos.x, TILE_SIZE);
	y = fmod(pos.y, TILE_SIZE);
	if (round(y) == TILE_SIZE / 2)
		return (x);
	else if (round(x) == TILE_SIZE / 2)
		return (y);
	return (0);
}

t_vec	wall_pos(t_vec pos, int dir)
{
	t_vec	wall_pos;

	if (!dir)
		wall_pos.x = TILE_SIZE - fmod(pos.x, TILE_SIZE);
	else if (dir == 1)
		wall_pos.x = TILE_SIZE - fmod(pos.y, TILE_SIZE);
	else if (dir == 2)
		wall_pos.x = fmod(pos.x, TILE_SIZE);
	else if (dir == 3)
		wall_pos.x = fmod(pos.y, TILE_SIZE);
	else if (dir == 4)
		wall_pos.x = door_pos(pos);
	else
		wall_pos.x = 0;
	return (wall_pos);
}

void	door_cast(t_data *data, t_edge *ray_edge, t_vec *inter, int *dir)
{
	t_list	*door_node;
	t_door	door;

	door_node = data->doors;
	while (door_node)
	{
		door = *(t_door *)door_node->content;
		if (!door.open && edges_intersect(*ray_edge, door.edge, inter)
			&& (vec_dist(*inter, data->player_pos) < vec_dist(ray_edge->end,
					data->player_pos)))
		{
			*dir = 4;
			ray_edge->end = *inter;
		}
		door_node = door_node->next;
	}
}

void	cast_and_draw_ray(t_data *data, t_edge ray_edge, int ray_index)
{
	t_list	*edge_node;
	t_edge	edge;
	t_vec	inter;
	t_vec	offset;
	int		dir;

	dir = -1;
	edge_node = data->wall_edges;
	while (edge_node)
	{
		edge = *(t_edge *)edge_node->content;
		if (edges_intersect(ray_edge, edge, &inter) && (vec_dist(inter,
					data->player_pos) < vec_dist(ray_edge.end,
					data->player_pos)))
		{
			ray_edge.end = inter;
			dir = edge.dir;
		}
		edge_node = edge_node->next;
	}
	door_cast(data, &ray_edge, &inter, &dir);
	render_ray(data, dir, ray_edge.end, ray_index);
	offset = sub_vec(data->player_pos, (t_vec){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2});
	edge = (t_edge){sub_vec(ray_edge.start, offset), sub_vec(ray_edge.end, offset), ray_edge.dir};
	draw_line(data->minimap, edge, 0x0000FFFF);
}

void	rays(t_data *data)
{
	t_edge	ray_edge;
	t_vec	ray_vec;
	t_list	*ray_node;
	int		ray_index;

	ray_node = data->rays;
	ray_index = 0;
	while (ray_node)
	{
		ray_vec = *((t_vec *)ray_node->content);
		ray_edge = (t_edge){data->player_pos, add_vec(data->player_pos,
				vec_rotate(vec_scl(ray_vec, RAY_LENGTH * TILE_SIZE),
					data->player_angle)), 0};
		cast_and_draw_ray(data, ray_edge, ray_index);
		ray_node = ray_node->next;
		ray_index++;
	}
}
