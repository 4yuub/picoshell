/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:52:06 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/06/07 19:03:49 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

void print_tree(t_cmd_tree *a)
{
	if (a->type == EXEC)
	{
		t_exec_node *b = (t_exec_node *) a;
		if (b->tcmd)
			printf("%s : ", b->tcmd->value);
		if (b->targs)
			printf("%s", b->targs->value);
		printf("\n");
	}
	else if (a->type == REDIR)
	{
		t_redir_node *b = (t_redir_node *) a;
		if (b)
		{
			printf("%s : \n", b->tok->value);
			if (b->sub)
				print_tree(b->sub);
		}
	}
}

void print_tokens(t_token *tokens);
void print_rev_tokens(t_token *tokens);

int analyse(t_token *tokens)
{
	tokens = get_token(tokens);
	while (tokens)
	{
		if (tokens && (tokens->type == GREAT || tokens->type == LESS || tokens->type == APPEND))
		{
			tokens = get_token(tokens->next);
			if (tokens && (tokens->value[0] == '&' || tokens->value[0] == '|' ||
						tokens->value[0] == '*' || tokens->value[0] == '(' ||
						tokens->value[0] == ')' || tokens->value[0] == '>' ||
						tokens->value[0] == '<'))
				return (0);
		}
		// need to check herdoc
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_env		*env_list;
	t_token		*tokens;
	t_parser_res	res;

	tokens = 0x0;
	env_list = 0x0;
	get_env_list(&env_list, env);
	while (1)
	{
		cmd = readline("awbx$ "); // to be freed
		if (!cmd)
			break ;
		if (!tokenize(&tokens, cmd))
			continue ;
		if (!analyse(tokens))
		{
			printf("syntax error\n");
			continue ;
		}
		res.current = tokens;
		t_parser_res *a = parse_exec(&res);
		print_tree(a->tree);
		/** print_tokens(tokens); */
		/** printf("\n------\n"); */
		/** print_rev_tokens(tokens);  */
	}
}
