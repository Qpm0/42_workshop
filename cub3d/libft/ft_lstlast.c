/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:25:53 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/21 13:25:53 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*mylist;

	if (!lst)
		return (lst);
	mylist = lst;
	while (mylist != NULL)
	{
		if (mylist->next == NULL)
			return (mylist);
		mylist = mylist->next;
	}
	return (0);
}
