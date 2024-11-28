/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:21:27 by cmoreanu          #+#    #+#             */
/*   Updated: 2024/02/23 15:04:11 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*function to handle character position check and whitespace skipping*/
// Skip leading newline characters, spaces, and tabs
// Process map characters until a double newline---
//--- or newline followed by a tab is encountered
// Exit the loop if a double newline or newline followed by a tab is encountered
// Check for invalid characters (characters other than '0', '1', space, newline)
// Update player direction if a valid direction character is found
// Check the count of player direction characters and their validity
// Skip trailing newline characters, spaces, and tabs
// Return the updated index after processing map characters
int	read_map_chars(char *m, int i, char *p_direction, int count)
{
	while (m && m[i] && (m[i] == '\n' || m[i] == ' ' || m[i] == '\t'))
		i++;
	while (m && i >= 0 && m[i])
	{
		if (m && m[i + 1] && m[i] == '\n' && (m[i + 1] == '\n' || m[i
					+ 1] == '\t'))
			break ;
		if ((m && m[i] != '0' && m[i] != '1' && m[i] != ' ' && m[i] != '\n'))
		{
			*p_direction = m[i];
			count++;
		}
		i++;
	}
	if (count != 1 || (*p_direction != 'N' && *p_direction != 'S'
			&& *p_direction != 'W' && *p_direction != 'E'))
		return (-1);
	while (m && m[i] && (m[i] == '\n' || m[i] == ' ' || m[i] == '\t'))
		i++;
	return (i);
}

// Check if temporary map data exists
// Process map characters, updating player position and counting elements
// Check if an error occurred during map character processing
// Check if there are remaining lines in the temporary map data
// Split the temporary map data into individual lines
// Check if the map splitting was successful
// Check the walls of the map
int	validate_map(t_data *data, char *pos, int i, int count)
{
	char	**tmp;

	if (!data->tmp_map)
		return (-1);
	i = read_map_chars(data->tmp_map, i, pos, count);
	if (i == -1 && data->tmp_map)
		return (-1);
	if (data->tmp_map && data->tmp_map[i])
		return (-1);
	tmp = ft_split(data->tmp_map, '\n');
	if (ft_spacecheck(tmp))
		return (-1);
	if (!tmp && data->tmp_map)
		return (-1);
	return (check_walls(tmp));
}

// cauta tot dupa prefix si copiaza
// Find the index of the first newline character -
//-in the substring of s starting from i
// Check conditions for an invalid substring
// Update the position k based on the index of the newline character
// Allocate memory for a substring of length ind + 1
// Check if memory allocation was successful
// Return the allocated memory for further processing
char	*prefix_string(char *s, int *i, int *k)
{
	int		ind;
	char	*tmp;

	ind = ft_strchr_idx(&s[*i], '\n');
	if (ind == -1 || ind == 0 || s[*i] == '\n')
		return (NULL);
	*k += ind;
	tmp = malloc(ind + 1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

// Iterate through characters in the string
// Check for comma or newline to terminate the current substring
// dupa ii dai convert cu check overflow  care primeste- 
//- si forma de string si de  nr/ merge alt nume
// Convert substring to integer and handle overflow
// Clear the temporary substring
// Check conditions based on the current index and character
int	extract_colors_from_string(char *s, int rgb[3], char *tmp, int *i)
{
	int	j;
	int	ind;

	j = 0;
	ind = 0;
	while (s[*i])
	{
		if (s[*i] == ',' || s[*i] == '\n')
		{
			tmp[j] = '\0';
			rgb[ind] = check_overflow(tmp, atoi(tmp));
			ft_memset(tmp, 0, ft_strlen(tmp));
			if (ind == 2 && s[*i] == '\n' && rgb[ind] != -1)
				return (0);
			else if (rgb[ind] == -1 || (ind == 2 && s[*i] != '\n'))
				return (1);
			ind++;
			j = 0;
		}
		else if (s[*i] != ' ' && s[*i] != '\t')
			tmp[j++] = s[*i];
		(*i)++;
	}
	return (0);
}

//Get the colors after the prefix
int	get_color(char *s, int rgb[3], int *k)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = prefix_string(s, &i, k);
	if (!tmp)
		return (1);
	if (extract_colors_from_string(s, rgb, tmp, &i))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
