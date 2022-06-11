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
	if (a && a->type == EXEC)
	{
		printf("exec ");
		t_exec_node *b = (t_exec_node *) a;
		if (b->tcmd)
			printf("%s : ", b->tcmd->value);
		if (b->targs)
			printf("%s\n", b->targs->value);
		printf("args count : %d\n", b->args_count);
		printf("\n");
	}
	else if (a && a->type == REDIR)
	{
		t_redir_node *b = (t_redir_node *) a;
		if (b)
		{
			printf("redir : %s\n", b->tok->value);
			if (b->sub)
				print_tree(b->sub);
		}
	}
	else if (a && a->type == PI)
	{
		t_pipe_node *b = (t_pipe_node *) a;
		print_tree(b->left);
		print_tree(b->right);
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
			else if (!tokens)
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
	g_minishell.on_error = 0;
	res.current = 0x0;
	res.tree = 0x0;
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
		t_parser_res *a = parse_pipe(&res);
		if (g_minishell.on_error)
		{
			printf("something_went_wrong\n");
			continue;
		}
		print_tree(a->tree);
		print_tokens(tokens);
		/** printf("\n------\n"); */
		/** print_rev_tokens(tokens); */
	}
}
