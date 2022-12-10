/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 16:39:13 by cigarcia         ###   ########.fr       */
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
	i = mlx_new_image(data->mlx, 100, 100);
	for (int x = 0; x < 100; x++)
		for (int y = 0; y < 100; y++)
			mlx_put_pixel(i, x, y, x * y << 8 | 0xFF);
	mlx_image_to_window(data->mlx, i, 10, 10);
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
