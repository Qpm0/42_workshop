/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:22:06 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:20:12 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Determines the texture color for a specific position on the screen.
The texture and shading are selected based on the ray's direction
and intersection point. It also accounts for the direction from which
the ray hits a wall to pick the correct texture side. */
int	calculate_texture_color(t_data *data, float start, int line, t_img *texture)
{
	int		color;
	float	x_text;
	float	x_wall;
	float	y_text;

	if (data->x_ray > 0 && !data->side)
		texture = data->east;
	else if (data->x_ray < 0 && !data->side)
		texture = data->west;
	else if (data->y_ray < 0 && data->side)
		texture = data->north;
	if (data->side == 0)
		x_wall = data->y + data->wall * data->y_ray;
	else
		x_wall = data->x + data->wall * data->x_ray;
	x_wall -= floor(x_wall);
	x_text = (int)(x_wall * (float)(texture->width));
	if ((data->side == 0 && data->x_ray < 0) || (data->side == 1
			&& data->y_ray > 0))
		x_text = texture->width - x_text - 1;
	color = ((int)start << 8) - (data->height << 7) + (line << 7);
	y_text = ((color * texture->height) / line) >> 8;
	color = texture->addr[(int)(y_text * texture->width + x_text)];
	return (color);
}

/* Uses the MLX library to load an image from a file. This function
is essential for loading different textures used in the game world.
It will return a pointer to the loaded image or fail if there are issues. */
static void	*load_image(t_data *data, char *path, int *width, int *height)
{
	void	*img;

	img = 0;
	if (!data || !data->mlx || !path || !width || !height)
		return (0);
	if (data && data->mlx && path && width && height)
		img = mlx_xpm_file_to_image(data->mlx, path, width, height);
	if (!img || *height > 1400 || *width > 1400)
	{
		if (img)
			mlx_destroy_image(data->mlx, img);
		return (NULL);
	}
	return (img);
}

/* Allocates and initializes a new image structure, assigning the correct
texture based on the provided value 'x' which determines the type of texture
(north, west, east, south, etc.).
It uses the `load_image` function to assist.*/
static t_img	*initialize_new_image(t_data *data, int width, int height,
		int x)
{
	t_img	*new;

	if (!data)
		return (0);
	new = ft_calloc(1, sizeof(t_img));
	if (!new)
		ft_error("Malloc failed", data);
	new->width = width;
	new->height = height;
	if (x == 'n')
		new->img = load_image(data, data->no_path, &new->width, &new->height);
	else if (x == 'w')
		new->img = load_image(data, data->we_path, &new->width, &new->height);
	else if (x == 'e')
		new->img = load_image(data, data->ea_path, &new->width, &new->height);
	else if (x == 's')
		new->img = load_image(data, data->so_path, &new->width, &new->height);
	else if (data->mlx)
		new->img = mlx_new_image(data->mlx, width, height);
	if (!new->img)
	{
		free(new);
		ft_error("Mlx failed", data);
	}
	return (new);
}

/* Creates a new image structure intended for rendering. It initializes
the structure, loads the appropriate texture, and also retrieves
the data address where pixel information will be written. */
t_img	*create_image(t_data *data, int width, int height, int x)
{
	t_img	*new;
	int		bpp;
	int		endian;

	if (!data)
		return (0);
	new = initialize_new_image(data, width, height, x);
	if (!new || !new->img)
		ft_error("Mlx init img failed", data);
	new->addr = (int *)mlx_get_data_addr(new->img, &bpp, &x, &endian);
	if (!new->addr)
		ft_error("Mlx failed", data);
	return (new);
}

/* Implements the Digital Differential Analyzer (DDA) algorithm for raycasting,
tracing the path of a ray until it hits a wall or goes out of bounds.
Returns 1 if a wall is hit, 0 otherwise. */
int	perform_dda(t_data *data)
{
	while (1)
	{
		if (data->x_side < data->y_side)
		{
			data->x_side += data->x_delta;
			data->x_map += data->x_step;
			data->side = 0;
		}
		else
		{
			data->y_side += data->y_delta;
			data->y_map += data->y_step;
			data->side = 1;
		}
		if (data->y_map < 0)
			data->y_map = 0;
		if (data->x_map < 0)
			data->x_map = 0;
		if (!data->map[data->y_map] || !data->map[data->y_map][data->x_map]
			|| data->map[data->y_map][data->x_map] == ' ')
			return (data->wall = -1, 0);
		if (data->map[data->y_map][data->x_map] == '1')
			return (1);
	}
	return (0);
}
