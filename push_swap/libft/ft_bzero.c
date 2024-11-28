/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:41 by rpascu           #+#    #+#             */
/*   Updated: 2022/10/13 16:24:24 by rpascu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int	main(void)
{
	char	*test;

	test = malloc(256);
	test[0] = 'a';
	printf("String after is - |%s|\n", test);	
	ft_bzero(test, 256);
	printf("String after is - |%s|\n", test);
	return (0);
}
*/
