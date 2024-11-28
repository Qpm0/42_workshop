/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:21:47 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:16:05 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

/*
*	Splits a command token containing a variable (VAR) into multiple tokens
*	and prepares them for processing as command arguments.
*/
static void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(ft_strdup(strs[1]), NULL, WORD, NORMAL);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_add_back_token(&new_tokens,
			lst_new_token(ft_strdup(strs[i]), NULL, WORD, NORMAL));
	lst_add_back_token(&new_tokens,
		lst_new_token(NULL, NULL, END, NORMAL));
	fill_args(&new_tokens, last_cmd);
	lstclear_token(&tmp, &free_ptr);
	free_str_array(strs);
}

/*
*	Processes a list of tokens to build a command and its arguments based on
*	token types.
*/
void	create_word(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			if (temp->type == VAR && contains_space(temp->str))
				split_var_cmd_token(last_cmd, temp->str);
			else
				last_cmd->command = ft_strdup(temp->str);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}
