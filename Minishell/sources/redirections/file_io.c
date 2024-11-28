/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:51:46 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:21:43 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Restores the original standard input and standard output
*	to their original fds of 0 and 1. Used to clear the input/output
*	fds after execution, in preparation for the next set of user commands.
*/
bool	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

/* 
*	Duplicates the input and output fds to the standard input and output.
*	Backs up the standard input and output before replacing them in order
*	to restore them after execution.
*/
bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_inp != -1)
		if (dup2(io->fd_inp, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->inputfl, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outputfl, strerror(errno), false);
	return (ret);
}

/* 
*	Checks if the inputfl and outputfl are set correctly.
*/
bool	check_inputfl_outputfl(t_io_fds *io)
{
	if (!io || (!io->inputfl && !io->outputfl))
		return (true);
	if ((io->inputfl && io->fd_inp == -1)
		|| (io->outputfl && io->fd_out == -1))
		return (false);
	return (true);
}
