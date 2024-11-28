/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:06:43 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/23 15:01:32 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Resets the readline user input prompt for interactive signal handling
*/
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
*	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\)
*	SIGINT resets the user input prompt to a new blank line
*	calls the function signal_reset_prompt only when SIGINT is used
*	SIGQUIT is ignored
*/
void	set_signals(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/*
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/*
*	Checks if the control characters are echoed to the terminal by
*	modifying the ECHOCTL flag in the c_lflag field of the terminal
*	then applying those modified settings to the standard output
*/
int	termios_change(bool echo_ctl_chr)
{
	struct termios	termios_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &termios_p);
	if (status == -1)
		return (-1);
	if (echo_ctl_chr)
		termios_p.c_lflag |= ECHOCTL;
	else
		termios_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_p);
	if (status == -1)
		return (-1);
	return (0);
}
