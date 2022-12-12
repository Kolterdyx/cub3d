/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:54:38 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 10:21:12 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_doors(t_data *data)
{
	t_list	*doors;
	t_door	door;

	doors = data->doors;
	while (doors)
	{
		door = *((t_door *)doors->content);
		draw_line(data->minimap, door.edge, 0xFF00FFFF);
		doors = doors->next;
	}
}

void	draw_minimap(t_data *data)
{
	t_list	*edges;
	t_edge	edge;

	mlx_fill_image(data->minimap, 0xFF);
	rays(data);
	draw_doors(data);
	edges = data->wall_edges;
	while (edges)
	{
		edge = *((t_edge *)edges->content);
		draw_line(data->minimap, edge, 0xFFFFFFFF);
		edges = edges->next;
	}
	draw_circle(data->minimap, data->player_pos, PLAYER_HITBOX_RADIUS
		* TILE_SIZE, 0x00FF00FF);
	draw_circle(data->minimap, data->player_pos, PLAYER_INTERACTION_RADIUS
		* TILE_SIZE, 0x00FF00FF);
	draw_line(data->minimap, (t_edge){data->player_pos, add_vec(data->player_pos, vec_scl(vec_from_rad(data->player_angle + M_PI - (FOV / 2) * (M_PI / 180)), 20)),
		0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, 0}, (t_vec){MINIMAP_WIDTH, 0},
		0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, MINIMAP_HEIGHT - 1},
		(t_vec){MINIMAP_WIDTH, MINIMAP_HEIGHT - 1}, 0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, 0}, (t_vec){0, MINIMAP_HEIGHT},
		0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){MINIMAP_WIDTH - 1, 0},
		(t_vec){MINIMAP_WIDTH - 1, MINIMAP_HEIGHT}, 0}, 0xFFFFFFFF);
}
