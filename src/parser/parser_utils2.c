/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:51:48 by apena-ba          #+#    #+#             */
/*   Updated: 2023/03/13 19:51:54 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_names(t_parser *parser_info)
{
	parser_info->name[0] = ft_substr("NO", 0, 2);
	parser_info->name[1] = ft_substr("SO", 0, 2);
	parser_info->name[2] = ft_substr("EA", 0, 2);
	parser_info->name[3] = ft_substr("WE", 0, 2);
	parser_info->name[4] = ft_substr("DO", 0, 2);
	parser_info->name[5] = ft_substr("SP", 0, 2);
	parser_info->name[6] = ft_substr("F", 0, 1);
	parser_info->name[7] = ft_substr("C", 0, 1);
}

int	fill_id(t_parser *parser_info)
{
	int	i;

	i = 0;
	parser_info->name = ft_calloc(sizeof(char *), 9);
	parser_info->value = ft_calloc(sizeof(char *), 9);
	if (!parser_info->name || !parser_info->value)
		return (1);
	fill_names(parser_info);
	while (i < 8)
		parser_info->value[i++] = NULL;
	i = 0;
	while (parser_info->name[i])
		i++;
	if (i != 8)
		return (1);
	return (0);
}

static int	set_values(int *i, int *max, char *line)
{
	if (ft_strlen(line) == 2)
	{
		*i = 0;
		*max = 6;
	}
	else if (ft_strlen(line) == 1)
	{
		*i = 6;
		*max = 8;
	}
	else
		return (-1);
	return (0);
}

int	get_index_tocomp(char *line, char *value, t_parser *parser_info)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	if (set_values(&i, &max, line) == -1)
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
