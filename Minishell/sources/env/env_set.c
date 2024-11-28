/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:51:06 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:52:40 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Reallocates memory for the global variable g_env_vars.
*	Returns a pointer to the new environment variables
*	or NULL in case of a memory allocation error.
*/
static char	**realloc_env_vars(t_tools *tools, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (tools->env[i] && i < size)
	{
		new_env[i] = ft_strdup(tools->env[i]);
		free_ptr(tools->env[i]);
		i++;
	}
	free(tools->env);
	return (new_env);
}

/*
*	Adds an environment variable with the given key
*	corresponding to the given value. If the key already
*	exists in the environment variables, the value will
*	be overwritten. If not, it creates a new entry.
*/
bool	set_env_var(t_tools *tools, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(tools->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && tools->env[idx])
	{
		free_ptr(tools->env[idx]);
		tools->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(tools->env);
		tools->env = realloc_env_vars(tools, idx + 1);
		if (!tools->env)
			return (false);
		tools->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

/*
*	Removes the variable at the given index from the
*	environment variables.
*/
bool	remove_env_var(t_tools *tools, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(tools->env))
		return (false);
	free_ptr(tools->env[idx]);
	i = idx;
	count = idx;
	while (tools->env[i + 1])
	{
		tools->env[i] = ft_strdup(tools->env[i + 1]);
		free_ptr(tools->env[i + 1]);
		count++;
		i++;
	}
	tools->env = realloc_env_vars(tools, count);
	if (!tools->env)
		return (false);
	return (true);
}
