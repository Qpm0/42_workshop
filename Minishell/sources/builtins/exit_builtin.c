/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:32:33 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:50:16 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Executes the exit builtin.
*	In case of failure due to invalid arguments, does not exit the shell
*	and returns an error exit code (1 or 2) instead.
*/
int	exit_builtin(t_tools *tools)
{
	int		exit_code;

	exit_code = g_exit_code;
	exit_minishell(tools, exit_code);
	return (2);
}
