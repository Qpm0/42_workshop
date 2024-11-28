/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:20:39 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:28:18 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	remove_old_file_ref(t_io_fds *io, bool inputfl)
{
	if (inputfl == true && io->inputfl)
	{
		if (io->fd_inp == -1 || (io->outputfl && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->inputfl);
		}
		free_ptr(io->inputfl);
		close(io->fd_inp);
	}
	else if (inputfl == false && io->outputfl)
	{
		if (io->fd_out == -1 || (io->inputfl && io->fd_inp == -1))
			return (false);
		free_ptr(io->outputfl);
		close(io->fd_out);
	}
	return (true);
}

/*
*	Opens an input file. If an input file was already set, frees it
*	and overwrites it. If a previous input file open failed (file does
*	not exist or permission denied), does not open any further input file.
*/
static void	open_inputfl(t_io_fds *io, char *file, char *original_filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->inputfl = ft_strdup(file);
	if (io->inputfl && io->inputfl[0] == '\0')
	{
		errmsg_cmd(original_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_inp = open(io->inputfl, O_RDONLY);
	if (io->fd_inp == -1)
		errmsg_cmd(io->inputfl, NULL, strerror(errno), false);
}

/*
*	Redirection of input causes the file whose name results from the expansion 
*	of word to be opened for reading on file descriptor n, or the standard input
*	(file descriptor 0) if n is not specified.
*/
void	create_input(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_inputfl(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
