/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:55:23 by cigarcia          #+#    #+#             */
/*   Updated: 2023/03/01 18:32:34 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, t_vec pos)
{
	int		i;
	double	radians;

	i = 0;
	data->player_pos = add_vec(vec_scl(pos, TILE_SIZE),
			vec_scl((t_vec){PLAYER_HITBOX_RADIUS, PLAYER_HITBOX_RADIUS},
				TILE_SIZE));
	data->player_angle = -M_PI_2 + (M_PI_2 * data->player_dir);
	while (i < RAYS)
	{
		radians = -(FOV / 2 * M_PI / 180) + i * (FOV / RAYS * M_PI / 180);
		ft_lstadd_back(&data->rays,
			ft_lstnew(vec_cpy(vec_from_rad(radians))));
		i++;
	}
}

t_vec	get_texture_size(t_data *data)
{
	t_vec	size;
	int		i;

	size.x = data->textures[0]->width;
	size.y = data->textures[0]->height;
	while (i < 5)
	{
		if (data->textures[i]->width < size.x)
			size.x = data->textures[i]->width;
		if (data->textures[i]->height < size.y)
			size.y = data->textures[i]->height;
		i++;
	}
	return (size);
}

void	load_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof(mlx_texture_t *));
	data->textures[0] = mlx_load_png(data->textures_path[0]);
	data->textures[1] = mlx_load_png(data->textures_path[1]);
	data->textures[2] = mlx_load_png(data->textures_path[2]);
	data->textures[3] = mlx_load_png(data->textures_path[3]);
	data->textures[4] = mlx_load_png(data->textures_path[4]);
	data->texture_size = get_texture_size(data);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	data->minimap = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_WIDTH, 0);
	mlx_set_instance_depth(&data->minimap->instances[0], 1);
	mlx_set_instance_depth(&data->img->instances[0], 0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	return (data);
}
