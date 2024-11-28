/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:39 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 14:56:12 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	flood_fill(char **mapcopy, int i, int j, int *err)
{
	if (i < 0 || j < 0 || !mapcopy[i] || (j >= (int)ft_strlen(mapcopy[i]))
		|| (mapcopy[i][j] && mapcopy[i][j] == ' '))
	{
		*err = 1;
		return ;
	}
	else if (mapcopy[i][j] != '0')
	{
		return ;
	}
	mapcopy[i][j] = 'O';
	flood_fill(mapcopy, i - 1, j, err);
	flood_fill(mapcopy, i + 1, j, err);
	flood_fill(mapcopy, i, j - 1, err);
	flood_fill(mapcopy, i, j + 1, err);
}

//search for the player pos and the flood fill the map
// Iterate through each row of the map
// Iterate through each character in the current row
// Check if the character is not '0', '1', space, or tab
// Set player character to '0'
// Perform flood-fill algorithm to mark connected non-wall areas
// Check if an error occurred during --
//--flood-fill (indicating an isolated non-wall area)
// Free allocated memory for the map
// Return 0 to indicate a valid route
int	check_walls(char **map)
{
	size_t	i;
	size_t	j;
	int		err;

	i = -1;
	err = 0;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != '\t')
			{
				map[i][j] = '0';
				flood_fill(map, i, j, &err);
				if (err == 1)
				{
					return (ft_free_all(map, NULL, NULL, NULL), -1);
				}
			}
		}
	}
	ft_free_all(map, NULL, NULL, NULL);
	return (0);
}

// Checks if a single texture file exists and can be read.
static int	check_texture(char *path, t_data *data)
{
	int		fd;
	char	c;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		data->error_code = ERR_FILE_NOT_FOUND;
		return (-1);
	}
	else if (read(fd, &c, 1) == -1)
	{
		data->error_code = ERR_FILE_READ;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	is_duplicate(t_data *data, char **path)
{
	if (path && *path)
	{
		free(*path);
		*path = NULL;
		data->error_code = ERR_MULTIPLE_TEXTURE;
		return (1);
	}
	return (0);
}

/* Validates each texture path (north, south, west, and east) by checking
if the corresponding files exist and can be read. */
int	check_textures(t_data *data)
{
	if (check_texture(data->no_path, data) == -1)
		return (-1);
	if (check_texture(data->so_path, data) == -1)
		return (-1);
	if (check_texture(data->we_path, data) == -1)
		return (-1);
	if (check_texture(data->ea_path, data) == -1)
		return (-1);
	return (0);
}
