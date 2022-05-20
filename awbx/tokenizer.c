/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 10:02:22 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/20 19:39:24 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenize(t_token **tokens, char *line)
{
	int	i;
	int	tmp;
	int	res;
	int	flag;

	i = 0;
	flag = 0;
	res = 1;
	while (line[i])
	{
		if (line[i] == ' ')
			i += is_space(&line[i], tokens);
		else if (line[i] == '>')
			i += is_great(&line[i], tokens);
		else if (line[i] == '<')
			i += is_less(&line[i], tokens);
		else if (line[i] == '\'')
		{
			tmp = is_quote(&line[i], tokens); // free linked lists
			if (tmp == -1)
			{
				printf("missing \'\n");
				return (0);
			}
			i += tmp;
		}
		else if (line[i] == '"')
		{
			tmp = is_dquote(&line[i], tokens); // free linked lists
			if (tmp == -1)
			{
				printf("missing \"\n");
				return (0);
			}
			i += tmp;
		}
		else if (line[i] == '$')
			i += is_dollar(&line[i], tokens);
		else if (line[i] == '|')
			i += is_pipe(&line[i], tokens);
		else if (line[i] == '&')
		{
			tmp = is_and(&line[i], tokens);	
			if (tmp == 1)
			{
					res = 0;
					break;
			}
			else
				i += tmp;
		}
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
			push_back(tokens, create_token(UNHANDLED, ft_strndup(&line[i], 1))); // to be freed
			res = 0;
			break;
		}
	}
	if (flag)
		drop_tokens(tokens);
	return (res);
}


