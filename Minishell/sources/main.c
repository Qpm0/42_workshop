/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:08:47 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:23:56 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Sets how signals should behave
 * reads the input line and saves it
 * starts processing the input line
 * sets the exit code variable to what the execution returns
 * frees tools
 */

void	minishell(t_tools *tools)
{
	while (1)
	{
		set_signals();
		tools->input_line = readline(PROMPT);
		if (parse_line(tools) == true)
			g_exit_code = executor(tools);
		free_tools(tools, false);
	}
}

/* main function
 * set the tools structure's memory to 0
 * check arguments
 * initializes working directories and the env variables
 * changes the terminal attribute so it doesnt print signal input
 * starts the main minishell loop
 * exits the program
*/
int	main(int ac, char **av, char **env)
{
	t_tools	tools;

	ft_memset(&tools, 0, sizeof(t_tools));
	if (ac > 1 && av[1] != NULL)
		return (printf("Too many arguments.\n"), 0);
	if (!init_tools(&tools, env))
		exit_minishell(NULL, EXIT_FAILURE);
	termios_change(false);
	minishell(&tools);
	exit_minishell(&tools, g_exit_code);
	return (0);
}
