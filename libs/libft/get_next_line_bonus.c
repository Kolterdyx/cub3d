/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:27:00 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/08 19:10:17 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_more(int fd, char *raw_buff)
{
	char	*buff;
	int		chars_seen;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	chars_seen = 1;
	while (!gnl_strchr(raw_buff, '\n') && chars_seen != 0)
	{
		chars_seen = read(fd, buff, BUFFER_SIZE);
		if (chars_seen == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[chars_seen] = '\0';
		raw_buff = gnl_strjoin(raw_buff, buff);
	}
	free(buff);
	return (raw_buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw_buff[256];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	raw_buff[fd] = read_more(fd, raw_buff[fd]);
	if (!raw_buff[fd])
		return (NULL);
	line = get_line(raw_buff[fd]);
	raw_buff[fd] = adjust_buffer(raw_buff[fd]);
	return (line);
}
