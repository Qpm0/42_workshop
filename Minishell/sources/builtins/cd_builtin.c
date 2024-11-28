/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:03:08 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 15:49:14 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Updates the PWD and OLDPWD in the environment after a directory change.
*	A copy of the paths are stored internally for use in case the environment
*	variables are unset.
*/
static void	update_wds(t_tools *tools, char *wd)
{
	set_env_var(tools, "OLDPWD", get_env_var_value(tools->env, "PWD"));
	set_env_var(tools, "PWD", wd);
	if (tools->curr_dir_old)
	{
		free_ptr(tools->curr_dir_old);
		tools->curr_dir_old = ft_strdup(tools->curr_dir);
	}
	if (tools->curr_dir)
	{
		free_ptr(tools->curr_dir);
		tools->curr_dir = ft_strdup(wd);
	}
	free_ptr(wd);
}

/* 
*	chdir can sometimes set errno to ESTALE ("Stale file handle")
*	when a parent directory is removed on some systems. This is due
*	to the inode table entry being recycled. This is a fix to display
*	"no such file or directory" error instead.
*	This solves the cd (non-exiting file) problem.
*/

static bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", strerror(errno), path, errno);
	return (false);
}

/*
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*/
static bool	change_dir(t_tools *tools, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno),
			errno);
		ret = ft_strjoin(tools->curr_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(tools, ret);
	return (true);
}

/*
*	Executes the builtin cd command by changing the working directory.
*/
int	cd_builtin(t_tools *tools, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(tools->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(tools, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(tools->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(tools, path));
	}
	return (!change_dir(tools, args[1]));
}
