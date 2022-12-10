/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:08:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 17:25:40 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*cropped_texture(mlx_t *mlx, mlx_texture_t *texture,
		t_vector origin, t_vector size)
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

uint32_t	mlx_get_pixel(mlx_image_t *image, int x, int y)
{
	uint8_t		*pixel;
	uint32_t	color;

	if (x < 0 || y < 0 || x > image->width || y > image->height)
		return (-1);
	pixel = &image->pixels[(int)(y * image->height + x) * 4];
	color = (*(pixel) << 24 | *(pixel + 1) << 16 | *(pixel + 2) << 8 | *(pixel
				+ 3));
	return (color);
}

mlx_image_t	*scale_image(mlx_t *mlx, mlx_image_t *img, t_vector scale)
{
	uint32_t	x;
	uint32_t	y;
	mlx_image_t	*new;

	y = 0;
	new = mlx_new_image(mlx, scale.x * img->width, scale.y * img->height);
	while (y < new->height)
	{
		x = 0;
		while (x < new->width)
		{
			mlx_put_pixel(new, x, y, mlx_get_pixel(img, x / scale.x, y
						/ scale.y));
			x++;
		}
		y++;
	}
	return (new);
}
