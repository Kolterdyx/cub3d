/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:37:06 by cigarcia          #+#    #+#             */
/*   Updated: 2023/03/13 19:55:32 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	basic_check(int argc, char **argv)
{
	char	*sub1;
	char	*sub2;

	if (argc != 2)
		return (1);
	else if (ft_strlen(argv[1]) < 4)
		return (1);
	sub1 = ft_substr(".cub", 0, 4);
	sub2 = ft_strrchr(argv[1], '.');
	if (!sub1 || !sub2)
	{
		free(sub1);
		return (1);
	}
	else if (ft_strlen(sub1) != ft_strlen(sub2))
		return (free(sub1), 1);
	else if (ft_strncmp(sub1, sub1, 4) != 0)
		ft_parser_error("file provided is not .cub\n");
	free(sub1);
	return (0);
}

static int	map_check(char ***map, t_data *info)
{
	int		i;
	char	**copy;

	copy = ft_charpp_cpy(*map);
	if (ft_charpp_len(copy) < 10)
		return (ft_charpp_free(*map), ft_charpp_free(copy), 1);
	i = 0;
	if (first_part_check(copy, &i, info))
		return (ft_charpp_free(*map), ft_charpp_free(copy), 1);
	ft_charpp_free(*map);
	*map = second_part_check(copy + i + 1, info);
	if (!*map)
		return (ft_charpp_free(*map), ft_charpp_free(copy), 1);
	ft_charpp_free(copy);
	return (0);
}

static char	**get_map_from_file(int fd)
{
	char	*line;
	char	**ret;

	ret = ft_calloc(sizeof(char *), 2);
	line = get_next_line(fd);
	if (!line)
		return (free(ret), NULL);
	while (line != NULL)
	{
		ret = ft_arradd_back(ret, line);
		if (!ret)
			return (NULL);
		line = get_next_line(fd);
	}
	return (ret);
}

int	parser(t_data *info, char **argv, int **map_arr, t_vec *dimensions)
{
	int		fd;
	char	**map;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (basic_check(argc, argv))
		ft_parser_error("basic data is incorrect\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_parser_error("file opening went wrong\n");
	map = get_map_from_file(fd);
	if (!map)
		return (close(fd), ft_parser_error("map couldn't be created\n"), 1);
	if (map_check(&map, info) != 0)
		return (close(fd), ft_parser_error("data in file is incorrect\n"), 1);
	if (map_filler(map, map_arr, dimensions))
		return (close(fd), ft_parser_error("map filling went wrong\n"), 1);
	close(fd);
	ft_charpp_free(map);
	return (0);
}
