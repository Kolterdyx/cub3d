/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:55:23 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 15:06:10 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, t_vector pos, double angle)
{
	int		i;
	double	a;
	double	radians;

	i = 0;
	data->player_pos = pos;
	data->player_dir = vector_from_angle(angle);
	while (i < FOV * RAYS)
	{
		a = (i * (FOV / RAYS)) - (FOV / 2);
		radians = angle + (a * M_PI / 180);
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
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (data);
}
