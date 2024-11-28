/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:09:12 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:23:50 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Initializes a tools variable with the contents of the environment
*	variables from the shell
*/
static bool	init_env(t_tools *tools, char **env)
{
	int		i;

	tools->env = ft_calloc(env_var_count(env) + 1, sizeof * tools->env);
	if (!tools->env)
		return (false);
	i = 0;
	while (env[i])
	{
		tools->env[i] = ft_strdup(env[i]);
		if (!tools->env[i])
			return (false);
		i++;
	}
	return (true);
}

/*
*	Initializes working directory variables to have a backup in case
*	environment PWD and OLDPWD are unset or not present
*	in the environment
*	Used for cd builtin
*/
static bool	init_wds(t_tools *tools)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	tools->curr_dir = ft_strdup(wd);
	if (!tools->curr_dir)
		return (false);
	if (get_env_var_index(tools->env, "OLDPWD") != -1)
	{
		tools->curr_dir_old = ft_strdup(get_env_var_value(tools->env,
					"OLDPWD"));
		if (!tools->curr_dir_old)
			return (false);
	}
	else
	{
		tools->curr_dir_old = ft_strdup(wd);
		if (!tools->curr_dir_old)
			return (false);
	}
	return (true);
}

/*
*	Initializes the tools structure used in parsing and executing user input
*/
bool	init_tools(t_tools *tools, char **env)
{
	if (!init_env(tools, env))
	{
		errmsg_cmd("ERROR", "Could not initialize environment", NULL, 1);
		return (false);
	}
	if (!init_wds(tools))
	{
		errmsg_cmd("ERROR", "Could not initialize working directories", NULL,
			1);
		return (false);
	}
	tools->token = NULL;
	tools->input_line = NULL;
	tools->cmd = NULL;
	tools->pid = -1;
	g_exit_code = 0;
	return (true);
}

/*
*	Initializes a structure with normal values to contain
*	inputfl and outputfl information for a command
*	used for creating commands
*/
void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->inputfl = NULL;
		cmd->io_fds->outputfl = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_inp = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
