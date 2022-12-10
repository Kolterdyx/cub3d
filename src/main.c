/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 18:04:38 by cigarcia         ###   ########.fr       */
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

	data = init_data();
	data->wall_north = mlx_load_png("assets/north_test.png");
	draw_texture_area_scaled(data->mlx, data->img, data->wall_north, (t_vector[4]){
			(t_vector){0, 0},
			(t_vector){32, 32},
			(t_vector){2, 1},
			(t_vector){0, 0},
	});
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
