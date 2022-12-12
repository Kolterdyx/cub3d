/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:59:40 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 03:30:28 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	wall_pos(t_vector pos, int dir)
{
	t_vector	wall_pos;

	if (!dir)
		wall_pos.x = TILE_SIZE - fmod(pos.x, TILE_SIZE);
	else if (dir == 1)
		wall_pos.x = TILE_SIZE - fmod(pos.y, TILE_SIZE);
	else if (dir == 2)
		wall_pos.x = fmod(pos.x, TILE_SIZE);
	else if (dir == 3)
		wall_pos.x = fmod(pos.y, TILE_SIZE);
	else
		wall_pos.x = 0;
	return (wall_pos);
}

void	render_wall(t_data *data, t_edge rect, t_vector hit_pos)
{
	double	ratio;
	double	wall_height;

	ratio = data->texture_size.x / TILE_SIZE;
	wall_height = 80 * ratio * rect.end.y;
	draw_texture_area_scaled(data->mlx, data->img,
		data->wall_textures[rect.dir],
		(t_vector [4]){
		(t_vector){hit_pos.x * ratio, 0},
		(t_vector){rect.end.x * ratio, data->texture_size.y},
		(t_vector){1, wall_height},
		vector_add(rect.start, (t_vector){0, -wall_height
			* data->texture_size.x / 2})
	});
	(void)hit_pos;
}

void	render_ray(t_data *data, int dir, t_vector inter, int ray_index)
{
	double		dist;
	t_vector	size;

	dist = vector_distance(data->player_pos, inter);
	size.y = (1. / (dist / 4));
	if (size.y > HEIGHT)
		size.y = HEIGHT;
	size.x = WIDTH / RAYS;
	if (size.x > WIDTH)
		size.x = WIDTH;
	render_wall(data, (t_edge){
		(t_vector){ray_index * size.x, HEIGHT / 2 - size.y / 2},
		size, dir}, wall_pos(inter, dir));
}

void	cast_and_draw_ray(t_data *data, t_edge ray_edge, int ray_index)
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
	render_ray(data, dir, ray_edge.end, ray_index);
	draw_line(data->minimap, ray_edge, 0x0000FFFF);
}

void	rays(t_data *data)
{
	t_edge		ray_edge;
	t_vector	ray_vec;
	t_list		*ray_node;
	int			ray_index;

	ray_node = data->rays;
	ray_index = 0;
	while (ray_node)
	{
		ray_vec = *((t_vector *)ray_node->content);
		ray_edge = (t_edge){data->player_pos, vector_add(data->player_pos,
				vector_rotate(vector_scale(ray_vec, RAY_LENGTH
						* TILE_SIZE), data->player_angle)), 0};
		cast_and_draw_ray(data, ray_edge, ray_index);
		ray_node = ray_node->next;
		ray_index++;
	}
}