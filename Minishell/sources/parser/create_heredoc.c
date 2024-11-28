/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:09:01 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 16:07:35 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Opens a heredoc awaiting user input.
*	Transform any given variables into	their environment values.
*/
bool	open_heredoc(t_tools *tools, t_io_fds *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->inputfl, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(tools, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

/*
*	Generates a unique name for the current heredoc.
*	Returns the new heredoc name.
*/
static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

/*
*	Returns the heredoc delimiter. Quotes are removed if present
*	around the delimiter, and the quotes boolean is set to true.
*/
static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

/*
*	Creates a temporary heredoc file which will be filled with
*	user input.
*/
void	create_heredoc(t_tools *tools,
	t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;
	t_io_fds	*io;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->inputfl = get_heredoc_name();
	io->heredoc_delimiter = get_delim(temp->next->str, &(io->heredoc_quotes));
	if (open_heredoc(tools, io))
		io->fd_inp = open(io->inputfl, O_RDONLY);
	else
		io->fd_inp = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
