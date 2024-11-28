/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:42:10 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 14:06:10 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->str[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->str[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

static bool	if_quotes_and_normal(t_token **token_node, int i)
{
	if (((*token_node)->str[i] == '\'' || (*token_node)->str[i] == '\"')
		&& (*token_node)->status == NORMAL)
		return (true);
	else
		return (false);
}

static bool	change_back_to_normal(t_token **token_node, int *i)
{
	if (((*token_node)->str[*i] == '\'' && (*token_node)->status == SQUOTE)
		|| ((*token_node)->str[*i] == '\"' && (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = NORMAL;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

/*
 * take a token node and check if it has closed quotes
 * if it does ,change the status to what quotes it finds
 * copy everything that isnt quotes from the original string
 * into the new one then swap with the original string
 */
int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->str, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->str[i])
	{
		if (if_quotes_and_normal(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_normal(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_line;
	(*token_node)->join = true;
	return (0);
}
