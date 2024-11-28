/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 09:34:51 by rpascu           #+#    #+#             */
/*   Updated: 2023/01/28 09:34:51 by rpascu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	write_move_count(t_main *main)
{
	char	*str;
	char	*str2;
	char	*desc;
	int		c;

	c = 0x00FFFFFF;
	mlx_string_put(main->mlx, main->win, PIXEL * 2, PIXEL / 2, c, "M O V E :");
	if (main->movecount == 0)
		mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, c, "0");
	str = ft_itoa(main->movecount);
	mlx_string_put(main->mlx, main->win, PIXEL * 3, PIXEL / 2, c, str);
	mlx_string_put(main->mlx, main->win, (PIXEL * 4), PIXEL / 2, c, "C O I N:");
	str2 = ft_itoa(main->coincount);
	mlx_string_put(main->mlx, main->win, PIXEL * 5, PIXEL / 2, c, str2);
	desc = "P R E S S   E S C   O R   C L I C K   ( X )   T O   E X I T";
	mlx_string_put(main->mlx, main->win, PIXEL * 8, PIXEL / 2, c, desc);
	free(str);
	free(str2);
}

static int	draw_map2(t_main *main, int y, int x)
{
	if (main->map->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win,
			main->img->wall, x, y);
	else if (main->map->map[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win,
			main->img->way, x, y);
	else if (main->map->map[y][x] == 'P')
	{
		mlx_put_image_to_window(main->mlx, main->win, main->img->pl, x, y);
		main->p_y = y;
		main->p_x = x;
	}
	else if (main->map->map[y][x] == 'E')
		mlx_put_image_to_window(main->mlx, main->win, main->img->exitd, x, y);
	else if (main->map->map[y][x] == 'C')
		mlx_put_image_to_window(main->mlx, main->win, main->img->coin, x, y);
	else if (main->map->map[y][x] == 'X')
		mlx_put_image_to_window(main->mlx, main->win, main->img->enemy, x, y);
	else if (main->map->map[y][x] != '\n')
		ft_error("Error\nWrong character in Map file", main);
	x++;
	return (x);
}

void	draw_map(t_main *main)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < (main->map->y))
	{
		while (x < (main->map->x))
			x = draw_map2(main, y, x);
		y++;
		x = 0;
	}
}
