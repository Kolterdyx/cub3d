/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:00:03 by cigarcia          #+#    #+#             */
/*   Updated: 2023/03/10 19:00:55 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_animation_flag(t_data *data, uint32_t flag)
{
	pthread_mutex_lock(data->mutex);
	data->animation_flag = flag;
	pthread_mutex_unlock(data->mutex);
}

uint32_t	get_animation_flag(t_data *data)
{
	uint32_t	flag;

	pthread_mutex_lock(data->mutex);
	flag = data->animation_flag;
	pthread_mutex_unlock(data->mutex);
	return (flag);
}

void	shoot_animation(t_data *data)
{
	t_list		*frame_lst;
	mlx_image_t	*frame;

	frame_lst = data->sprite_lst;
	while (frame_lst)
	{
		frame = frame_lst->content;
		frame->enabled = 1;
		usleep(100000);
		frame->enabled = 0;
		frame_lst = frame_lst->next;
	}
}

void	*animation_thread(void *vdata)
{
	t_data	*data;

	data = vdata;
	while (get_animation_flag(data) & ANIMATION_EXIT)
	{
		if (get_animation_flag(data) & ANIMATION_SHOOT)
		{
			printf("SHOOTING\n");
			shoot_animation(data);
			set_animation_flag(data, 0);
		}
	}
	return (NULL);
}
