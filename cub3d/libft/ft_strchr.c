/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:27:11 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/21 13:27:12 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != (char)c && *ptr != '\0')
		ptr++;
	if (*ptr == (char)c)
		return ((char *)ptr);
	if (!c && *ptr == '\0')
		return ((char *)ptr);
	return (NULL);
}
