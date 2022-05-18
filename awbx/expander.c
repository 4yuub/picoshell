/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:41:35 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 15:41:35 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expande(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	t_token	*ret;
	int			i;
	t_token	*tmp2;

	tmp = *tokens;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->type == QUOTE)
		{
			drop_token(get_token(tokens, i));
			if (!sanitize_quote(&tmp2))
			{
				drop_tokens(tokens); // add a message variable
				return (0);
			}
		}
		tmp = tmp2;
		i += 1;
	}
	return (1);
}
