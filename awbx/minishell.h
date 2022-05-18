/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:54:10 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 09:54:10 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
typedef enum
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
}	types;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int							type;
	char						*value;
	struct	s_token *next;
	struct	s_token	*prev;
} t_token;

	/*	str_utils	*/
char	*ft_strdup(char *s);
char	*ft_strndup(const char *str, int size);
int		ft_strlen(char *str);
int		not_in(char c, char *str);

	/*	tokenizer_utils	*/
void	drop_tokens(t_token **tokens);
int		is_space(char *line, t_token **tokens);
int		is_great(char *line, t_token **tokens);
int		is_less(char *line, t_token **tokens);
int		is_quote(char *line, t_token **tokens);
int		is_dquote(char *line, t_token **tokens);
int		is_dollar(char *line, t_token **tokens);
int		is_pipe(char *line, t_token **tokens);
int		is_and(char *line, t_token **tokens);
int		is_wildcard(char *line, t_token **tokens);
int		is_lparen(char *line, t_token **tokens);
int		is_rparen(char *line, t_token **tokens);
int		is_word(char *line, t_token **tokens);
t_token	*create_token(int type, char *value);
t_token *get_token(t_token **tokens, int i);
void		drop_token(t_token *token);


	/*	env	*/
void get_env_list(t_env **env, char **envp);

	/*	tokenizer	*/
int tokenize(t_token **tokens, char *line);

	/*	lists	*/
void	push_back(t_token **tokens, t_token *token);

	/*	sanitizer	*/
int		sanitize_quote(t_token **tokens);
