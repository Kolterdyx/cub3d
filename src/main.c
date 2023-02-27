/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/27 20:20:40 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(t_data *data)
{
	t_vec	vel;

	vel = (t_vec){0, 0};
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vel = calc_velocity(data, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vel = calc_velocity(data, M_PI);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		vel = calc_velocity(data, -M_PI_2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		vel = calc_velocity(data, M_PI_2);
	collisions(data);
	data->player_pos = add_vec(data->player_pos, vel);
	update_sprites(data);
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
	ft_lstclear(&data->sprites, free);
	free(data);
	exit(code);
}

void	ft(void)
{
	system("leaks -q cub3D");
}

void	load_colors(t_data *data)
{
	char		**ceil;
	char		**floor;
	uint32_t	c;
	uint32_t	f;

	ceil = ft_split(data->textures_path[7], ',');
	floor = ft_split(data->textures_path[6], ',');
	c = (ft_atoi(ceil[0]) << 24)
		| (ft_atoi(ceil[1]) << 16) | (ft_atoi(ceil[2]) << 8) | 0xFF;
	f = (ft_atoi(floor[0]) << 24)
		| (ft_atoi(floor[1]) << 16) | (ft_atoi(floor[2]) << 8) | 0xFF;
	data->ceiling_color = c;
	data->floor_color = f;
	ft_charpp_free(floor);
	ft_charpp_free(ceil);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		*map_arr;
	t_vec	dimensions;

	atexit(ft);
	(void)argc;
	data = init_data();
	parser(data, argv, &map_arr, &dimensions);
	load_colors(data);
	load_textures(data);
	init_map(data, map_arr, dimensions);
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_cursor_hook(data->mlx, cursor_hook, data);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_loop(data->mlx);
	ft_charpp_free(data->textures_path);
	ft_exit(data, 0);
}
