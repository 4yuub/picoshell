/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nature.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:05:59 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:56 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pipe(char *line, t_token **tokens)
{
	int i;

	if (!*line)
		return (0);
	i = 0;
	if (line[i + 1] == '|')
	{
		push_back(tokens, create_token(OR, ft_strdup("||"))); // to be freed
		return (2);
	}
	push_back(tokens, create_token(PIPE, ft_strdup("|"))); // to be freed
	return (1);
}

int is_and(char *line, t_token **tokens)
{
	int i;

	if (!*line)
		return (0);
	i = 0;
	if (line[i + 1] == '&')
	{
		push_back(tokens, create_token(AND, ft_strdup("&&"))); // to be freed
		return (2);
	}
	push_back(tokens, create_token(UNHANDLED, ft_strdup("&"))); // to be freed
	drop_tokens_err(tokens);
	return (1);
}

int is_wildcard(char *line, t_token **tokens)
{
	int i;

	if (!*line)
		return (0);
	i = 0;
	if (line[i] == '*')
		push_back(tokens, create_token(WILDCARD, ft_strdup("*?"))); // to be freed
	return (1);
}

int is_lparen(char *line, t_token **tokens)
{
	if (!*line)
		return (0);
	if (*line == '(')
		push_back(tokens, create_token(LPAR, ft_strdup("("))); // to be freed
	return (1);
}

int is_rparen(char *line, t_token **tokens)
{
	if (!*line)
		return (0);
	if (*line == ')')
		push_back(tokens, create_token(RPAR, ft_strdup(")"))); // to be freed
	return (1);
}
