/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:43:16 by cigarcia          #+#    #+#             */
/*   Updated: 2023/03/01 18:21:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	map_range(double value, t_vec old_range, t_vec new_range)
{
	return (new_range.x + (value - old_range.x) * (new_range.y - new_range.x)
		/ (old_range.y - old_range.x));
}

void	mlx_fill_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
			put_pixel(img, x++, y, color);
		y++;
	}
}

uint32_t	rgb_to_int(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

t_list	*ft_lsti(t_list *lst, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
