/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:10:11 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:19:38 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This function joins all the tokens of a quoted sentence
*	that was previously split.
*	To join them, the tokens have to be of type VAR and the join
*	setting must be set to true (the quotes are implied)
*	The function is only used when the command is "echo".
*/

char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (temp->type == VAR && temp->next->type == VAR
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->str);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

/*
*	Counts the number of arguments in the list of tokens.
*	To consider a token or multiple tokens as an argument they must be either
*	a WORD or a VAR and if they	temp = *token_node;
*	are a VAR that has to be joined, we have
*	to loop through all the tokens that check these conditions 
*	(type == VAR and join == true) before counting them as one argument
*/
int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		if (temp->type == VAR && temp->join == true)
		{
			while (temp->type == VAR && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

char	**copy_in_new_tab(int len, char **new_tab,
			t_command *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/*
*	If a variable does not exist in the environment, the token string
*	will contain "\0". In this case, echo should not print the variable
*	or any spaces before/after it. Therefore the token must be
*	removed before creating/adding echo args.
*	However, if the variable exists but its value is empty, the token
*	should not be removed.
*/
void	remove_empty_var_args(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->type == VAR && temp->str[0] == '\0'
			&& temp->var_exists == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			lstdelone_token(temp->prev, free_ptr);
		}
		else
			temp = temp->next;
	}
}
