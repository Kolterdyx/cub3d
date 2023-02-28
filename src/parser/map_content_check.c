/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:14:58 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/28 21:36:41 by apena-ba         ###   ########.fr       */
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

static int	last_check(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_isspace_str(map[i]) == 0)
			return (1);
		i++;
	}
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
				ft_parser_error("door is not attached to two walls or is in bad position\n");
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

static int	skip_nl(char **file)
{
	int		i;
	char	*trimed;

	i = 0;
	while (1)
	{
		trimed = ft_strtrim(file[i], "\n");
		if (!trimed)
			return (-1);
		if (ft_isspace_str(trimed))
		{
			free(trimed);
			i++;
		}
		else
			break ;
	}
	free(trimed);
	return (i);
}

static char	**create_map(char **file)
{
	char	**ret;
	int		i;
	int		j;
	size_t	max_len;

	max_len = 0;
	i = 0;
	if (!file || !*file)
		return (NULL);
	while (ft_strlen(file[i]) > 0 && ft_isspace_str(file[i]) == 0)
	{
		if (ft_strlen(file[i]) > max_len)
			max_len = ft_strlen(file[i]);
		i++;
	}
	ret = ft_calloc(sizeof(char *), ft_charpp_len(file) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (file[i])
	{
		j = 0;
		ret[i] = ft_calloc(sizeof(char), max_len + 1);
		if (!ret[i])
			return (ft_charpp_free(ret), NULL);
		ft_memcpy(ret[i], file[i], ft_strlen(file[i]));
		if (max_len >= ft_strlen(file[i]) && ft_strlen(file[i]) > 0
			&& file[i][ft_strlen(file[i]) - 1] == '\n')
			set_char(ret[i], ft_strlen(file[i]) - 1, max_len, ' ');
		else if (max_len >= ft_strlen(file[i]) && ft_strlen(file[i]) > 0)
			set_char(ret[i], ft_strlen(file[i]), max_len, ' ');
		i++;
	}
	for (int y = 0; ret[y]; y++)
		printf("|%s|\n", ret[y]);
	return (ret);
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
	else if (last_check(map + i))
		ft_parser_error("found characters after map\n");
	return (map);
}
