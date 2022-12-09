/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:54:26 by cigarcia          #+#    #+#             */
/*   Updated: 2022/11/28 19:07:51 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, void (*print)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		(*print)(lst->content);
		lst = lst->next;
	}
}
