/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 17:24:46 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)data;
}

int	main(void)
{
	t_data		*data;
	mlx_image_t	*i;

	data = init_data();
	data->wall_north = mlx_load_png("assets/north_test.png");
	i = mlx_new_image(data->mlx, 200, 200);
	for (int x = 0; x < (int)i->width; x++)
		for (int y = 0; y < (int)i->height; y++)
			mlx_put_pixel(i, x, y, x * y << 8 | 0xFF);
	mlx_image_to_window(data->mlx, i, 10, 10);
	mlx_image_to_window(data->mlx, scale_image(data->mlx, i, (t_vector){0.5,
				0.5}), 210, 210);
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
