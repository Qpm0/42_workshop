/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:22:10 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:19:29 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Sets the initial direction and view plane for the player based on
the player's position character in the game state `t_data *data`. */
void	set_initial_direction(t_data *data)
{
	data->x_dir = 0;
	data->y_dir = -1;
	if (data->p_direction == 'W')
	{
		data->x_dir = -1;
		data->y_dir = 0;
	}
	else if (data->p_direction == 'E')
	{
		data->x_dir = 1;
		data->y_dir = 0;
	}
	else if (data->p_direction == 'S')
	{
		data->x_dir = 0;
		data->y_dir = 1;
	}
}

/* Determines the starting position of the player on the map using the position
character stored in the game state `t_data *data`.
It then initializes the player's
x and y coordinates in the game state. */
void	get_position(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != data->p_direction)
			j++;
		if (map[i][j] && map[i][j] == data->p_direction)
		{
			data->x = (j + 0.5);
			data->y = (i + 0.5);
		}
		i++;
	}
	set_initial_direction(data);
}

/* Modifies the player's position in the game state `t_data *data` based on the
proposed movements in the x and y directions (`newX` and `newy`). */
static void	move_player(t_data *data, float newy, float newX)
{
	if ((int)newy >= 0 && data->map[(int)(newy)])
	{
		if (data->y > 1.5)
			data->y = newy;
		else
			data->y = newy + 0.01;
		if ((int)newX >= 0 && data->map[(int)newy][(int)(newX)]
			&& data->map[(int)newy][(int)(newX)] != ' '
			&& data->map[(int)newy][(int)(newX)] != '1')
			data->x = newX;
	}
}

/* Handles player movement and rotation based on the key pressed. Updates
the player's position and direction in the game state `t_data *data`. */
void	handle_key_press(int key, t_data *data, float temp)
{
	if ((data->move == XK_w || key == XK_w) && data->y)
		move_player(data, data->y + data->y_dir * SPEED, data->x + data->x_dir
			* SPEED);
	else if (data->move && (key == XK_s))
		move_player(data, data->y - data->y_dir * SPEED / 2, data->x
			- data->x_dir * SPEED / 2);
	else if (key == XK_a)
		move_player(data, data->y - data->x_dir * SPEED / 2, data->x
			+ data->y_dir * SPEED / 2);
	else if (key == XK_d)
		move_player(data, data->y + data->x_dir * SPEED / 2, data->x
			- data->y_dir * SPEED / 2);
	if (data->rotate[2] == XK_Right && (key == XK_Right))
	{
		data->x_dir = data->x_dir * cos(LR_ANGLE) - data->y_dir * sin(LR_ANGLE);
		data->y_dir = temp * sin(LR_ANGLE) + data->y_dir * cos(LR_ANGLE);
	}
	else if (data->rotate[0] == XK_Left && (key == XK_Left))
	{
		data->x_dir = data->x_dir * cos(-LR_ANGLE) - data->y_dir
			* sin(-LR_ANGLE);
		data->y_dir = temp * sin(-LR_ANGLE) + data->y_dir * cos(-LR_ANGLE);
	}
}
