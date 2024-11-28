/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:06:38 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/16 15:20:58 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Exits the minishell program by closing all opened
*	fds and freeing all allocated memory
*/
void	exit_minishell(t_tools *tools, int exno)
{
	if (tools)
	{
		if (tools->cmd && tools->cmd->io_fds)
			close_fds(tools->cmd, true);
		free_tools(tools, true);
	}
	exit(exno);
}
