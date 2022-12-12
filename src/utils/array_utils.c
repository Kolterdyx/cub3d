/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:32:04 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/12 06:43:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	arr_index(t_vec pos, const int *arr, int width, int default_value)
{
	if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= width)
		return (default_value);
	return (arr[(int)pos.y * width + (int)pos.x]);
}
