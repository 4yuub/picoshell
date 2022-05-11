/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:57:33 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:57 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(char *line, t_token **tokens)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i += is_space(&line[i], tokens);
		else if (line[i] == '>')
			i += is_great(&line[i], tokens);
		else if (line[i] == '<')
			i += is_less(&line[i], tokens);
		else if (line[i] == '\'')
			i += is_quote(&line[i], tokens);
		else if (line[i] == '"')
			i += is_dquote(&line[i], tokens);
		else if (line[i] == '$')
			i += is_dollar(&line[i], tokens);
		else if (line[i] == '|')
			i += is_pipe(&line[i], tokens);
		else if (line[i] == '&')
			i += is_and(&line[i], tokens);
		else if (line[i] == '*')
			i += is_wildcard(&line[i], tokens);
		else if (line[i] == '(')
			i += is_lparen(&line[i], tokens);
		else if (line[i] == ')')
			i += is_rparen(&line[i], tokens);
		else if (not_in(line[i], " ><'\"$|?&*()"))
			i += is_word(&line[i], tokens);
		else
		{
			flag = 1;
			push_back(tokens, create_token(UNHANDLED, ft_strdup(&line[i]))); // to be freed
			break;
		}
	}
	if (flag)
		drop_tokens_err(tokens);
}

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token)); //to_be_freed
	if (token == NULL || value == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void drop_tokens_err(t_token **tokens)
{
	t_token *next;

	while ((*tokens)->next)
	{
		next = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = next;
	}
	if (*tokens)
	{
		printf("unhandled token : %s\n", (*tokens)->value);
		free((*tokens)->value);
		free(*tokens);
		*tokens = NULL;
	}
}
