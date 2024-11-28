/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:26:14 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/16 15:22:38 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exists(t_tools *tools, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*search_env_var(t_tools *tools, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(tools->env[i] + len);
	return (str);
}
/*
 * checks if the variable exists and if it does
 * it saves its value
 * if it is a ? the values becomes the exit code
 */

char	*recover_val(t_token *token, char *str, t_tools *tools)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(tools, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(tools, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_exit_code);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
