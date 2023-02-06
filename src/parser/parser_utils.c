/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:07:18 by apena-ba          #+#    #+#             */
/*   Updated: 2023/02/01 19:19:05 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	condition(char c)
{
	if (c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != '1' && c != '0'  && c != 'D'
		&& c != ' ' && c != 'C' && c != '2' && c != '\n')
		return (1);
	return (0);
}

void ft_parser_error(char *str){
	char *joined;

	joined = ft_strjoin("Error -> ", str);
	ft_putstr_fd(joined, 2);
	free(joined);
	exit(1);
}

char	*ft_strjoin_free(char *str1, const char *str2)
{
	char	*res;
	int		pos;
	int		pos2;

	if (!str1 || !str2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!res)
		return (NULL);
	pos = 0;
	while (str1[pos] != '\0')
	{
		res[pos] = str1[pos];
		pos++;
	}
	pos2 = 0;
	while (str2[pos2] != '\0')
		res[pos++] = str2[pos2++];
	res[pos] = '\0';
	free(str1);
	return (res);
}

void ft_print_data(int *map, t_vec dimensions){
    int i = 0, j, x = 0;

    ft_printf("dimensions.x = %d | dimensions.y = %d\n", dimensions.x, dimensions.y);
    while(i != dimensions.y){
        j = 0;
        while(j < dimensions.x){
            ft_printf("%d ", map[x++]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

int get_player_dir(char c, int *flag){
	*flag = 1;
	if(c == 'N')
		return(0);
	else if(c == 'E')
		return(1);
	else if(c == 'S')
		return(2);
	return(3);
}

void ft_charpp_printf(char **charpp){
	if(!charpp)
		return;
	for(int i = 0; charpp[i]; i++)
		ft_printf("charpp[%d] = |%s| and has %d characters\n", i, charpp[i], (int)ft_strlen(charpp[i]));
}

void set_char(char *str, int start, int end, char c){
	while(start < end)
		str[start++] = c;
}
