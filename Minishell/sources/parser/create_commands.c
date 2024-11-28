/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:16:58 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/25 15:36:20 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_no_arg_commands(t_tools *tools)
{
	t_command	*cmd;

	if (!tools || !tools->cmd)
		return ;
	cmd = tools->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(tools->cmd);
}

void	create_commands(t_tools *tools, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&tools->cmd, lst_new_cmd(false));
		if (temp->type == WORD || temp->type == VAR)
			create_word(&tools->cmd, &temp);
		else if (temp->type == INPUT)
			create_input(&tools->cmd, &temp);
		else if (temp->type == TRUNC)
			create_trunc(&tools->cmd, &temp);
		else if (temp->type == HEREDOC)
			create_heredoc(tools, &tools->cmd, &temp);
		else if (temp->type == APPEND)
			create_append(&tools->cmd, &temp);
		else if (temp->type == PIPE)
			create_pipe(&tools->cmd, &temp);
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_commands(tools);
}
