/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:56:07 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/16 15:39:46 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **cmdlist, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!*cmdlist)
	{
		*cmdlist = new;
		return ;
	}
	tmp = ft_lstlast(*cmdlist);
	tmp->next = new;
}
