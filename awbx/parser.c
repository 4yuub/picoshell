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

t_cmd_tree	*new_exec(void)
{
	t_exec_node	*res;

	res = malloc(sizeof(t_exec_node));
	if (!res)
		return (0x0);
	res->type = EXEC;
	res->tcmd = 0x0;
	res->cmd = 0x0;
	res->args = 0x0;
	res->targs = 0x0;
	res->args_count = 0;
	return ((t_cmd_tree *) res);
}

int herdoc(char *delim)
{
	int	p[2];
	char	*buffer;

	if (!delim || pipe(p) == -1)
		return (-1);
	while (1)
	{
		buffer = readline("herdoc : ");
		if (!buffer || ft_strcmp(buffer, delim))
			break;
		write(p[1], buffer, ft_strlen(buffer));
		write(p[1], "\n", 1);
		free(buffer);
	}
	close(p[1]);
	return (p[0]);
}

t_cmd_tree	*new_redir(t_parser_res *r, int type)
{
	t_redir_node	*res;

	res = malloc(sizeof(t_redir_node));
	if (!res)
		return (0x0);
	res->type = REDIR;
	res->sub = r->tree;
	res->tok = r->current;
	if (type == GREAT)
	{
		res->flag = O_CREAT | O_WRONLY | O_TRUNC;
		res->fd = 1;
		res->redir_type = GREAT;
	}
	else if (type == LESS)
	{
		res->flag = O_RDONLY;
		res->fd = 0;
		res->redir_type = LESS;
	}
	else if (type == APPEND)
	{
		res->flag = O_CREAT | O_WRONLY;
		res->fd = 1;
		res->redir_type = APPEND;
	}
	else if (type == HERDOC)
	{
		res->flag = O_RDONLY;
		res->fd = herdoc(r->current->value);
		res->redir_type = HERDOC;
	}
	return ((t_cmd_tree *) res);
}

t_parser_res	*parse_redir(t_parser_res *res)
{
	int type;

	while (res->current && (res->current->type == GREAT || res->current->type == LESS || res->current->type == APPEND || res->current->type == HERDOC))
	{
		type = res->current->type;
		res->current = get_token(res->current->next);
		res->tree = new_redir(res, type);
		res->current = get_token(res->current->next);
	}
	return (res);
}

t_parser_res	*parse_block(t_parser_res *parser)
{
	if (parser->current && parser->current->type == LPAR)
		parser->current = get_token(parser->current->next);
	parser = parse_and_or(parser);
	if (parser->current && parser->current->type == RPAR)
		parser->current = get_token(parser->current->next);
	else
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	parser = parse_redir(parser);
	return (parser);
}

t_parser_res	*add_args(t_parser_res *res, t_exec_node *cmd)
{
	while (res->current && (res->current->type == WORD || res->current->type == DQUOTE || res->current->type == QUOTE
		|| res->current->type == DOLLAR|| res->current->type == WILDCARD))
	{
		
		if (cmd->args_count == 0)
			cmd->targs = res->current;
		cmd->args_count += 1;
		res->current = get_token(res->current->next);
	}
	res = parse_redir(res);
	return (res);
}

t_parser_res	*on_error_exec(t_parser_res *res)
{
	if (!res->current)
	{
		g_minishell.on_error = 1;
		return (res);
	}
	return (res);
}

t_parser_res	*on_error_exec2(t_parser_res *res)
{
	if (!res->tree)
	{
		g_minishell.on_error = 1;
		return (res);
	}
	return (res);
}

t_parser_res	*parse_exec(t_parser_res *res)
{
	t_exec_node	*cmd;

	res = on_error_exec(res);
	if (g_minishell.on_error == 1)
		return (res);
	if (res->current->type == LPAR)
		return (parse_block(res));
	res->tree = new_exec();
	res = on_error_exec2(res);
	if (g_minishell.on_error == 1)
		return (res);
	cmd = (t_exec_node *) res->tree;
	res = parse_redir(res);
	if ( res->current && (res->current->type == WORD ||
				res->current->type == DQUOTE || res->current->type == QUOTE ||
				res->current->type == DOLLAR|| res->current->type == WILDCARD))
	{
		cmd->tcmd = res->current;
		if (res->current)
			res->current = get_token(res->current->next);
		res = add_args(res, cmd);
	}
	return (res);
}

t_cmd_tree	*new_pipe(t_cmd_tree *left, t_cmd_tree *right)
{
	t_pipe_node	*res;

	if (!left || !right)
		return (0x0);
	res = malloc(sizeof(t_pipe_node));
	if (!res)
		return (0x0);
	res->type = PI;
	res->left = left;
	res->right = right;
	return ((t_cmd_tree *) res);
}

t_cmd_tree	*new_and(t_cmd_tree *left, t_cmd_tree *right)
{
	t_pipe_node	*res;

	if (!left || !right)
		return (0x0);
	res = malloc(sizeof(t_and_node));
	if (!res)
		return (0x0);
	res->type = ANDD;
	res->left = left;
	res->right = right;
	return ((t_cmd_tree *) res);
}

t_cmd_tree	*new_or(t_cmd_tree *left, t_cmd_tree *right)
{
	t_pipe_node	*res;

	if (!left || !right)
		return (0x0);
	res = malloc(sizeof(t_or_node));
	if (!res)
		return (0x0);
	res->type = ORR;
	res->left = left;
	res->right = right;
	return ((t_cmd_tree *) res);
}


t_parser_res	*on_error_pipe(t_parser_res *parser, t_cmd_tree **a)
{
	t_parser_res	*t1;

	if (!parser || !parser->current)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	t1 = parse_exec(parser);
	if (!t1->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	*a = t1->tree;
	if (!parser || !parser->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	return (parser);
}

t_parser_res	*parse_pipe(t_parser_res *parser)
{
	t_cmd_tree			*a;
	t_cmd_tree			*b;
	t_parser_res		*t2;

	parser = on_error_pipe(parser, &a);
	if (g_minishell.on_error == 1)
		return (parser);
	while (parser->current && parser->current->type == PIPE)
	{
		parser->current = get_token(parser->current->next);
		t2 = parse_exec(parser);
		if (!t2 || !t2->tree)
		{
			g_minishell.on_error = 1;
			return (parser);
		}
		b = t2->tree;
		a = new_pipe(a, b);
		if (parser->current && parser->current->type == WSPACE)
			parser->current = parser->current->next;
		else if (!parser->current)
			break;
	}
	parser->tree = a;
	return (parser);
}

t_parser_res	*on_error_and_or(t_parser_res	*parser, t_cmd_tree **a)
{
	t_parser_res	*t1;

	if (!parser || !parser->current)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	t1 = parse_pipe(parser);
	if (!t1->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	*a = t1->tree;
	if (!parser || !parser->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	return (parser);
}

t_parser_res	*parse_cmd(t_parser_res *parser)
{
	parser = parse_and_or(parser);
	if (parser->current && parser->current->type == WSPACE)
		parser->current = parser->current->next;
	if (parser->current)
		g_minishell.on_error = 1;
	return (parser);
}

t_parser_res	*parse_and(t_parser_res *parser, t_cmd_tree **a, t_cmd_tree **b)
{
	t_parser_res	*t2;

	parser->current = get_token(parser->current->next);
	t2 = parse_pipe(parser);
	if (!t2 || !t2->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	*b = t2->tree;
		*a = new_and(*a, *b);
	return (parser);
}

t_parser_res	*parse_or(t_parser_res *parser, t_cmd_tree **a, t_cmd_tree **b)
{
	t_parser_res	*t2;

	parser->current = get_token(parser->current->next);
	t2 = parse_pipe(parser);
	if (!t2 || !t2->tree)
	{
		g_minishell.on_error = 1;
		return (parser);
	}
	*b = t2->tree;
		*a = new_or(*a, *b);
	return (parser);
}

t_parser_res	*parse_and_or(t_parser_res	*parser)
{
	t_cmd_tree			*a;
	t_cmd_tree			*b;
	int					type;

	parser = on_error_and_or(parser, &a);
	if (g_minishell.on_error == 1)
		return (parser);
	while (parser->current && (parser->current->type == AND || parser->current->type == OR))
	{
		type = parser->current->type;
		if (type == AND)
			parser = parse_and(parser, &a, &b);
		else
			parser = parse_or(parser, &a, &b);
		if (g_minishell.on_error == 1)
			return (parser);
		if (parser->current && parser->current->type == WSPACE)
			parser->current = parser->current->next;
		else if (!parser->current)
			break;
	}
	parser->tree = a;
	return (parser);
}
