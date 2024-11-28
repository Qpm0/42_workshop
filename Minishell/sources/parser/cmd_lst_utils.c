/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:22:15 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/25 13:58:26 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_cmd(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->pipe_output = value;
	initialize_cmd(&new_node);
	return (new_node);
}

/*
*	Add a new t_command node to the end of a linked list.
*/
void	lst_add_back_cmd(t_command **cmdlist, t_command *new_node)
{
	t_command	*start;

	start = *cmdlist;
	if (start == NULL)
	{
		*cmdlist = new_node;
		return ;
	}
	if (cmdlist && *cmdlist && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_command	*lst_last_cmd(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
