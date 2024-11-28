/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:46:58 by rpascu           #+#    #+#             */
/*   Updated: 2022/10/24 21:41:45 by rpascu          ###   ########.fr       */
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
