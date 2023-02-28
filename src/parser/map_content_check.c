/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:14:58 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/28 22:12:56 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	square_check(char **file, int i, size_t x)
{
	if (i == 0 || x == 0 || i == ft_charpp_len(file) - 1
		|| x == ft_strlen(file[i]) - 1)
		return (1);
	if (file[i - 1][x] == ' ' || file[i + 1][x] == ' ')
		return (1);
	if (file[i][x - 1] == ' ' || file[i][x + 1] == ' ')
		return (1);
	return (0);
}

static int	door_check(char **file, int i, size_t x)
{
	if (i == 0 || x == 0 || i == ft_charpp_len(file) - 1
		|| x == ft_strlen(file[i]) - 1)
		return (1);
	if (file[i - 1][x] == ' ' || file[i + 1][x] == ' ')
		return (1);
	if (file[i][x - 1] == ' ' || file[i][x + 1] == ' ')
		return (1);
	if (file[i][x - 1] == '1')
		if (file[i][x + 1] == '1' && file[i - 1][x] != '1' && file[i
			+ 1][x] != '1')
			return (0);
	if (file[i - 1][x] == '1')
		if (file[i + 1][x] == '1' && file[i][x - 1] != '1' && file[i][x
			+ 1] != '1')
			return (0);
	return (1);
}

static void	line_check(char **file, int *i, int *flag, t_data *info)
{
	int	x;

	x = 0;
	while (file[*i][x])
	{
		if (condition(file[*i][x]))
			ft_parser_error("unable character found in map\n");
		else if (file[*i][x] == '0' && square_check(file, *i, x))
			ft_parser_error("map is not surrounded by walls\n");
		else if (file[*i][x] == 'N' || file[*i][x] == 'S' || file[*i][x] == 'E'
				|| file[*i][x] == 'W')
		{
			if (*flag == 1)
				ft_parser_error("double character\n");
			else if (square_check(file, *i, x) == 0)
				info->player_dir = get_player_dir(file[*i][x], flag);
			else
				ft_parser_error("bad position for player\n");
		}
		else if (file[*i][x] == 'D')
			if (door_check(file, *i, x))
				ft_parser_error("door in bad position\n");
		x++;
	}
}

static int	content_check(char **file, int *i, t_data *info)
{
	int	x;
	int	flag;

	flag = 0;
	*i = 0;
	while (file[*i])
	{
		x = 0;
		line_check(file, i, &flag, info);
		if (ft_isspace_str(file[*i]) == 1)
			break ;
		*i += 1;
	}
	if (flag == 0)
		ft_parser_error("no player found\n");
	return (0);
}

char	**second_part_check(char **file, t_data *info)
{
	int		i;
	char	**map;

	i = skip_nl(file);
	if (i == -1)
		return (ft_charpp_free(file), NULL);
	map = create_map(file + i);
	if (!map)
		return (ft_charpp_free(file), NULL);
	if (content_check(map, &i, info))
		return (ft_charpp_free(file), ft_charpp_free(map));
	while (map[i])
	{
		if (ft_isspace_str(map[i]) == 0)
			ft_parser_error("found characters after map\n");
		i++;
	}
	return (map);
}
