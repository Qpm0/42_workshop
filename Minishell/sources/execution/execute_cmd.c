/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:12:08 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:25:33 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Executes the builtin command.
*/
int	execute_builtin(t_tools *tools, t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(tools, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(tools, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(tools, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(tools, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(tools, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(tools, cmd->args);
	else if ((ft_strncmp(cmd->command, "exit", 5) == 0)
		&& tools->token->next->next)
	{
		ret = exit_check(tools);
	}
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(tools);
	return (ret);
}

/*
*	Check if the exit function has more than 1 argument
*	which is numerical, returns the exit code.	
*/
int	exit_check(t_tools *tools)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	tools->token = tools->token->next;
	if (*tools->token->next->str != '\0')
	{
		g_exit_code = 1;
		errmsg_cmd(NULL, NULL, "too many arguments", EXIT_FAILURE);
		return (1);
	}
	else
	{
		g_exit_code = ft_atoi(tools->token->str);
		ret = exit_builtin(tools);
	}
	return (ret);
}

/*
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*/
static int	execute_sys_bin(t_tools *tools, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(tools, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, tools->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/*
*	Executes the given command, in case it is a 
*	local directory file or already contains the
*	path to bin.
*/
static int	execute_local_bin(t_tools *tools, t_command *cmd)
{
	int	ret;

	ret = check_command_not_found(tools, cmd);
	if (ret != 0)
		return (ret);
	if (cmd->args[0][0] == '\0')
		return (EXIT_SUCCESS);
	if (execve(cmd->command, cmd->args, tools->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

/*
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command
*		3. Execute given command name directly (local bin)
*	Child exits with it's executed program's exit code, or 1 if it 
*	could not find one.
*/
int	execute_command(t_tools *tools, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_minishell(tools, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_inputfl_outputfl(cmd->io_fds))
		exit_minishell(tools, EXIT_FAILURE);
	set_pipe_fds(tools->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(tools->cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(tools, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_minishell(tools, ret);
		ret = execute_sys_bin(tools, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_minishell(tools, ret);
	}
	ret = execute_local_bin(tools, cmd);
	exit_minishell(tools, ret);
	return (ret);
}
