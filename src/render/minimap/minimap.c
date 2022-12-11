/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:54:38 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 15:00:41 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_data *data)
{
	t_list	*edges;
	t_edge	edge;

	mlx_fill_image(data->minimap, 0xFF);
	rays(data);
	edges = data->edges;
	while (edges)
	{
		edge = *((t_edge *)edges->content);
		draw_line(data->minimap, edge, 0xFFFFFFFF);
		edges = edges->next;
	}
	draw_circle(data->minimap, data->player_pos, PLAYER_HITBOX_RADIUS
		* MINIMAP_SCALE, 0x00FF00FF);
	draw_line(data->minimap, (t_edge){(t_vector){0, 0},
		(t_vector){MINIMAP_WIDTH, 0}, 0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){
		(t_vector){0, MINIMAP_HEIGHT - 1},
		(t_vector){MINIMAP_WIDTH, MINIMAP_HEIGHT - 1}, 0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vector){0, 0}, (t_vector){0,
		MINIMAP_HEIGHT}, 0}, 0xFFFFFFFF);
	draw_line(data->minimap, (t_edge){(t_vector){MINIMAP_WIDTH - 1, 0},
		(t_vector){MINIMAP_WIDTH - 1, MINIMAP_HEIGHT}, 0}, 0xFFFFFFFF);
}
