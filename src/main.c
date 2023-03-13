/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2023/03/13 20:49:04 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	movement(t_data *data);

void	update(t_data *data)
{
	t_vec	vel;
	double	len1;
	double	len2;

	collisions(data);
	vel = movement(data);
	if (is_vector_empty(vel))
		return ;
	len1 = vec_len(calc_velocity(data, 0));
	len2 = vec_len(vel);
	vel = vec_scl(vec_scl(vel, 1 / len2), len1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		vel = vec_scl(vel, PLAYER_SPRINT_RATIO);
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
	mlx_delete_image(data->mlx, data->img);
	mlx_delete_image(data->mlx, data->minimap);
	mlx_delete_texture(data->textures[0]);
	mlx_delete_texture(data->textures[1]);
	mlx_delete_texture(data->textures[2]);
	mlx_delete_texture(data->textures[3]);
	mlx_delete_texture(data->textures[4]);
	mlx_delete_texture(data->textures[5]);
	ft_charpp_free(data->textures_path);
	free(data->textures);
	ft_lstclear(&data->wall_edges, free);
	ft_lstclear(&data->rays, free);
	ft_lstclear(&data->doors, free);
	ft_lstclear(&data->map, free);
	set_animation_flag(data, ANIMATION_EXIT);
	usleep(SPRITE_TIME_OFFSET * SPRITE_COUNT);
	free_sprites(data);
	pthread_mutex_destroy(data->mutex);
	free(data->mutex);
	pthread_join(*data->animation_thread, NULL);
	free(data->animation_thread);
	mlx_terminate(data->mlx);
	free(data);
	exit(code);
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
	ft_exit(data, 0);
}
