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

t_token	*change_value(t_token *old, char *value)
{
	free(old->value);
	old->value = ft_strdup(value);
	old->type = WORD;
	return (old);
}

void expande(t_token *token, t_env *list)
{
	if (!token || !list)
		return ;
	while (list)
	{
		if (ft_strcmp(list->key, token->value))
		{
				token = change_value(token, list->value);
				return ;
		}
		list = list->next;
	}
}

t_cmd_tree	*redir_cmd(t_cmd_tree *sub, char *file, int flag, int fd)
{
	t_redir_node	*node;

	node = malloc(sizeof(t_redir_node));
	if (!node)
		return (0x0);
	node->fd = fd;
	node->file = file;
	node->flag = flag;
	node->sub = sub;
	return ((t_cmd_tree *) node);
}

t_cmd_tree	*parse_redirs(t_token **tokens, t_cmd_tree	*cmd)
{
	t_token	*tmp;
	int	i;

	if (!tokens || !*tokens)
		return (0x0);
	tmp = *tokens;
	i = 0;
	while (tmp)
	{
		if (tmp && tmp->type == GREAT)
		{
			if (tmp->next && tmp->next->type == WSPACE)
				tmp = tmp->next;
			tmp = tmp->next;
			if (!tmp || (tmp->type != WORD && tmp->type != DOLLAR && tmp->type != QUOTE && tmp->type != DQUOTE))
			{
				printf("missing file for redirection\n");
				return (0x0);
			}
		}
		else if (tmp && tmp->type == LESS)
		{
			if (tmp->next && tmp->next->type == WSPACE)
				tmp = tmp->next;
			tmp = tmp->next;
			if (!tmp || (tmp->type != WORD && tmp->type != DOLLAR && tmp->type != QUOTE && tmp->type != DQUOTE))
			{
				printf("missing file for redirection\n");
				return (0x0);
			}
		}
		else if (tmp && tmp->type == APPEND)
		{
			if (tmp->next && tmp->next->type == WSPACE)
				tmp = tmp->next;
			tmp = tmp->next;
			if (!tmp || (tmp->type != WORD && tmp->type != DOLLAR && tmp->type != QUOTE && tmp->type != DQUOTE))
			{
				printf("missing file for redirection\n");
				return (0x0);
			}
		}
		else if (tmp && tmp->type == HERDOC)
		{
			if (tmp->next && tmp->next->type == WSPACE)
				tmp = tmp->next;
			tmp = tmp->next;
			if (!tmp || (tmp->type != WORD && tmp->type != DOLLAR && tmp->type != QUOTE && tmp->type != DQUOTE))
			{
				printf("missing delimiter\n");
				return (0x0);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp && tmp->type == GREAT && !tmp->visited)
		{
			tmp->visited = 1;
			if (tmp->next && tmp->next->type == WSPACE)
			{
				tmp = tmp->next;
				tmp->visited = 1;
			}
			tmp = tmp->next;
			if (tmp && !tmp->visited && (tmp->type == WORD || tmp->type == DOLLAR || tmp->type == QUOTE || tmp->type == DQUOTE))
			{
				tmp->visited = 1;
				cmd = redir_cmd(cmd, ft_strdup(tmp->value), O_CREAT | O_TRUNC | O_RDONLY, 1);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}

	// herdoc is very different from other redirections so it will be treated differently
}
