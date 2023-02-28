/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:18:32 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/28 19:35:54 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_id(t_parser *parser_info)
{
	int	i;

	i = 0;
	parser_info->name = ft_calloc(sizeof(char *), 8);
	parser_info->value = ft_calloc(sizeof(char *), 8);
	if (!parser_info->name || !parser_info->value)
		return (1);
	parser_info->name[0] = ft_substr("NO", 0, 2);
	parser_info->name[1] = ft_substr("SO", 0, 2);
	parser_info->name[2] = ft_substr("EA", 0, 2);
	parser_info->name[3] = ft_substr("WE", 0, 2);
	parser_info->name[4] = ft_substr("DO", 0, 2);
	parser_info->name[5] = ft_substr("F", 0, 1);
	parser_info->name[6] = ft_substr("C", 0, 1);
	parser_info->value[0] = NULL;
	parser_info->value[1] = NULL;
	parser_info->value[2] = NULL;
	parser_info->value[3] = NULL;
	parser_info->value[4] = NULL;
	parser_info->value[5] = NULL;
	parser_info->value[6] = NULL;
	while (parser_info->name[i])
		i++;
	if (i != 7)
		return (1);
	return (0);
}

static int	line_check(char *line, char *to_comp)
{
	char			**splited;
	char			*trimed;
	mlx_texture_t	*texture;

	splited = ft_split(line, ' ');
	if (ft_charpp_len(splited) != 2)
		return (ft_charpp_free(splited), 1);
	if (ft_strlen(splited[0]) != ft_strlen(to_comp))
		return (ft_charpp_free(splited), 1);
	else if (ft_strncmp(splited[0], to_comp, ft_strlen(to_comp)))
		return (ft_charpp_free(splited), 1);
	trimed = ft_strtrim(splited[1], "\n");
	texture = mlx_load_png(trimed);
	if (!texture)
		return (ft_charpp_free(splited), free(trimed),
			ft_parser_error("failed to open .png file from path provided\n"),
			1);
	mlx_delete_texture(texture);
	ft_charpp_free(splited);
	free(trimed);
	return (0);
}

static int	color_check(char *line, char *to_comp)
{
	char	**splited;
	char	**colors;
	char	*trimed;
	int		i;

	splited = ft_split(line, ' ');
	if (ft_charpp_len(splited) != 2)
		return (ft_charpp_free(splited), 1);
	else if (ft_strlen(splited[0]) != ft_strlen(to_comp))
		return (ft_charpp_free(splited), 1);
	else if (ft_strncmp(splited[0], to_comp, ft_strlen(to_comp)))
		return (ft_charpp_free(splited), 1);
	colors = ft_split(splited[1], ',');
	if (ft_charpp_len(colors) != 3)
		return (ft_charpp_free(splited), ft_charpp_free(colors), 1);
	i = 0;
	while (i < 2)
	{
		if (ft_isdigit_str(colors[i]) == 0)
			return (ft_charpp_free(splited), ft_charpp_free(colors), 1);
		else if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (ft_charpp_free(splited), ft_charpp_free(colors), 1);
		i++;
	}
	trimed = ft_strtrim(colors[2], "\n");
	if (ft_isdigit_str(trimed) == 0)
		return (free(trimed), ft_charpp_free(splited), ft_charpp_free(colors),
			1);
	else if (ft_atoi(trimed) < 0 || ft_atoi(trimed) > 255)
		return (free(trimed), ft_charpp_free(splited), ft_charpp_free(colors),
			ft_parser_error("number in colors must be between 0 and 255\n"), 1);
	ft_charpp_free(splited);
	ft_charpp_free(colors);
	return (free(trimed), 0);
}

static int	get_index_tocomp(char *line, char *value, t_parser *parser_info)
{
	int	i;
	int	max;

	if (ft_strlen(line) == 2)
	{
		i = 0;
		max = 5;
	}
	else if (ft_strlen(line) == 1)
	{
		i = 5;
		max = 7;
	}
	else
		return (-1);
	while (i < max)
	{
		if (ft_strncmp(line, parser_info->name[i],
				ft_strlen(parser_info->name[i])) == 0)
		{
			if (parser_info->value[i] != NULL)
				return (-1);
			parser_info->value[i] = ft_substr(value, 0, ft_strlen(value) - 1);
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	check_final_data(t_parser *parser_info)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (parser_info->value[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

static int	info_check(char *line, t_parser *parser_info)
{
	char	**splited;
	int		index;

	splited = ft_split(line, ' ');
	if (ft_charpp_len(splited) != 2)
		return (ft_charpp_free(splited), 1);
	index = get_index_tocomp(splited[0], splited[1], parser_info);
	ft_charpp_free(splited);
	if (index == -1)
		return (1);
	if (index < 5 && line_check(line, parser_info->name[index]))
		return (1);
	else if (index > 4 && color_check(line, parser_info->name[index]))
		return (1);
	if (check_final_data(parser_info))
		return (2);
	return (0);
}

int	first_part_check(char **file, int *j, t_data *info)
{
	int			i;
	int			check;
	t_parser	parser_info;

	if (!file || !*file)
		return (1);
	i = 0;
	check = 0;
	if (fill_id(&parser_info))
		return (1);
	while (file[i])
	{
		if (ft_isspace_str(file[i]))
			i++;
		else
		{
			check = info_check(file[i], &parser_info);
			if (check == 1){
				return (ft_charpp_nfree(parser_info.name, 7),
					ft_charpp_nfree(parser_info.value, 7), 1);
			}
			else if (check == 2)
				break ;
			i++;
		}
	}
	ft_charpp_free(parser_info.name);
	if (check_final_data(&parser_info) == 0)
		return (1);
	*j = i;
	info->textures_path = parser_info.value;
	return (0);
}
