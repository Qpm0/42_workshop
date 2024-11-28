/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:28:59 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:19:12 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Checks if the command is a directory rather than an executable.
*/
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

/*
*	Searches for the reason a command was not found in the system binaries.
*	Returns an error message and status if the command is invalid,
*/
int	check_command_not_found(t_tools *tools, t_command *cmd)
{
	if (cmd->args[0][0] == '\0')
		return (EXIT_SUCCESS);
	else if (ft_strchr(cmd->command, '/') == NULL
		&& get_env_var_index(tools->env, "PATH") != -1)
		return (errmsg_cmd(NULL, "command not found", cmd->command,
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (errmsg_cmd(NULL, strerror(errno), cmd->command, CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (errmsg_cmd(NULL, "Is a directory", cmd->command,
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (errmsg_cmd(NULL, strerror(errno), cmd->command,
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
