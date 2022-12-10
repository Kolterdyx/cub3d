/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:55:23 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 00:14:32 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, t_vector pos)
{
	int		i;
	double	radians;

	i = 0;
	data->player_pos = vector_add(vector_scale(pos, MINIMAP_SCALE),
			(t_vector){PLAYER_HITBOX_RADIUS, PLAYER_HITBOX_RADIUS});
	while (i < FOV * RAYS)
	{
		radians = data->player_angle + ((i / RAYS) * M_PI / 180);
		ft_lstadd_back(&data->rays,
			ft_lstnew(vector_copy(vector_from_angle(radians))));
		i++;
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	data->minimap = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->minimap_offset = (t_vector){0, 0};
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	mlx_set_instance_depth(&data->minimap->instances[0], 1);
	mlx_set_instance_depth(&data->img->instances[0], 0);
	return (data);
}
