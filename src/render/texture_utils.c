/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:08:33 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 19:49:50 by cigarcia         ###   ########.fr       */
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
	uint32_t	color;
	int			i;

	i = 0;
	color = 0;
	if (x < 0 || y < 0 || x > (int)image->width || y > (int)image->height)
		return (-1);
	while (i < 4)
	{
		color |= image->pixels[(y * image->width + x) * 4 + i] << (8 * (3 - i));
		i++;
	}
	return (color);
}

mlx_image_t	*scale_image(mlx_t *mlx, mlx_image_t *img, t_vector scale)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	mlx_image_t	*new;

	y = 0;
	new = mlx_new_image(mlx, scale.x * img->width, scale.y * img->height);
	while (y < new->height)
	{
		x = 0;
		while (x < new->width)
		{
			color = mlx_get_pixel(img,
					floor(map_range(x,
							(t_vector){0, new->width},
							(t_vector){0, img->width})),
					floor(map_range(y,
							(t_vector){0, new->height},
							(t_vector){0, img->height})));
			mlx_put_pixel(new, x, y, color);
			x++;
		}
		y++;
	}
	return (new);
}

void	draw_texture_area_scaled(mlx_t *mlx, mlx_image_t *img,
		mlx_texture_t *texture, t_vector *area)
{
	mlx_image_t	*temp;
	mlx_image_t	*temp2;
	int			x;
	int			y;

	y = 0;
	temp = cropped_texture(mlx, texture, area[0], area[1]);
	temp2 = scale_image(mlx, temp, area[2]);
	mlx_delete_image(mlx, temp);
	while (y < (int)temp2->height)
	{
		x = 0;
		while (x < (int)temp2->width)
		{
			mlx_put_pixel(img, x, y, mlx_get_pixel(temp2, x, y));
			x++;
		}
		y++;
	}
	mlx_delete_image(mlx, temp2);
}
