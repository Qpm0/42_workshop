/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:31:15 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/25 16:33:20 by cmoreanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This function divides the given string into
*   words or separators (pipes,heredoc ...)
*	It checks each char of the string if it is a separator or
*   a word and then saves the token in a list
*   checks if there is an unclosed quote error and defines which
*   separators will be analyzed following rules
*   Without quotes, it tries to analyze all special characters
*   (') prevent all analysis
*   (") prevent most analysis
*/

int	fill_token_list(t_tools *tools, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = NORMAL;
	while (++i <= end)
	{
		status = check_quotes(status, str, i);
		if (status == NORMAL)
			start = create_token(&i, str, start, tools);
	}
	if (status != NORMAL)
	{
		if (status == DQUOTE)
			errmsg("unclosed quotes", "\"", true);
		else if (status == SQUOTE)
			errmsg("unclosed quotes", "\'", true);
		return (1);
	}
	return (0);
}
