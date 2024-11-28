/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 09:37:30 by rpascu           #+#    #+#             */
/*   Updated: 2023/01/28 09:37:30 by rpascu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	render2(t_main *main, int y)
{
	int	x;

	x = -1;
	while (++x < main->map->x)
	{
		if (main->map->map[y][x] == '1')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->wall, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == '0' || main->map->map[y][x] == 'P')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->way, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'E')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->exitd, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'C')
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->coin, x * PIXEL, y * PIXEL);
		else if (main->map->map[y][x] == 'X' && (main->p_x + main->p_y) % 3)
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->enemy, x * PIXEL, y * PIXEL);
		else
			mlx_put_image_to_window(main->mlx, main->win,
				main->img->way, x * PIXEL, y * PIXEL);
	}
}

int	render(t_main *main)
{
	int	y;

	y = 0;
	while (y < main->map->y)
	{
		render2(main, y);
		y++;
	}
	mlx_put_image_to_window(main->mlx, main->win, main->img->pl,
		(main->p_x) * PIXEL, (main->p_y) * PIXEL);
	if (main->coincount == 0
		&& main->map->map[main->p_y][main->p_x] == 'E')
		ft_destroy(main);
	else
		write_move_count(main);
	return (0);
}
