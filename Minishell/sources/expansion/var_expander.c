/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:35:14 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 14:06:52 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*  After splitting the input into tokens, we have to expand
*  the variables
*  After the expansion is done quote characters are
*  removed from the original word unless they are between quotes.
*/
static void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == NORMAL)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == NORMAL)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = NORMAL;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = NORMAL;
}

static bool	is_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	is_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

/*
 * if the current type is a variable and if it is
 * check if there are aditional quotes in the token
 * if it finds a $ and there arent any separatos and the $ isnt in between quotes
 * and quotes are closed or double quotes replace the variable with
 * its values from env
 */
int	var_expander(t_tools *tools, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$'
					&& is_sep(temp->str[i + 1]) == false
					&& is_between_quotes(temp->str, i) == false
					&& (temp->status == NORMAL || temp->status == DQUOTE))
					replace_var(&temp,
						recover_val(temp, temp->str + i, tools), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

/*
*	Heredoc variant of var_expander
*	Replaces a string containing an environment variable with its  value
*/
char	*var_expander_heredoc(t_tools *tools, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_sep(str[i + 1]) == false
			&& is_between_quotes(str, i) == false)
			str = replace_str_heredoc(str,
					recover_val(NULL, str + i, tools), i);
		else
			i++;
	}
	return (str);
}
