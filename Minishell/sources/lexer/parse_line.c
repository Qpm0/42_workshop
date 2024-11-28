/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:01:18 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/10 13:58:57 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

/*
*	Checks if the input is valid
*	Adds history
*	Splits the input into tokens
*	Checks for variables and consecutive ops
*	Replaces the variables with their values
*	Checks the quotes to see if they need to be removed or not from the token
*	Creates the commands
*/
bool	parse_line(t_tools *tools)
{
	if (tools->input_line == NULL)
		exit_builtin(tools);
	else if (ft_strcmp(tools->input_line, "\0") == 0)
	{
		g_exit_code = 0;
		return (false);
	}
	else if (input_is_space(tools->input_line))
		return (true);
	add_history(tools->input_line);
	if (fill_token_list(tools, tools->input_line) == FAILURE)
		return (false);
	if (tools->token->type == END)
		return (false);
	if (check_if_var(&tools->token) == FAILURE)
		return (g_exit_code = 1, (false));
	var_expander(tools, &tools->token);
	handle_quotes(tools);
	create_commands(tools, tools->token);
	return (true);
}
