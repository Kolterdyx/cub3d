/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:18:32 by apena-ba          #+#    #+#             */
/*   Updated: 2023/03/13 19:56:18 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	check_final_data(t_parser *parser_info)
{
	int	i;

	i = 0;
	while (i < 8)
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
	if (index < 6 && line_check(line, parser_info->name[index]))
		return (1);
	else if (index > 5 && color_check(line, parser_info->name[index]))
		return (1);
	if (check_final_data(parser_info))
		return (2);
	return (0);
}

static int	check_loop(char **file, int *i, int *check, t_parser *parser_info)
{
	while (file[*i])
	{
		if (ft_isspace_str(file[*i]))
			*i += 1;
		else
		{
			*check = info_check(file[*i], parser_info);
			if (*check == 1)
			{
				return (ft_charpp_nfree(parser_info->name, 8),
					ft_charpp_nfree(parser_info->value, 8), 1);
			}
			else if (*check == 2)
				break ;
			*i += 1;
		}
	}
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
	if (check_loop(file, &i, &check, &parser_info))
		return (1);
	ft_charpp_free(parser_info.name);
	if (check_final_data(&parser_info) == 0)
		return (1);
	*j = i;
	info->textures_path = parser_info.value;
	return (0);
}
