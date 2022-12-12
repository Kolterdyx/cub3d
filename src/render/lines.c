/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:12:19 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 04:47:48 by cigarcia         ###   ########.fr       */
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
	uint32_t	len;
	t_vec	unit;
	t_vec	delta;
	t_vec	point;
	uint32_t	i;

	len = (uint32_t) vec_dist(edge.start, edge.end);
	unit = vec_unit(sub_vec(edge.end, edge.start));
	delta = unit;
	i = 0;
	while (i < len)
	{
		point = add_vec(delta, edge.start);
		delta = add_vec(unit, delta);
		put_pixel(img, point.x, point.y, color);
		i++;
	}
}

void	draw_circle(mlx_image_t *img, t_vec pos, double radius,
					uint32_t color)
{
	float		i;
	t_vec	p;

	i = 0;
	while (i < M_PI * 2)
	{
		p = vec_scl(vec_from_rad(i), radius);
		put_pixel(img, pos.x + p.x, pos.y + p.y, color);
		i += 0.1;
	}
}

void	draw_rectangle(mlx_image_t *img, t_vec pos, t_vec size,
					   uint32_t color)
{
	t_vec	p;

	p.y = pos.y;
	while (p.y < pos.y + size.y)
	{
		p.x = pos.x;
		while (p.x < pos.x + size.x)
		{
			put_pixel(img, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}
