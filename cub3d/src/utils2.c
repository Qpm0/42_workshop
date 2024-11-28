/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:55 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:22:46 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include <stdio.h>

/* checks the R G or B color value if it's between
 0-255 to ensure it's within the valid range
Check if all characters in the string are digits or whitespace 
Convert the integer back to a string
Check if conversion was successful
Check if the original string matches the converted string
Check if the number is within the valid range (0 to 255)*/
int	check_overflow(char *str, int num)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if (!str || !str[0])
		return (-1);
	while (str && str[++i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (-1);
	}
	tmp = ft_itoa(num);
	if (!tmp)
		return (-1);
	if (ft_strncmp(str, tmp, ft_strlen(str)) != 0)
	{
		ft_free_all(NULL, NULL, NULL, tmp);
		return (-1);
	}
	free(tmp);
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

/* finds first occurence of a char in a string, returns index of the found
character or -1 if not found*/
int	ft_strchr_idx(char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s || !s[0])
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s && s[i])
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c == 0)
		return (i);
	return (-1);
}

int	ft_spacecheck(char **map)
{
	size_t	i;
	size_t	j;

	j = -1;
	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == '0' &&
				((j > 0 && map[i][j - 1] == ' ') ||
					(j < ft_strlen(map[i]) - 1 && map[i][j + 1] == ' ') ||
					(i > 0 && map[i - 1][j] == ' ') ||
					(map[i + 1] != NULL && map[i + 1][j] == ' ')))
				return (ft_free_all(map, NULL, NULL, NULL), 1);
			else if (map[i][j] == '0' &&
						((j > 0 && map[i][j - 1] == '\t') ||
						(j < ft_strlen(map[i]) - 1 && map[i][j + 1] == '\t') ||
						(i > 0 && map[i - 1][j] == '\t') ||
						(map[i + 1] != NULL && map[i + 1][j] == '\t')))
				return (ft_free_all(map, NULL, NULL, NULL), 1);
		}
	}
	return (0);
}
