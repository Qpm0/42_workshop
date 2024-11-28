/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:06:15 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:23:28 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Joins two strings together, freeing the previous string.
*	Returns the new concatenated string. Or NULL if an error occured.
*/
char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

/*
*	Prints an error message to the standard error with the
*	program name
*	Returns with the specified error number
*/
int	errmsg_cmd(char *detail, char *error_message, char *command, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (detail != NULL)
	{
		msg = join_strs(msg, detail);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	msg = join_strs(msg, ": ");
	if (command != NULL)
		msg = join_strs(msg, command);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (error_nb);
}

/*
*	Prints an error message that is unrelated to a specific command
*	for syntax errors
*/
void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " '");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
