/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:53:20 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/09 15:23:33 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
typedef enum
{
	SPACE,
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
}	types;

typedef enum
{
	REDIR_IN,
	REDIR_OUT,
}	nodes;

typedef struct s_tuple
{
	char	*key;
	char	*value;
}	t_tuple;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_token
{
	int			type;
	char		*value;
	struct	s_token *next;
} t_token;

typedef struct s_cmd_tree
{
	int type;
} t_cmd_tree;

typedef struct s_redirnode
{
	int type;
	t_cmd_tree *sub_node;
	int fd;
	int mode;
} t_redirnode;

int			ft_strlen(char *str);
int			not_in(char c, char *str);
char		*ft_strdup(char *src);
char		*ft_strndup(const char *str, int size);
void		tokenize(char *line, t_token **tokens);
t_token	*create_token(int type, char *value);
void 		drop_tokens_err(t_token **tokens);
int			is_pipe(char *line, t_token **tokens);
int			is_and(char *line, t_token **tokens);
int			is_wildcard(char *line, t_token **tokens);
int			is_lparen(char *line, t_token **tokens);
int			is_rparen(char *line, t_token **tokens);
int			is_less(char *line, t_token **tokens);
int			is_dquote(char *line, t_token **tokens);
int			is_word(char *line, t_token **tokens);
int			is_dollar(char *line, t_token **tokens);
int			is_space(char *line, t_token **tokens);
int			is_great(char *line, t_token **tokens);
int			is_quote(char *line, t_token **tokens);
void		print_tokens(t_token *tokens);
void		push_back(t_token **head, t_token *token);
void		get_env_list(t_env **env_list, char **env);
