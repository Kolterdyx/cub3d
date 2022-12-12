/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:45 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:58:09 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_data *data)
{
	t_door	*door;
	t_list	*node;
	t_vec	point;

	node = data->doors;
	while (node)
	{
		door = ((t_door *)node->content);
		if (edge_intersects_circle(door->edge, data->player_pos,
				PLAYER_INTERACTION_RADIUS * TILE_SIZE, &point))
			door->open = !door->open;
		node = node->next;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		open_door(data);
}

void	cursor_hook(double x, double y, void *vdata)
{
	t_data	*data;

	data = vdata;
	if (!is_vector_empty(data->last_mousepos))
		data->player_angle += (x - data->last_mousepos.x)
			* PLAYER_ROTATION_SPEED;
	data->last_mousepos = (t_vec){x, y};
}

void	mouse_hook(mouse_key_t key, action_t action, modifier_key_t mod,
		void *vdata)
{
	t_data	*data;

	data = vdata;
	(void)mod;
	if (!(key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS))
		return ;
	open_door(data);
}
