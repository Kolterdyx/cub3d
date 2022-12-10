/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 00:25:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(t_data *data)
{
	t_vector	vel;

	vel = (t_vector){0, 0};
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vel = vector_scale(
				vector_from_angle(data->player_angle
					+ (FOV * M_PI / 180) / 2), PLAYER_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vel = vector_scale(
				vector_from_angle(data->player_angle
					+ M_PI + (FOV * M_PI / 180) / 2), PLAYER_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		vel = vector_scale(
				vector_from_angle(data->player_angle
					- M_PI_2 + (FOV * M_PI / 180) / 2), PLAYER_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		vel = vector_scale(
				vector_from_angle(data->player_angle + M_PI_2
					+ (FOV * M_PI / 180) / 2), PLAYER_SPEED);
	data->player_pos = vector_add(data->player_pos, vel);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player_angle -= PLAYER_ROTATION_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player_angle += PLAYER_ROTATION_SPEED;
	collisions(data);
}

void	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update(data);
	render(data);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	load_map_from_ints(data, (int [(12 * 12)]){
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	}, (t_vector){12, 12});
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	ft_lstclear(&data->edges, free);
	mlx_terminate(data->mlx);
	return (0);
}
