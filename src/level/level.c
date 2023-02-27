/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:08:50 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/27 20:05:33 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_edge	*make_wall_edge(t_vec a, t_vec b, int dir)
{
	return (edge_alloc(vec_scl(a, TILE_SIZE),
			vec_scl(b, TILE_SIZE), dir));
}

void	add_wall(t_data *data, t_vec pos, int direction)
{
	t_edge	*edge;

	if (direction == 0)
		edge = make_wall_edge((t_vec){pos.x, pos.y},
				(t_vec){pos.x + 1, pos.y}, direction);
	else if (direction == 1)
		edge = make_wall_edge((t_vec){pos.x + 1, pos.y},
				(t_vec){pos.x + 1, pos.y + 1}, direction);
	else if (direction == 2)
		edge = make_wall_edge((t_vec){pos.x, pos.y + 1},
				(t_vec){pos.x + 1, pos.y + 1}, direction);
	else if (direction == 3)
		edge = make_wall_edge((t_vec){pos.x, pos.y},
				(t_vec){pos.x, pos.y + 1}, direction);
	else
		return ;
	ft_lstadd_back(&data->wall_edges, ft_lstnew(edge));
}

void	wall_case(t_data *data, t_vec pos, t_vec shape, const int *arr)
{
	t_vec	*vec;

	if (pos.y == 0 || arr[(int)((pos.y - 1) * shape.x + pos.x)] != 1)
		add_wall(data, (t_vec){pos.x, pos.y}, 0);
	if (pos.x == (int)shape.x - 1 || arr[(int)(pos.y * shape.x + pos.x
			+ 1)] != 1)
		add_wall(data, (t_vec){pos.x, pos.y}, 1);
	if (pos.y == (int)shape.y - 1 || arr[(int)((pos.y + 1) * shape.x
			+ pos.x)] != 1)
		add_wall(data, (t_vec){pos.x, pos.y}, 2);
	if (pos.x == 0 || arr[(int)(pos.y * shape.x + pos.x - 1)] != 1)
		add_wall(data, (t_vec){pos.x, pos.y}, 3);
	if (arr[(int)(pos.y * shape.x + pos.x)] == 1)
	{
		vec = ft_calloc(sizeof(t_vec), 1);
		*vec = pos;
		ft_lstadd_back(&data->map, ft_lstnew(vec));
	}
}

void	init_map(t_data *data, const int *arr, t_vec shape)
{
	int	x;
	int	y;
	int	p_exists;

	p_exists = 0;
	y = -1;
	while (++y < shape.y)
	{
		x = -1;
		while (++x < shape.x)
		{
			if (arr[(int)(y * shape.x + x)] == 1)
				wall_case(data, (t_vec){x, y}, shape, arr);
			if (arr[(int)(y * shape.x + x)] == 2 && !p_exists)
			{
				p_exists = 1;
				init_player(data, (t_vec){x, y});
			}
			if (arr[(int)(y * shape.x + x)] == 3)
				init_sprite(data, (t_vec){x, y});
			if (arr[(int)(y * shape.x + x)] == 4)
				init_door(data, (t_vec){x, y}, shape, arr);
		}
	}
}
