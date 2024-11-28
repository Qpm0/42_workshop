/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:34 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:12:00 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Extracts the texture file path*/
static char	*get_texture(char *s, t_data *data, int *pos)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = ft_strchr_idx(&s[i], '\n');
	while (s[i] && i < k && s[i] != '\n' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (k == -1 || k == 0 || s[i] == '\n')
		return (NULL);
	*pos += k;
	k--;
	while (s[k] && s[k] != '\n' && (s[k] == ' ' || s[k] == '\t'))
		k--;
	tmp = ft_substr(s, i, k - i + 1);
	if (!tmp || ft_strlen(tmp) < 4 || (ft_strncmp(tmp + ft_strlen(tmp) - 4,
				".xpm", 4)))
	{
		data->error_code = ERR_INVALID_TEXTURE;
		if (tmp)
			free(tmp);
		return (NULL);
	}
	else
		return (tmp);
}

//verifica daca nu se gasesc diferente la indexul -
//-ala si daca nu e duplicat ii luam textura
//copiaza tot dupa Prefixul texturii (NO, SO etc)
//Checks if the color (data->f_color) has not -
//-been assigned (data->f_color[0] != -1)
//or attempts to get the color from the string using -
//- get_color (if not assigned). daca nu a mers da eroare
// salveata valorile rgb in structura
int	assign_textures(char *s, t_data *data, int *i)
{
	while (s[*i] != 0)
	{
		if (!ft_strncmp(&s[*i], "NO ", 3) && !is_duplicate(data,
				&data->no_path))
			data->no_path = get_texture(&s[*i + 3], data, i);
		else if (!ft_strncmp(&s[*i], "SO ", 3) && !is_duplicate(data,
				&data->so_path))
			data->so_path = get_texture(&s[*i + 3], data, i);
		else if (!ft_strncmp(&s[*i], "WE ", 3) && !is_duplicate(data,
				&data->we_path))
			data->we_path = get_texture(&s[*i + 3], data, i);
		else if (!ft_strncmp(&s[*i], "EA ", 3) && !is_duplicate(data,
				&data->ea_path))
			data->ea_path = get_texture(&s[*i + 3], data, i);
		else if (!ft_strncmp(&s[*i], "F ", 2) && (data->f_color[0] != -1
				|| get_color(&s[*i + 2], data->f_color, i)))
			data->error_code = ERR_INVALID_COLOR;
		else if (!ft_strncmp(&s[*i], "C ", 2) && (data->c_color[0] != -1
				|| get_color(&s[*i + 2], data->c_color, i)))
			data->error_code = ERR_INVALID_COLOR;
		if (data->error_code)
			return (1);
		(*i)++;
	}
	return (0);
}

//verifica ca texturile si culorile s-au salvat bine
int	verify_color_path(char *s, t_data *data, int *i)
{
	*i = 0;
	while (s[*i] && ft_strnstr(&s[*i], "NO ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], data->no_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "SO ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], data->so_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "WE ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], data->we_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "EA ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], data->ea_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "F ", ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "C ", ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && s[*i] != '\n')
		(*i)++;
	return (0);
}

// Extract the remaining part of the string -
//-(map data) from index *i until the end
// Check if the substring extraction was successful
// Check the validity of the map and update the player direction
// Free the memory occupied by the temporary map data
// Split the map data into individual lines using -
//-newline character as a delimiter
// Check if the map splitting was successful
int	prepare_map(char *s, t_data *data, int *i)
{
	data->tmp_map = ft_substr(s, *i, ft_strlen(&s[*i]));
	if (!data->tmp_map)
		return (1);
	if (validate_map(data, &data->p_direction, 0, 0))
	{
		data->error_code = ERR_INVALID_MAP;
		if (data->tmp_map)
			free(data->tmp_map);
		return (1);
	}
	if (data->tmp_map)
		free(data->tmp_map);
	data->map = ft_split(&s[*i], '\n');
	if (!data->map)
		return (1);
	return (0);
}

/* Sets everything found in the map in the game's structure*/
//verifica toate caractere din fisier sa vezi daca ai ce-ti trebuie
//salveaza texturile si culorile in structura
//daca nu a fcuntionat aslvare de texturi si culori da eroare
//CHeck if the colors are saved and move on to the next part of the map
//check pathing and player position and save everything in the struct
int	split_map(char *s, t_data *data)
{
	int	i;

	i = 0;
	if (!pre_check(s))
		return (1);
	if (assign_textures(s, data, &i))
		return (1);
	if (!data->ea_path || !data->we_path || !data->so_path || !data->no_path
		|| data->f_color[0] == -1 || data->c_color[0] == -1
		|| data->f_color[1] == -1 || data->c_color[1] == -1
		|| data->f_color[2] == -1 || data->c_color[2] == -1)
		return (1);
	if (verify_color_path(s, data, &i))
		return (1);
	return (prepare_map(s, data, &i));
}
