/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:06:30 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/11 00:10:32 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data)
{
	mlx_fill_image(data->img, 0x000033FF);
	draw_rectangle(data->img, (t_vector){0, 0}, (t_vector){WIDTH, HEIGHT/2}, data->ceiling_color);
	draw_rectangle(data->img, (t_vector){0, HEIGHT/2}, (t_vector){WIDTH, HEIGHT/2}, data->floor_color);
	draw_minimap(data);
}
