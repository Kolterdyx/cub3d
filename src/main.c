/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 14:34:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(t_data *data)
{
	t_vec	vel;

	vel = (t_vec){0, 0};
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vel = speed_at_relative_angle(data, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vel = speed_at_relative_angle(data, M_PI);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		vel = speed_at_relative_angle(data, -M_PI_2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		vel = speed_at_relative_angle(data, M_PI_2);
	data->player_pos = add_vec(data->player_pos, vel);
	collisions(data);
}

void	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update(data);
	render(data);
}

void	ft_exit(t_data *data, int code)
{
	mlx_terminate(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_delete_image(data->mlx, data->minimap);
	mlx_delete_texture(data->textures[0]);
	mlx_delete_texture(data->textures[1]);
	mlx_delete_texture(data->textures[2]);
	mlx_delete_texture(data->textures[3]);
	mlx_delete_texture(data->textures[4]);
	free(data->textures);
	ft_lstclear(&data->wall_edges, free);
	ft_lstclear(&data->rays, free);
	ft_lstclear(&data->doors, free);
	free(data);
	exit(code);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	init_map(data, (int [(12 * 16)]){
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 4, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 2, 4, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 4, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	}, (t_vec){12, 16});
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_cursor_hook(data->mlx, cursor_hook, data);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_loop(data->mlx);
	ft_exit(data, 0);
}
