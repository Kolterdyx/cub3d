/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:26:49 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/28 22:17:36 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_max_line_len(char **map)
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

void	evaluate(int **map_arr, int *x, char c)
{
	if (c == '1' || c == '0' || c == '4')
		map_arr[0][(*x)++] = c - 48;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		map_arr[0][(*x)++] = 2;
	else if (c == 'D')
		map_arr[0][(*x)++] = 4;
	else if (c == ' ')
		(*x)++;
}

int	map_filler(char **map, int **map_arr, t_vec *dimensions)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	map_arr[0] = ft_calloc(sizeof(int), ft_charpp_len(map)
			* get_max_line_len(map));
	if (!*map_arr)
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			evaluate(map_arr, &x, map[i][j]);
			j++;
		}
		i++;
	}
	dimensions->x = get_max_len(map);
	dimensions->y = ft_charpp_len(map);
	return (0);
}
