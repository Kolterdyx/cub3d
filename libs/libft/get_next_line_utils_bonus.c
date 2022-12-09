/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:27:21 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/20 18:32:41 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[gnl_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *raw_buff, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!raw_buff)
	{
		raw_buff = (char *)malloc(1 * sizeof(char));
		raw_buff[0] = '\0';
	}
	if (!raw_buff || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((gnl_strlen(raw_buff) + gnl_strlen(buff))
				+ 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (raw_buff)
		while (raw_buff[++i] != '\0')
			str[i] = raw_buff[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[gnl_strlen(raw_buff) + gnl_strlen(buff)] = '\0';
	free(raw_buff);
	return (str);
}

char	*get_line(char *raw_buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!raw_buff[i])
		return (NULL);
	while (raw_buff[i] && raw_buff[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (raw_buff[i] && raw_buff[i] != '\n')
	{
		str[i] = raw_buff[i];
		i++;
	}
	if (raw_buff[i] == '\n')
	{
		str[i] = raw_buff[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*adjust_buffer(char *buff)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (gnl_strlen(buff) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		str[j++] = buff[i++];
	str[j] = '\0';
	free(buff);
	return (str);
}
