/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:27:14 by apena-ba          #+#    #+#             */
/*   Updated: 2023/03/01 18:13:52 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_charpp_cpy(char **to_copy)
{
	int i;
	char **ret;

	if (!to_copy || !*to_copy)
	{
		return (NULL);
	}
	i = 0;
    ret = ft_calloc(sizeof(char *), ft_charpp_len(to_copy) + 1);
    if (!ret)
	{
		return (NULL);
	}
	while (to_copy[i]){
        ret[i] = ft_substr(to_copy[i], 0, ft_strlen(to_copy[i]));
        if(!ret[i])
            return(ft_charpp_free(ret));
        i++;
    }
    return(ret);
}
