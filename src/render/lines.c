/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:12:19 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 23:53:17 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	draw_line(mlx_image_t *img, t_edge edge, uint32_t color)
{
	uint32_t	len = (uint32_t)vector_distance(edge.start, edge.end);
	t_vector	u = vector_normalize(vector_sub(edge.end, edge.start));
	t_vector	d = u;
	t_vector	p;
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		p = vector_add(d, edge.start);
		d = vector_add(u, d);
		put_pixel(img, p.x, p.y, color);
		i++;
	}
}

void	draw_circle(mlx_image_t *img, t_vector pos, double radius, uint32_t color)
{
	float i = 0;
	t_vector p;

	while (i < M_PI * 2)
	{
		p = vector_scale(vector_from_angle(i), radius);
		put_pixel(img, pos.x + p.x, pos.y + p.y, color);
		i += 0.1;
	}
}