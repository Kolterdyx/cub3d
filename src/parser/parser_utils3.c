/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:59:28 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/28 22:38:05 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**fill_items(char *to_comp, char **splited)
{
	char	**colors;

	if (ft_charpp_len(splited) != 2)
		return (ft_charpp_free(splited), NULL);
	else if (ft_strlen(splited[0]) != ft_strlen(to_comp))
		return (ft_charpp_free(splited), NULL);
	else if (ft_strncmp(splited[0], to_comp, ft_strlen(to_comp)))
		return (ft_charpp_free(splited), NULL);
	colors = ft_split(splited[1], ',');
	if (ft_charpp_len(colors) != 3)
		return (ft_charpp_free(splited), ft_charpp_free(colors), NULL);
	return (colors);
}

int	color_check(char *line, char *to_comp)
{
	char	**splited;
	char	**clr;
	char	*trimed;
	int		i;

	splited = ft_split(line, ' ');
	clr = fill_items(to_comp, splited);
	if (!clr)
		return (1);
	i = -1;
	while (++i < 2)
	{
		if (ft_isdigit_str(clr[i]) == 0)
			return (ft_charpp_free(splited), ft_charpp_free(clr), 1);
		else if (ft_atoi(clr[i]) < 0 || ft_atoi(clr[i]) > 255)
			return (ft_charpp_free(splited), ft_charpp_free(clr), 1);
	}
	trimed = ft_strtrim(clr[2], "\n");
	if (ft_isdigit_str(trimed) == 0)
		return (free(trimed), ft_charpp_free(splited), ft_charpp_free(clr), 1);
	else if (ft_atoi(trimed) < 0 || ft_atoi(trimed) > 255)
		return (free(trimed), ft_charpp_free(splited), ft_charpp_free(clr),
			ft_parser_error("number in colors must be between 0 and 255\n"), 1);
	return (ft_charpp_free(splited), ft_charpp_free(clr), free(trimed), 0);
}

int	skip_nl(char **file)
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

size_t	get_max_len(char **file)
{
	int		i;
	size_t	max_len;

	max_len = 0;
	i = 0;
	while (ft_strlen(file[i]) > 0 && ft_isspace_str(file[i]) == 0)
	{
		if (ft_strlen(file[i]) > max_len)
			max_len = ft_strlen(file[i]);
		i++;
	}
	return (max_len);
}

char	**create_map(char **file)
{
	char	**ret;
	int		i;
	size_t	max_len;

	max_len = 0;
	if (!file || !*file)
		return (NULL);
	max_len = get_max_len(file);
	ret = ft_calloc(sizeof(char *), ft_charpp_len(file) + 1);
	i = -1;
	while (file[++i])
	{
		ret[i] = ft_calloc(sizeof(char), max_len + 1);
		ft_memcpy(ret[i], file[i], ft_strlen(file[i]));
		if (max_len >= ft_strlen(file[i]) && ft_strlen(file[i]) > 0
			&& file[i][ft_strlen(file[i]) - 1] == '\n')
			set_char(ret[i], ft_strlen(file[i]) - 1, max_len, ' ');
		else if (max_len >= ft_strlen(file[i]) && ft_strlen(file[i]) > 0)
			set_char(ret[i], ft_strlen(file[i]), max_len, ' ');
	}
	return (ret);
}
