/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:23:46 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:27:54 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Draws the floor and ceiling color */
static void	draw_ceiling_and_floor_color(t_data *data, int x, int start)
{
	int	t;

	t = 0;
	while (t < start)
	{
		data->pic->addr[(data->pic->width * t) + x] = data->c_color[0] << 16;
		data->pic->addr[(data->pic->width * t) + x] += data->c_color[1] << 8;
		data->pic->addr[(data->pic->width * t) + x] += data->c_color[2];
		t++;
	}
	while (t < data->height)
	{
		data->pic->addr[(data->pic->width * t) + x] = data->f_color[0] << 16;
		data->pic->addr[(data->pic->width * t) + x] += data->f_color[1] << 8;
		data->pic->addr[(data->pic->width * t) + x] += data->f_color[2];
		t++;
	}
}

/* Draws the walls and other world elements onto the screen based on
the results of ray casting. This determines the vertical slice of
the texture that should be displayed for each column
of pixels on the screen. */
static void	draw_walls(t_data *data, int x)
{
	int	line;
	int	start;
	int	end;

	if (data->wall < 0.05)
		return ;
	line = (int)(data->height / data->wall);
	start = data->height / 2 - line / 2;
	if (start < 0)
		start = 0;
	end = data->height / 2 + line / 2;
	if (end >= data->height)
		end = data->height - 1;
	draw_ceiling_and_floor_color(data, x, start);
	while (++start < end)
		data->pic->addr[(data->pic->width * start)
			+ x] = calculate_texture_color(data, start, line, data->south);
}

/* Uses ray casting algorithms to calculate where rays intersect with map
elements. This helps in determining how far walls are from the player,
which is essential for correct wall rendering and texture mapping. */
static void	calculate_ray_values(t_data *data)
{
	data->x_step = 1;
	data->y_step = 1;
	data->x_delta = fabs(1 / data->x_ray);
	data->y_delta = fabs(1 / data->y_ray);
	data->x_side = (data->x_map + 1.0 - data->x) * data->x_delta;
	data->y_side = (data->y_map + 1.0 - data->y) * data->y_delta;
	if (data->x_ray < 0)
	{
		data->x_step = -1;
		data->x_side = (data->x - data->x_map) * data->x_delta;
	}
	if (data->y_ray < 0)
	{
		data->y_step = -1;
		data->y_side = (data->y - data->y_map) * data->y_delta;
	}
	if (perform_dda(data))
	{
		if (!data->side)
			data->wall = (data->x_map - data->x + (1 - data->x_step) / 2)
				/ data->x_ray;
		else
			data->wall = (data->y_map - data->y + (1 - data->y_step) / 2)
				/ data->y_ray;
	}
}

static void	raycast_columns(t_data *data)
{
	int		y;
	float	x_camera;

	y = -1;
	while (++y < data->width)
	{
		data->x_map = (int)data->x;
		data->y_map = (int)data->y;
		x_camera = 2 * y / (float)data->width - 1;
		data->x_ray = data->x_dir - data->y_dir * x_camera;
		data->y_ray = data->y_dir + data->x_dir * x_camera;
		calculate_ray_values(data);
		draw_walls(data, y);
	}
}

/* The core rendering function that's invoked for every frame. It computes
ray casting for each screen column, draws the results, and then displays
the frame on the screen using MLX. Also handles some input events.*/
int	render_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->pic = create_image(data, data->width, data->width, 0);
	if (!data->pic)
		ft_error("Mlx init img failed", data);
	raycast_columns(data);
	if (data->pic->img)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->pic->img, 0, 0);
		mlx_destroy_image(data->mlx, data->pic->img);
	}
	free(data->pic);
	if (data->key)
		handle_key_press(data->key, data, data->x_dir);
	return (0);
}
