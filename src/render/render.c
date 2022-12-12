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
	draw_rectangle(data->img, (t_vec){0, 0}, (t_vec){WIDTH, HEIGHT / 2}, data->ceiling_color);
	draw_rectangle(data->img, (t_vec){0, HEIGHT / 2}, (t_vec){WIDTH, HEIGHT / 2}, data->floor_color);
	draw_minimap(data);
}

void	render_wall(t_data *data, t_edge rect, t_vec hit_pos)
{
	double	ratio;
	double	wall_height;

	ratio = data->texture_size.x / TILE_SIZE;
	wall_height = 80 * ratio * rect.end.y;
	draw_texture_area_scaled(data->mlx, data->img,
							 data->textures[rect.dir],
							 (t_vec [4]){
									 (t_vec){hit_pos.x * ratio, 0},
									 (t_vec){rect.end.x * ratio, data->texture_size.y},
									 (t_vec){1, wall_height},
									 add_vec(rect.start, (t_vec) {0, -wall_height
																	 * data->texture_size.x / 2})
							 });
	(void)hit_pos;
}

void	render_ray(t_data *data, int dir, t_vec inter, int ray_index)
{
	double		dist;
	t_vec		size;

	dist = vec_dist(data->player_pos, inter);
	size.y = (1. / (dist / 4));
	if (size.y > HEIGHT)
		size.y = HEIGHT;
	size.x = WIDTH / RAYS;
	if (size.x > WIDTH)
		size.x = WIDTH;
	render_wall(data, (t_edge){
			(t_vec){ray_index * size.x, HEIGHT / 2 - size.y / 2},
			size, dir}, wall_pos(inter, dir));
}