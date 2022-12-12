/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:55:23 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 03:33:17 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, t_vector pos)
{
	int		i;
	double	radians;

	i = 0;
	data->player_pos = vector_add(vector_scale(pos, TILE_SIZE),
			vector_scale((t_vector){PLAYER_HITBOX_RADIUS, PLAYER_HITBOX_RADIUS},
				TILE_SIZE));
	data->player_angle = M_PI_2 + M_PI / 8;
	while (i < RAYS)
	{
		radians = data->player_angle + ((i * FOV / RAYS) * M_PI / 180);
		ft_lstadd_back(&data->rays,
			ft_lstnew(vector_copy(vector_from_angle(radians))));
		i++;
	}
}

void	load_textures(t_data *data)
{
	data->wall_textures = ft_calloc(5, sizeof(mlx_texture_t *));
	data->wall_textures[0] = mlx_load_png("assets/north_test.png");
	data->wall_textures[1] = mlx_load_png("assets/east_test.png");
	data->wall_textures[2] = mlx_load_png("assets/south_test.png");
	data->wall_textures[3] = mlx_load_png("assets/west_test.png");
	data->texture_size.x = data->wall_textures[0]->width;
	data->texture_size.y = data->wall_textures[0]->height;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	data->minimap = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->ceiling_color = 0x000030FF;
	data->floor_color = 0x003000FF;
	load_textures(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_WIDTH, 0);
	mlx_set_instance_depth(&data->minimap->instances[0], 1);
	mlx_set_instance_depth(&data->img->instances[0], 0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	return (data);
}
