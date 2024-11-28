/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:46:45 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:40:32 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Checks access and permissions for each possible command path to find
*	a valid path to binay files for a command.
*/
static char	*find_valid_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL, "an unexpected error occured",
				EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

/*
*	Extracts paths from the PATH environment variable.
*/
static char	**get_paths_from_env(t_tools *tools)
{
	char	**env_paths;

	if (get_env_var_index(tools->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_value(tools->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

/*
*	Searches the PATH environment variable for the location of the given
*	command's binary file.
*/
char	*get_cmd_path(t_tools *tools, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(tools);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_str_array(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_path(cmd, env_paths);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_str_array(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
