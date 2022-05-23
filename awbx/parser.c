/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:12:52 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/23 15:04:12 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tree	*parse_redirs(t_token **tokens)
{
	int res;
	t_token	*tok;

	res = has_redirections(*tokens);
	while (res != -1)
	{
		tok = get_token(tokens, res);
		if (tok->next->type == WORD)
		{
			tok = get_token(tokens, res);
			if (tok->type == APPEND)
				cmd = redircmd(cmd, ft_strdup(tok->value), 	O_WRONLY | O_CREAT | O_APPEND);
			else if (tok->type == GREAT)
				cmd = redircmd(cmd, ft_strdup(tok->value), O_WRONLY | O_CREAT | O_TRUNC);
		}
	}
	return (ret);
}


t_cmd_tree	*parse(t_token **tokens)
{
	t_cmd_tree	*cmd_tree;
}
