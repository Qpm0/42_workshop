/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:45 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:26:13 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

# define LR_ANGLE 0.04
# define SPEED 0.04

# define ERR_FILE_NOT_FOUND 0
# define ERR_FILE_READ 1
# define ERR_INVALID_TEXTURE 2
# define ERR_MULTIPLE_TEXTURE 3
# define ERR_INVALID_MAP 4
# define ERR_INVALID_COLOR 5

typedef struct s_pic
{
	int		width;
	int		height;
	void	*img;
	int		*addr;
}			t_img;

typedef struct s_data
{
	int		error_code;
	void	*mlx;
	void	*win;
	char	*tmp_map;
	char	**map;
	int		fd;
	int		width;
	int		height;
	int		side;
	float	wall;
	float	x;
	int		x_map;
	int		x_step;
	float	x_ray;
	float	x_dir;
	float	x_delta;
	float	x_side;
	float	y;
	int		y_map;
	int		y_step;
	float	y_ray;
	float	y_dir;
	float	y_delta;
	float	y_side;
	char	p_direction;
	int		key;
	int		move;
	int		rotate[3];
	int		f_color[3];
	int		c_color[3];
	t_img	*pic;
	t_img	*north;
	t_img	*east;
	t_img	*west;
	t_img	*south;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}			t_data;

int			split_map(char *s, t_data *data);
char		*read_cub_file(int fd);
int			validate_map(t_data *data, char *p_direction, int i, int count);
int			check_textures(t_data *data);
int			is_duplicate(t_data *data, char **path);
int			check_cub_file(t_data *data);
void		get_position(char **map, t_data *cub);
int			ft_spacecheck(char **map);
int			ft_spacecheck2(char **map);
int			perform_dda(t_data *cub);
t_img		*create_image(t_data *cub, int width, int height, int x);
int			render_frame(void *param);
int			ft_exit(t_data *cub);
void		ft_free_all(char **s, char *s1, char *s2, char *s3);
void		ft_error(char *errorcode, t_data *data);
int			ft_strchr_idx(char *s, int c);
int			ft_isspace(int c);
int			check_overflow(char *str, int num);
int			get_color(char *s, int rgb[3], int *k);
int			pre_check(char *s);
void		flood_fill(char **mapcopy, int i, int j, int *exit);
int			check_walls(char **map);
int			calculate_texture_color(t_data *data, float start,
				int line, t_img *texture);
void		handle_key_press(int key, t_data *data, float temp);

#endif
