/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:30:41 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:50:57 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Separates the given argument into a key-value pair
*	for the environment variable.
*	Returns an array of 2 strings containing the key and the
*	value of the new environment variable.
*/
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

/* 
*	Adds the given variables to the environment variables.
*/
int	export_builtin(t_tools *tools, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(tools, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", "invalid parameter name", args[i], false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(tools, tmp[0], tmp[1]);
			free_str_array(tmp);
		}
		i++;
	}
	return (ret);
}
