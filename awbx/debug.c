/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 10:41:45 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 10:41:45 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == WSPACE)
			printf("[SPACE] : <%s>\n", tokens->value);
		else if (tokens->type == GREAT)
			printf("[GREAT]\n");
		else if (tokens->type == APPEND)
			printf("[APPEND]\n");
		else if (tokens->type == LESS)
			printf("[LESS]\n");
		else if (tokens->type == HERDOC)
			printf("[HERDOC]\n");
		else if (tokens->type == QUOTE)
			printf("[QUOTE]\n");
		else if (tokens->type == DQUOTE)
			printf("[DQUOTE]\n");
		else if (tokens->type == DOLLAR)
			printf("[DOLLAR]\n");
		else if (tokens->type == PIPE)
			printf("[PIPE]\n");
		else if (tokens->type == OR)
			printf("[OR]\n");
		else if (tokens->type == RET)
			printf("[RET]\n");
		else if (tokens->type == AND)
			printf("[AND]\n");
		else if (tokens->type == UNHANDLED)
			printf("[UNHANDLED]\n");
		else if (tokens->type == WILDCARD)
			printf("[WILDCARD]\n");
		else if (tokens->type == LPAR)
			printf("[LPAR]\n");
		else if (tokens->type == RPAR)
			printf("[RPAR]\n");
		else if (tokens->type == WORD)
			printf("[WORD] : %s\n", tokens->value);
		
		tokens = tokens->next;
	}
}

void print_rev_tokens(t_token *tokens)
{
	t_token *tmp;
	tmp = tokens;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->type == WSPACE)
			printf("[SPACE] : <%s>\n", tmp->value);
		else if (tmp->type == GREAT)
			printf("[GREAT]\n");
		else if (tmp->type == APPEND)
			printf("[APPEND]\n");
		else if (tmp->type == LESS)
			printf("[LESS]\n");
		else if (tmp->type == HERDOC)
			printf("[HERDOC]\n");
		else if (tmp->type == QUOTE)
			printf("[QUOTE]\n");
		else if (tmp->type == DQUOTE)
			printf("[DQUOTE]\n");
		else if (tmp->type == DOLLAR)
			printf("[DOLLAR]\n");
		else if (tmp->type == PIPE)
			printf("[PIPE]\n");
		else if (tmp->type == OR)
			printf("[OR]\n");
		else if (tmp->type == RET)
			printf("[RET]\n");
		else if (tmp->type == AND)
			printf("[AND]\n");
		else if (tmp->type == UNHANDLED)
			printf("[UNHANDLED]\n");
		else if (tmp->type == WILDCARD)
			printf("[WILDCARD]\n");
		else if (tmp->type == LPAR)
			printf("[LPAR]\n");
		else if (tmp->type == RPAR)
			printf("[RPAR]\n");
		else if (tmp->type == WORD)
			printf("[WORD] : %s\n", tmp->value);
		tmp = tmp->prev;
	}
}
