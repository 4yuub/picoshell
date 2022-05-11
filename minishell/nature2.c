/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nature2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:14:07 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:55 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_less(char *line, t_token **tokens)
{
	int	i;

	if (!*line)
		return (0);
	i = 0;
	if (line[i + 1] == '<')
	{
		push_back(tokens, create_token(HERDOC, ft_strdup("<<"))); // to be freed
		return (2);
	}
	push_back(tokens, create_token(LESS, ft_strdup("<"))); // to be freed
	return (1);
}

int is_quote(char *line, t_token **tokens)
{
	if (!*line)
		return (0);
	if (*line == '\'')
		push_back(tokens, create_token(QUOTE, ft_strdup("'"))); // to be freed
	return (1);
}

int is_dquote(char *line, t_token **tokens)
{
	if (!*line)
		return (0);
	if (*line == '"')
		push_back(tokens, create_token(DQUOTE, ft_strdup("\""))); // to be freed
	return (1);
}

int is_dollar(char *line, t_token **tokens)
{
	if (!*line)
		return (0);
	if (*line == '$' && *(line + 1) == '?')
	{
		push_back(tokens, create_token(RET, ft_strdup("$?"))); // to be freed
		return (2);
	}
	push_back(tokens, create_token(DOLLAR, ft_strdup("$"))); // to be freed
	return (1);
}

int is_word(char *line, t_token **tokens)
{
	int i;

	if (!*line)
		return (0);
	i = 0;
	while (line[i] != '\0' && not_in(line[i], " ><'\"$|?&*()"))
		i++;
	push_back(tokens, create_token(WORD, ft_strndup(line, i))); // to be freed
	return (i);
}
