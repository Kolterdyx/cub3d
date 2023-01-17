/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:54:38 by cigarcia          #+#    #+#             */
/*   Updated: 2023/01/17 17:55:39 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_doors(t_data *data, t_vec offset)
{
	t_list	*doors;
	t_door	door;

	doors = data->doors;
	while (doors)
	{
		door = *((t_door *)doors->content);
		door.edge = (t_edge){sub_vec(door.edge.start, offset), sub_vec(door.edge.end, offset), door.edge.dir};
		draw_line(data->minimap, door.edge, 0xFF00FFFF);
		doors = doors->next;
	}
}

void	draw_minimap(t_data *data)
{
	t_list	*edges;
	t_edge	edge;
	t_vec	offset;

	offset = sub_vec(data->player_pos, (t_vec){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2});
	edges = data->wall_edges;
	while (edges)
	{
		edge = *((t_edge *)edges->content);
		edge = (t_edge){sub_vec(edge.start, offset), sub_vec(edge.end, offset), edge.dir};
		draw_line(data->minimap, edge, 0xFFFFFFFF);
		edges = edges->next;
	}
	draw_circle(data->minimap, sub_vec(data->player_pos, offset), PLAYER_HITBOX_RADIUS
												 * TILE_SIZE, 0x00FF00FF);
	draw_circle(data->minimap, sub_vec(data->player_pos, offset), PLAYER_INTERACTION_RADIUS
												 * TILE_SIZE, 0x00FF00FF);
	draw_line(data->minimap, (t_edge){sub_vec(data->player_pos, offset), add_vec(sub_vec(data->player_pos, offset), vec_scl(vec_from_rad(data->player_angle + M_PI - (FOV / 2) * (M_PI / 180)), 20)),
									  0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, 0}, (t_vec){MINIMAP_WIDTH, 0},
									  0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, MINIMAP_HEIGHT - 1},
									  (t_vec){MINIMAP_WIDTH, MINIMAP_HEIGHT - 1}, 0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){0, 0}, (t_vec){0, MINIMAP_HEIGHT},
									  0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vec){MINIMAP_WIDTH - 1, 0},
									  (t_vec){MINIMAP_WIDTH - 1, MINIMAP_HEIGHT}, 0}, 0xFFFFFFFF);
	draw_doors(data, offset);
}

void	draw_calls(t_data *data)
{
	mlx_fill_image(data->minimap, 0xFF);
	rays(data);
	draw_minimap(data);
}
