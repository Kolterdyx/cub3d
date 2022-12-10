/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 22:36:27 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 23:18:15 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collisions(t_data *data)
{
	t_list		*node;
	t_edge		edge;
	t_vector	point;
	double		dist;

	node = data->edges;
	while (node)
	{
		edge = *((t_edge *)node->content);
		if (edge_intersects_circle(edge, data->player_pos,
				PLAYER_HITBOX_RADIUS, &point))
		{
			dist = PLAYER_HITBOX_RADIUS
				- vector_length(vector_sub(point, data->player_pos));
			data->player_pos = vector_sub(data->player_pos,
					vector_scale(vector_normalize(
							vector_sub(point, data->player_pos)), dist));
		}
		node = node->next;
	}
}
