/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:42 by rpascu           #+#    #+#             */
/*   Updated: 2022/10/16 15:39:07 by rpascu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *c, int fd)
{
	write(fd, c, ft_strlen(c));
}
/* 
int	main(void)
{
ft_putstr_fd("a\0a", 1);
return (0);
}
*/