/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:07:15 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/16 20:07:15 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sanitize_quote(t_token **tokens)
{
	t_token	*tmp;
	t_token *arr;
	int			i;
	t_token *tmp2;

	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->type == QUOTE)
		{
			drop_token(get_token(tokens, i));
			return (1);
		}
		push_back(&arr, tmp);
		tmp = tmp2;
		i += 1;
	}
	return (0);
}

