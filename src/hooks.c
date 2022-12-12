/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:45 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 16:44:44 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}

void	cursor_hook(double x, double y, void *vdata)
{
	t_data	*data;

	data = vdata;
	if (!is_vector_empty(data->last_mousepos))
		data->player_angle += (x - data->last_mousepos.x) * PLAYER_ROTATION_SPEED;
	data->last_mousepos = (t_vector){x, y};
}
