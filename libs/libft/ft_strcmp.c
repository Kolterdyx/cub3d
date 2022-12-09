/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efournou <efournou@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:04:10 by efournou          #+#    #+#             */
/*   Updated: 2022/02/23 22:28:17 by efournou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include <stdio.h>*/
int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	counter;

	counter = 0;
	while (s1[counter] != '\0' || s2[counter] != '\0')
	{
		if (s1[counter] != s2[counter])
			return (s1[counter] - s2[counter]);
		counter++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[]="ABC";
	char	str2[]="ABF";

	printf("%d\n", ft_strcmp(str1, str2)); 
}*/
