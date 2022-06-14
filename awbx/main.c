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


char	*join_args(t_token *tokens, int args_count)
{
	char		*res;
	char		*tmp;
	char		*tmp2;
	

	res = 0x0;
	tmp = 0x0;
	tmp2 = 0x0;
	while (args_count-- > 0)
	{
		tmp = res;
		res = ft_strjoin(res, tokens->value);
		free(tmp);
		tmp2 = ft_strjoin(res, " ");
		free(res);
		res = tmp2;
		tokens = get_token(tokens->next);
	}
	return ((char *) res);
}

void print_tree(t_cmd_tree *a)
{
	if (a && a->type == EXEC)
	{
		printf("exec ");
		t_exec_node *b = (t_exec_node *) a;
		if (b->tcmd)
			printf("%s : ", b->tcmd->value);
		if (b->targs)
		{
			b->args = join_args(b->targs, b->args_count);
			printf("args : %s\n", b->args);
		}
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
	else if (a && a->type == ANDD)
	{
		t_and_node *b = (t_and_node *) a;
		print_tree(b->left);
		print_tree(b->right);
	}
	else if (a && a->type == ORR)
	{
		t_or_node *b = (t_or_node *) a;
		print_tree(b->left);
		print_tree(b->right);
	}
}

void expand_args(t_token *tokens)
{
	while (args_count-- > 0)
	{
		if (tokens->type == DQUOTE || tokens->type == DOLLAR)
			expand_word(tokens->value);
		tokens = tokens->next;
	}

void print_tokens(t_token *tokens);
void print_rev_tokens(t_token *tokens);

int check_redir(t_token *tokens)
{
	int	res;

	res = 1;
	if ((tokens && ((tokens->type == WORD && tokens->value[0] == '&') || tokens->type == PIPE ||
				tokens->type == WILDCARD || tokens->type == LPAR ||
				tokens->type == RPAR || tokens->type == GREAT||
				tokens->type == LESS || tokens->type == APPEND)) || !tokens)
		res = 0;
	return (res);
}

int	check_herdoc(t_token *tokens)
{
	int	res;

	res = 1;
	if ((tokens && ((tokens->type == WORD && tokens->value[0] == '&') || tokens->type == PIPE ||
				tokens->type == LPAR ||
				tokens->type == RPAR || tokens->type == GREAT||
				tokens->type == LESS || tokens->type == APPEND)) || !tokens)
		res = 0;
	return (res);
}

int analyse(t_token *tokens)
{
	tokens = get_token(tokens);
	while (tokens)
	{
		if (tokens && (tokens->type == GREAT || tokens->type == LESS || tokens->type == APPEND))
		{
			tokens = get_token(tokens->next);
			if (!check_redir(tokens))
				return (0);
		}
		else if (tokens && tokens->type == HERDOC)
		{
			tokens = get_token(tokens->next);
			if (!check_herdoc(tokens))
					return (0);
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}

void ft_init(t_parser_res *res, t_env *env_list, t_token *tokens)
{
	tokens = 0x0;
	env_list = 0x0;
	g_minishell.on_error = 0;
	res->current = 0x0;
	res->tree = 0x0;
}

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_env		*env_list;
	t_token		*tokens;
	t_parser_res	res;

	ft_init(&res, env_list, tokens);
	get_env_list(&env_list, env);
	while (1)
	{
		cmd = readline("awbx$ "); // to be freed
		if (!cmd)
			break ;
		if (!tokenize(&tokens, cmd) || !tokens)
			continue ;
		if (!analyse(tokens))
		{
			printf("syntax error\n");
			continue ;
		}
		res.current = tokens;
		t_parser_res *a = parse_cmd(&res);
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
