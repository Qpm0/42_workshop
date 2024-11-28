/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:10:05 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/16 15:40:04 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **cmdlist, t_list *new)
{
	if (!new)
		return ;
	if (!*cmdlist)
	{
		*cmdlist = new;
		return ;
	}
	new->next = *cmdlist;
	*cmdlist = new;
}
