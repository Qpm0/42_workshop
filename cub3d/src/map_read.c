/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:22:15 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:14:28 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	pre_check(char *s)
{
	if (!ft_strnstr(s, "NO ", ft_strlen(s)) || !ft_strnstr(s, "SO ",
			ft_strlen(s)) || !ft_strnstr(s, "WE ", ft_strlen(s))
		|| !ft_strnstr(s, "EA ", ft_strlen(s)) || !ft_strnstr(s, "C ",
			ft_strlen(s)) || !ft_strnstr(s, "F ", ft_strlen(s)) || !ft_strchr(s,
			'1') || !ft_strchr(s, '0'))
		return (0);
	return (1);
}

//getnextline
char	*read_cub_file(int fd)
{
	char	*map;
	char	*buffer;
	char	*tmp;
	int		bytes;

	map = ft_calloc(1, 1);
	if (!map)
		return (0);
	buffer = ft_calloc(1, 101);
	if (!buffer)
		return (free(map), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 100);
		if (bytes == -1)
			return (free(map), free(buffer), NULL);
		buffer[bytes] = '\0';
		tmp = map;
		map = ft_strjoin(map, buffer);
		if (!map)
			return (free(tmp), free(buffer), NULL);
		free(tmp);
	}
	return (free(buffer), map);
}

/* Check everything about the map(Chars, borders, etc.)*/
int	check_cub_file(t_data *data)
{
	char	*map_content;

	if (data->fd == -1)
	{
		data->error_code = ERR_FILE_NOT_FOUND;
		return (-1);
	}
	map_content = read_cub_file(data->fd);
	if (!map_content)
	{
		data->error_code = ERR_FILE_READ;
		close(data->fd);
		return (-1);
	}
	if (split_map(map_content, data) || check_textures(data))
	{
		close(data->fd);
		free(map_content);
		return (-1);
	}
	if (data->fd != -1)
		close(data->fd);
	free(map_content);
	return (0);
}
