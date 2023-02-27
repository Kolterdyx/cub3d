/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:26:49 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/27 20:17:56 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_len(char **map)
{
	int		i;
	size_t	max_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

int	map_filler(char **map, int **map_arr, t_vec *dimensions)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	map_arr[0] = ft_calloc(sizeof(int), ft_charpp_len(map) * get_max_len(map));
	if (!*map_arr)
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == '4')
				map_arr[0][x++] = map[i][j] - 48;
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W')
				map_arr[0][x++] = 2;
			else if (map[i][j] == 'D')
				map_arr[0][x++] = 4;
			else if (map[i][j] == ' ')
				x++;
			j++;
		}
		i++;
	}
	dimensions->x = get_max_len(map);
	dimensions->y = ft_charpp_len(map);
	return (0);
}
