/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:06:46 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:28:06 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Opens an output file in append mode. If an output file was 
*	already set, frees it and overwrites it. If a previous input 
*	file or output file open failed (file does not exist or permission denied), 
*	does not open any further output file.
*/
static void	open_file_append(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outputfl = ft_strdup(file);
	if (io->outputfl && io->outputfl[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outputfl, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outputfl, NULL, strerror(errno), false);
}

/*
	Redirection of output in append mode causes the file whose name results 
	from the expansion of word to be opened for appending on file descriptor n, 
	or the standard output (fd 1) if n is not specified. 
*/
void	create_append(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_file_append(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
