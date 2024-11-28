/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:21 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:26:30 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*Resets the game's state based on which key was released.*/
static int	key_reset(int key, t_data *data)
{
	data->key = 0;
	if (key == XK_Left)
		data->rotate[0] = 0;
	if (key == XK_Right)
		data->rotate[2] = 0;
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		data->move = 0;
		if (data->rotate[0])
			data->key = data->rotate[0];
		if (data->rotate[2])
			data->key = data->rotate[2];
	}
	else if (data->move)
		data->key = data->move;
	return (0);
}

/*Updates the game's state based on which key was pressed*/
static int	key_input(int key, t_data *data)
{
	if (key == XK_Escape)
		ft_exit(data);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		data->move = key;
	else if (key == XK_Left)
		data->rotate[0] = XK_Left;
	else if (key == XK_Right)
		data->rotate[2] = XK_Right;
	data->key = key;
	return (0);
}

/* Initializes everything mlx related about the game */
static int	init_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	mlx_get_screen_size(data->mlx, &data->width, &data->height);
	if (data->width == 0 || data->height == 0)
		return (0);
	get_position(data->map, data);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3D");
	if (!data->win)
		return (0);
	data->north = create_image(data, 0, 0, 'n');
	data->west = create_image(data, 0, 0, 'w');
	data->east = create_image(data, 0, 0, 'e');
	data->south = create_image(data, 0, 0, 's');
	if (!data->north || !data->east || !data->south || !data->west)
		return (0);
	mlx_hook(data->win, 2, 1L, &key_input, data);
	mlx_hook(data->win, 3, 2L, &key_reset, data);
	mlx_hook(data->win, 17, 0, ft_exit, data);
	mlx_loop_hook(data->mlx, &render_frame, data);
	mlx_loop(data->mlx);
	return (1);
}

// Initialize the structure for the RGB of
//the floor(f_color) and ceiling(c_color)
static void	init_colors(t_data *data)
{
	data->f_color[0] = -1;
	data->f_color[1] = -1;
	data->f_color[2] = -1;
	data->c_color[0] = -1;
	data->c_color[1] = -1;
	data->c_color[2] = -1;
}

//check daca are doar 1 arg / daca are mai putin de 4 litere
// verifica daca ultimele 4 caractere din arg daca sunt.cub
//set t_data struct values to 0
//deschide fisieru si salveazal in structura
//seteaza valorile default la structura
//Check the map
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || ft_strlen(argv[1]) < 4 || (ft_strncmp(argv[1]
				+ ft_strlen(argv[1]) - 4, ".cub", 4)))
	{
		ft_putendl_fd("Error\nUsage: ./cub3D maps/map1.cub", 2);
		exit(1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd == -1)
	{
		ft_putendl_fd("Error:File error", 2);
		exit(1);
	}
	init_colors(&data);
	if (check_cub_file(&data) != 0)
		ft_error("Parsing failed, map error", &data);
	if (init_game(&data) == 0)
		ft_error("Initialisation failed", &data);
	return (0);
}
