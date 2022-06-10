/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:54:10 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/06/07 18:38:05 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>

typedef enum e_tokens
{
	WSPACE,
	APPEND,
	GREAT,
	LESS,
	HERDOC,
	QUOTE,
	DQUOTE,
	DOLLAR,
	PIPE,
	OR,
	RET,
	AND,
	UNHANDLED,
	WILDCARD,
	LPAR,
	RPAR,
	WORD,
}	t_types;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell
{
	int exit_status;
}	t_minishell;

extern t_minishell g_minishell;

typedef enum e_nodes
{
	REDIR,
	EXEC,
	PI,
}	t_nodes;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_tree
{
	int	type;
}t_cmd_tree;

typedef struct s_redir_node
{
	int			type;
	t_cmd_tree	*sub;
	t_token		*tok;
	int			flag;
	int			fd;
}	t_redir_node;

typedef struct s_pipe_node
{
	int			type;
	t_cmd_tree	*left;
	t_cmd_tree	*right;
}	t_pipe_node;

typedef struct s_parser_res
{
	t_token	*current;
	t_cmd_tree	*tree;
}	t_parser_res;

typedef struct s_exec_node
{
	int		type;
	t_token	*tcmd;
	char	*cmd;
	char	**args;
	t_token	*targs;
}	t_exec_node;
	/*	str_utils	*/
char		*ft_strdup(char *s);
char		*ft_strndup(const char *str, int size);
int			ft_strlen(char *str);
int			not_in(char c, char *str);
int			ft_strcmp(char *s1, char *s2);
	/*	tokenizer_utils	*/
void		drop_tokens(t_token **tokens);
int			is_space(char *line, t_token **tokens);
int			is_great(char *line, t_token **tokens);
int			is_less(char *line, t_token **tokens);
int			is_quote(char *line, t_token **tokens);
int			is_dquote(char *line, t_token **tokens);
int			is_dollar(char *line, t_token **tokens);
int			is_pipe(char *line, t_token **tokens);
int			is_and(char *line, t_token **tokens);
int			is_wildcard(char *line, t_token **tokens);
int			is_lparen(char *line, t_token **tokens);
int			is_rparen(char *line, t_token **tokens);
int			is_word(char *line, t_token **tokens);
t_token		*create_token(int type, char *value);
t_token		*get_token(t_token *tokens);
void		drop_token(t_token *token);
int			has_redirections(t_token *tokens);
int			peek(t_token *tokens, int type);
	/*	env	*/
void		get_env_list(t_env **env, char **envp);

	/*	tokenizer	*/
int			tokenize(t_token **tokens, char *line);

	/*	lists	*/
void		push_back(t_token **tokens, t_token *token);

	/*	sanitizer	*/
int			sanitize_quote(t_token **tokens);

	/*	parser	*/
t_parser_res	*parse_redir(t_parser_res *ret);
t_parser_res	*parse_exec(t_parser_res *tokens);
t_cmd_tree	*parse_pipe(t_token	*tokens);
#endif
