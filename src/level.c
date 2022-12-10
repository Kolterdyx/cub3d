/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:08:50 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 23:37:20 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_wall(t_data *data, t_vector pos, int direction)
{
	t_edge		*edge;

	if (direction == 0)
		edge = edge_alloc(vector_scale((t_vector){pos.x, pos.y},
					MINIMAP_SCALE), vector_scale(
					(t_vector){pos.x + 1, pos.y}, MINIMAP_SCALE), direction);
	else if (direction == 1)
		edge = edge_alloc(vector_scale((t_vector){pos.x + 1, pos.y},
					MINIMAP_SCALE), vector_scale(
					(t_vector){pos.x + 1, pos.y + 1},
					MINIMAP_SCALE), direction);
	else if (direction == 2)
		edge = edge_alloc(vector_scale((t_vector){pos.x, pos.y + 1},
					MINIMAP_SCALE), vector_scale(
					(t_vector){pos.x + 1, pos.y + 1},
					MINIMAP_SCALE), direction);
	else if (direction == 3)
		edge = edge_alloc(vector_scale((t_vector){pos.x, pos.y},
					MINIMAP_SCALE), vector_scale(
					(t_vector){pos.x, pos.y + 1}, MINIMAP_SCALE), direction);
	else
		return ;
	ft_lstadd_back(&data->edges, ft_lstnew(edge));
}

void	load_map_from_ints(t_data *data, const int *arr, t_vector shape)
{
	int	x;
	int	y;

	y = -1;
	while (++y < shape.y)
	{
		x = -1;
		while (++x < shape.x)
		{
			if (arr[(int)(y * shape.x + x)] == 1)
			{
				if (y == 0 || !arr[(int)((y - 1) * shape.x + x)])
					add_wall(data, (t_vector){x, y}, 0);
				if (x == (int)shape.x - 1 || !arr[(int)(y * shape.x + x + 1)])
					add_wall(data, (t_vector){x, y}, 1);
				if (y == (int)shape.y - 1 || !arr[(int)((y + 1) * shape.x + x)])
					add_wall(data, (t_vector){x, y}, 2);
				if (x == 0 || !arr[(int)(y * shape.x + x - 1)])
					add_wall(data, (t_vector){x, y}, 3);
			}
			if (arr[(int)(y * shape.x + x)] == 2)
				init_player(data, (t_vector){x, y});
		}
	}
}
