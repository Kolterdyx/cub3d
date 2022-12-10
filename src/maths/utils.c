/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:43:16 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 18:44:24 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	map_range(double value, t_vector old_range, t_vector new_range)
{
	return (new_range.x + (value - old_range.x) * (new_range.y - new_range.x)
		/ (old_range.y - old_range.x));
}