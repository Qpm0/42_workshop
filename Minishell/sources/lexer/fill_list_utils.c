/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:34:40 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/30 13:57:04 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * Check if the separator needs 2 letters to save then
 * add it to the token list
 */

int	save_token(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL));
	}
	return (0);
}
/*
 * Create a new list node and add the saved word to the token list
 */

int	save_word(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_token(token_lst, \
			lst_new_token(word, ft_strdup(word), WORD, NORMAL));
	free(word);
	return (0);
}

/*
 * Check what character type is the current character
 */

int	check_character(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}
/*
 * Check the quotes status (Closed / Unclosed)
 */

int	check_quotes(int status, char *str, int i)
{
	if (str[i] == '\'' && status == NORMAL)
		status = SQUOTE;
	else if (str[i] == '\"' && status == NORMAL)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = NORMAL;
	else if (str[i] == '\"' && status == DQUOTE)
		status = NORMAL;
	return (status);
}

/*
 * If it reaches EOF  and type isnt an separator save token as text
 * if the type is a separator save it as a separator
 */
int	create_token(int *i, char *str, int start, t_tools *tools)
{
	int	type;

	type = check_character(str, (*i));
	if (type)
	{
		if ((*i) != 0 && check_character(str, (*i) - 1) == 0)
			save_word(&tools->token, str, (*i), start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == TRUNC || type == END)
		{
			save_token(&tools->token, str, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
