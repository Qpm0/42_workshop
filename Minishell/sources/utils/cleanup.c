/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:05:55 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:23:10 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Frees all of the tools used to run a command
*	if clear_history is true frees the environment and the
*	command history before returning
*/
void	free_tools(t_tools *tools, bool clear_history)
{
	if (tools && tools->input_line)
	{
		free_ptr(tools->input_line);
		tools->input_line = NULL;
	}
	if (tools && tools->token)
		lstclear_token(&tools->token, &free_ptr);
	if (tools && tools->cmd)
		lst_clear_cmd(&tools->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (tools && tools->curr_dir)
			free_ptr(tools->curr_dir);
		if (tools && tools->curr_dir_old)
			free_ptr(tools->curr_dir_old);
		if (tools && tools->env)
			free_str_array(tools->env);
		rl_clear_history();
	}
}

/*
*	Closes opened file descriptors including pipes and input and output fds
*	if close_backups is set to true  it also closes
*	backup STDIN and STDOUT file descriptors
*/
void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_inp != -1)
			close(cmds->io_fds->fd_inp);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

/*
*	Frees the input/output fd structure
*/
void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->inputfl);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->inputfl)
		free_ptr(io->inputfl);
	if (io->outputfl)
		free_ptr(io->outputfl);
	if (io)
		free_ptr(io);
}

/*
*	Frees an array of strings
*/
void	free_str_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free_ptr(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

/*
*	Frees a pointer of any type if it is not NULL and sets it to NULL.
*	avoids accidental double-frees.
*/
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
