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

char	*expande(char *str, t_env *env_list);
char	*join_args(t_token *tokens, int args_count, t_env *env_list)
{
	char		*res;
	char		*tmp;
	char		*tmp2;
	char		*filtered;
	

	res = 0x0;
	tmp = 0x0;
	tmp2 = 0x0;
	while (args_count-- > 0)
	{
		tmp = res;
		filtered = expande(tokens->value, env_list);
		res = ft_strjoin(res, filtered);
		free(tmp);
		free(filtered);
		tmp2 = ft_strjoin(res, " ");
		free(res);
		res = tmp2;
		tokens = get_token(tokens->next);
	}
	return ((char *) res);
}

void print_tree(t_cmd_tree *a, t_env *list)
{
	if (a && a->type == EXEC)
	{
		printf("exec ");
		t_exec_node *b = (t_exec_node *) a;
		if (b->tcmd)
			printf("%s : ", b->tcmd->value);
		if (b->targs)
		{
			b->args = join_args(b->targs, b->args_count, list);
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
				print_tree(b->sub, list);
		}
	}
	else if (a && a->type == PI)
	{
		t_pipe_node *b = (t_pipe_node *) a;
		print_tree(b->left, list);
		print_tree(b->right, list);
	}
	else if (a && a->type == ANDD)
	{
		t_and_node *b = (t_and_node *) a;
		print_tree(b->left, list);
		print_tree(b->right, list);
	}
	else if (a && a->type == ORR)
	{
		t_or_node *b = (t_or_node *) a;
		print_tree(b->left, list);
		print_tree(b->right, list);
	}
}

void print_tokens(t_token *tokens);
void print_rev_tokens(t_token *tokens);

char *get_val(char *str, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, str))
		{
			free(str);
			return (env_list->value);
		}
		env_list = env_list->next;
	}
	free(str);
	return (ft_strdup(""));
}

char	*expande(char *str, t_env *env_list)
{
	int			i;
	int			j;
	const char	*res = 0x0;
	char		*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i += 1;
			if (str[i] == ' ' || str[i] == '\0')
				res = ft_strjoin(res, "$");
			else
			{
				j = i;
				while (str[i] && str[i] != ' ' && str[i] != '$')
					i += 1;
				res = ft_strjoin(res, get_val(ft_strndup(str + j, i - j),  env_list));
			}
		}
		else
		{
			j = i;
			while (str[i] && str[i] != '$')
				i += 1;
			tmp = ft_strndup(str + j, i - j);
			res = ft_strjoin(res, tmp);
			free(tmp);
		}
	}
	return ((char *) res);
}

int check_redir(t_token *tokens)
{
	int	res;

	res = 1;
	if ((tokens && ((tokens->type == WORD && tokens->value[0] == '&') || tokens->type == PIPE ||
				tokens->type == WILDCARD || tokens->type == LPAR ||
				tokens->type == RPAR || tokens->type == GREAT||
				tokens->type == LESS || tokens->type == APPEND || tokens->type == AND)) || !tokens)
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
				tokens->type == LESS || tokens->type == APPEND || tokens->type == AND)) || !tokens)
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
	/** while (1) */
	/** { */
	/**     char *bu = readline(">"); */
	/**     char *r = expande(bu, env_list); */
	/**     printf("%s\n", r); */
	/** } */
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
		print_tree(a->tree, env_list);
	}
	/**     print_tokens(tokens); */
		/** printf("\n------\n"); */
		/** print_rev_tokens(tokens); */
	/** } */
}
