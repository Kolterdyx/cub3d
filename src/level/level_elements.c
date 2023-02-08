/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:40:42 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:47:59 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_data *data, t_vec pos)
{
	t_edge	*edge = ft_calloc(1, sizeof(t_edge));
	edge->tex_index = 5;
	edge->start = vec_scl((t_vec){pos.x, pos.y + 0.5f}, TILE_SIZE);
	edge->end = vec_scl((t_vec){pos.x + 1, pos.y + 0.5f}, TILE_SIZE);

	ft_lstadd_back(&data->sprites, ft_lstnew(edge));
}

t_door	*door_alloc(t_vec pos, int dir)
{
	t_door	*door;

	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	if (dir == 0)
		door->edge = (t_edge){
			vec_scl((t_vec){pos.x + .5, pos.y}, TILE_SIZE),
			vec_scl((t_vec){pos.x + .5, pos.y + 1}, TILE_SIZE),
			dir};
	else if (dir == 1)
		door->edge = (t_edge){
			vec_scl((t_vec){pos.x, pos.y + .5}, TILE_SIZE),
			vec_scl((t_vec){pos.x + 1, pos.y + .5}, TILE_SIZE),
			dir};
	door->dir = dir;
	door->open = 0;
	return (door);
}

void	init_door(t_data *data, t_vec pos, t_vec shape, const int *arr)
{
	int	dir;

	dir = 0;
	if (arr_index(add_vec(pos, (t_vec){0, -1}), arr, shape.x, 1) &&
		arr_index(add_vec(pos, (t_vec){0, 1}), arr, shape.x, 1))
		dir = 0;
	else if (arr_index(add_vec(pos, (t_vec){-1, 0}), arr, shape.x, 1) &&
				arr_index(add_vec(pos, (t_vec){1, 0}), arr, shape.x, 1))
		dir = 1;
	else
		return ;
	if (dir == 0)
	{
		add_wall(data, (t_vec){pos.x, pos.y - 1}, 2);
		add_wall(data, (t_vec){pos.x, pos.y + 1}, 0);
	}
	else if (dir == 1)
	{
		add_wall(data, (t_vec){pos.x - 1, pos.y}, 1);
		add_wall(data, (t_vec){pos.x + 1, pos.y}, 3);
	}
	ft_lstadd_back(&data->doors, ft_lstnew(door_alloc(pos, dir)));
}
