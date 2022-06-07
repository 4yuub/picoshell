/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:12:52 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/06/07 18:59:46 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*check_word(t_token *tokens)
{
	t_token	*ret;

	ret = 0x0;
	if (tokens && (tokens->type == WSPACE))
		tokens = tokens->next;
	if (tokens && (tokens->type == WORD || tokens->type == QUOTE
			||tokens->type == DQUOTE || tokens->type == WILDCARD
			|| tokens->type == DOLLAR || tokens->type == RET))
	{
		if (tokens && tokens->next && (tokens->type == DOLLAR
				&& (tokens->next->type == WORD || tokens->next->type == RET)))
			tokens = tokens->next;
		return (tokens);
	}
	return (0x0);
}

t_cmd_tree	*parse_exec(t_token *tokens)
{
	t_exec_node	*ex;

	ex = 0x0;
	tokens = check_word(tokens);
	if (tokens)
	{
		ex = malloc(sizeof(t_exec_node));
		if (!ex)
			return (0x0);
		ex->type = EXEC;
		ex->tcmd = tokens;
		ex->cmd = 0x0;
		ex->args = 0x0;
	}
	else
	{
		return (0x0);
	}
	tokens = tokens->next;
	tokens = check_word(tokens);
	if (tokens)
		ex->targs = tokens;
	else
		ex->args = 0x0;
	return ((t_cmd_tree *) ex);
}

t_cmd_tree	*parse_redir(t_token *tokens)
{
	t_redir_node	*re;

	if (tokens && tokens->type == WSPACE)
		tokens = tokens->next;
	if (tokens && (tokens->type == GREAT || tokens->type == LESS || tokens->type == APPEND))
	{
		tokens = tokens->next;
		if (tokens && tokens->type == WSPACE)
			tokens = tokens->next;
		if (tokens && (tokens->type == WORD || tokens->type == QUOTE
					|| tokens->type == DQUOTE ||
					tokens->type == WILDCARD || tokens->type == RET))
			return (0);
	}
	return 0;
		
}
