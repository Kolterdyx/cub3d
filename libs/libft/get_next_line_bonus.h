/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:23:11 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/08 19:04:01 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*read_more(int fd, char *raw_buff);
char	*get_line(char *raw_buff);
char	*adjust_buffer(char *raw_buff);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *raw_buff, char *buff);
size_t	gnl_strlen(char *s);

#endif