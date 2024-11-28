/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_trunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:16:18 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 16:11:19 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_relative_path(char *file_to_open)
{
	char	*path;
	char	*ret;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	ret = ft_strjoin(path, file_to_open);
	return (ret);
}

/* open_outputfl_trunc:
*	Opens an outputfl in truncated mode. If an outputfl was already set, frees it
*	and overwrites it. If a previous inputfl or outputfl open failed (file does
*	not exist or permission denied), does not open any further output file.
*
*	Ex.:
*		echo hello > forbidden_file > test
*		echo hello >> forbidden_file > test
*		< forbidden_file cat > test
*	In these 3 cases, the test file should not be opened or created.
*
*	"0664" permissions mean that the file's owner and members of the group can 
*	both read and write to the file, while others can only read it.
*/
static void	open_outputfl_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outputfl = ft_strdup(file);
	if (io->outputfl && io->outputfl[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outputfl, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outputfl, NULL, strerror(errno), false);
}

/*
*	The file whose name results from the expansion of word has to be opened 
*   in writing mode on fd n or the standard output (fd 1) if n is not specified.
*   If the file does not exist it is created;
*   if it does exist it is truncated to 0 size.
*/
void	create_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outputfl_trunc(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
