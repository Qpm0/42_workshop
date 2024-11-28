/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:09:49 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:38:53 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_code;

/* 
*	Waits for child to terminate after cleaning up fds and the command
*	list. Returns a child's exit status as bash does
*		(The return status of a simple command is its
*		exit status as provided by the waitpid function, or
*		128 + n if the command was terminated by signal n.)
*	If there are multiple commands in a pipeline the exit status of a 
*	pipeline is the exit status of the last command in the pipeline
*/
static int	get_child(t_tools *tools)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(tools->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == tools->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/*
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the 
*	main process.
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/
static int	create_child(t_tools *tools)
{
	t_command	*cmd;

	cmd = tools->cmd;
	while (tools->pid != 0 && cmd)
	{
		tools->pid = fork();
		if (tools->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (tools->pid == 0)
			execute_command(tools, cmd);
		cmd = cmd->next;
	}
	return (get_child(tools));
}

/*
*	Prepares the command list for execution.
*	Creates pipes and checks the input and output files.
*/
static int	prep_for_exec(t_tools *tools)
{
	if (!tools || !tools->cmd)
		return (EXIT_SUCCESS);
	if (!tools->cmd->command)
	{
		if (tools->cmd->io_fds && !check_inputfl_outputfl(tools->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(tools))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

/* 
*	Executes the given commands by creating child processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate.
*/

int	executor(t_tools *tools)
{
	int	ret;

	ret = prep_for_exec(tools);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!tools->cmd->pipe_output && !tools->cmd->prev
		&& check_inputfl_outputfl(tools->cmd->io_fds))
	{
		redirect_io(tools->cmd->io_fds);
		ret = execute_builtin(tools, tools->cmd);
		restore_io(tools->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_child(tools));
}
