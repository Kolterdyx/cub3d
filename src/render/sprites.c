/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:39:26 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/27 19:37:01 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_edge *set_sprites_dir(t_edge *sprite, t_data *data){
    t_edge	*edge = ft_calloc(1, sizeof(t_edge));
    t_vec diff;
    double angle;

    diff = sub_vec(vec_scl(data->player_pos, TILE_SIZE), sub_vec(sprite->start, sprite->end));
	edge->tex_index = 5;
    angle = atan2(diff.y, diff.x) + (M_PI / 2);
	edge->start = (t_vec){cos(angle) * .5 + ((sprite->start.y + sprite->end.y) / 2), sin(angle) * .5 + ((sprite->start.y + sprite->end.y) / 2)};
	edge->end = (t_vec){cos(angle + M_PI) * .5 + ((sprite->start.y + sprite->end.y) / 2), sin(angle + M_PI) * .5 + ((sprite->start.y + sprite->end.y) / 2)};
    free(sprite);
    return(edge);
}

void update_sprites(t_data *data){
    t_list *sprites;

    sprites = data->sprites;
    while(sprites){
        sprites->content = (t_edge *)set_sprites_dir((t_edge *)sprites->content, data);
        sprites = sprites->next;
    }
}
