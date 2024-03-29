/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:06:30 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/27 19:10:02 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data)
{
	mlx_fill_image(data->img, 0x000033FF);
	draw_rectangle(data->img, (t_vec){0, 0}, (t_vec){WIDTH, HEIGHT / 2},
		data->ceiling_color);
	draw_rectangle(data->img, (t_vec){0, HEIGHT / 2}, (t_vec){WIDTH, HEIGHT
		/ 2}, data->floor_color);
	draw_calls(data);
}

void	render_wall(t_data *data, t_edge rect, t_vec hit_pos)
{
	double	ratio;
	double	wall_height;

	ratio = data->texture_size.x / TILE_SIZE;
	wall_height = (TILE_SIZE * 4) * pow(32. / data->texture_size.x, 2) * ratio
		* rect.end.y;
	draw_texture_area_scaled(data->mlx, data->img,
		data->textures[rect.tex_index],
		(t_vec[4]){(t_vec){hit_pos.x * ratio, 0}, (t_vec){fmax(rect.end.x
			* ratio, 1.), fmax(data->texture_size.y, 1.)},
		(t_vec){1, wall_height},
		add_vec(rect.start, (t_vec){0, -wall_height * data->texture_size.x
			/ 2})});
	(void)hit_pos;
}

void	render_ray(t_data *data, int tex_index, t_vec inter, int ray_index)
{
	double	dist;
	t_vec	size;
	double	ray_angle;

	if (tex_index == -1)
		return ;
	ray_angle = ((ray_index * FOV / RAYS) * M_PI / 180);
	dist = vec_dist(data->player_pos, inter) * cos(ray_angle
			- (FOV * M_PI / 180) / 2);
	size.y = (1. / fmax(0.01f, dist / 4));
	size.x = WIDTH / RAYS;
	if (size.x > WIDTH)
		size.x = WIDTH;
	if (size.x < 1)
		size.x = 1;
	render_wall(data, (t_edge){(t_vec){ray_index * size.x, HEIGHT / 2 - size.y
		/ 2}, size, tex_index}, wall_pos(inter, tex_index));
}
