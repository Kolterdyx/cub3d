/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 04:08:22 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(t_data *data)
{
	t_vector	vel;

	vel = (t_vector){0, 0};
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vel = speed_at_relative_angle(data, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vel = speed_at_relative_angle(data, M_PI);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		vel = speed_at_relative_angle(data, -M_PI_2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		vel = speed_at_relative_angle(data, M_PI_2);
	data->player_pos = vector_add(data->player_pos, vel);
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
	mlx_delete_texture(data->wall_textures[0]);
	mlx_delete_texture(data->wall_textures[1]);
	mlx_delete_texture(data->wall_textures[2]);
	mlx_delete_texture(data->wall_textures[3]);
	free(data->wall_textures);
	ft_lstclear(&data->edges, free);
	ft_lstclear(&data->rays, free);
	free(data->mlx);
	exit(code);
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
	mlx_cursor_hook(data->mlx, cursor_hook, data);
	mlx_loop(data->mlx);
	ft_exit(data, 0);
}
