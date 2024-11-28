/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:55:54 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/20 14:38:37 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Executes the builtin env command: Prints the environment variables.
*/
int	env_builtin(t_tools *tools, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!tools->env)
		return (EXIT_FAILURE);
	while (tools->env[i])
		ft_putendl_fd(tools->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
