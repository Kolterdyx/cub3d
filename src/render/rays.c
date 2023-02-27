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

void	cast_and_draw_ray(t_data *data, t_edge ray_edge, int ray_index)
{
	t_edge	edge;
	t_vec	inter;
	t_vec	offset;
	int		tex_index;

	tex_index = -1;
	door_cast(data, &ray_edge, &inter, &tex_index);
	wall_cast(data, &ray_edge, &inter, &tex_index);
	render_ray(data, tex_index, ray_edge.end, ray_index);
	offset = sub_vec(data->player_pos, (t_vec){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2});
	edge = (t_edge){sub_vec(ray_edge.start, offset), sub_vec(ray_edge.end, offset), ray_edge.tex_index};
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
