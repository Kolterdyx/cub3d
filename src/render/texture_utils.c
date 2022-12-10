/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:08:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 16:38:16 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*cropped_texture(mlx_t *mlx, mlx_texture_t *texture, t_vector origin,
		t_vector size)
{
	mlx_image_t	*cropped;
	uint32_t	xy[3];
	uint32_t	wh[3];

	xy[0] = (uint32_t)origin.x;
	xy[1] = (uint32_t)origin.y;
	wh[0] = (uint32_t)size.x;
	wh[1] = (uint32_t)size.y;
	cropped = mlx_texture_area_to_image(mlx, texture, xy, wh);
	return (cropped);
}

mlx_image_t *scale_image(mlx_image_t *img, t_vector scale)
{
	int x = 0;
	int y = 0;
	mlx_image_t	*new;
	new = mlx_new_image(NULL, scale.x, scale.y);
	while (y < scale.y)
	{
		x = 0;
		while (x < scale.x)
		{
			mlx_put_pixel(new, x, y, img->pixels[(int)((y / (scale.y / img->height)) * img->height + x / (scale.x / img->width))]);
			x++;
		}
		y++;
	}
	return (new);
}
