#include "minishell.h"

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == SPACE)
			printf("[SPACE]\n");
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

