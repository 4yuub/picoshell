/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nature3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:16:32 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:53 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *line, t_token **tokens)
{
	int	i;

	if (!*line)
		return (0);
	i = 0;
	while (line[i] == ' ')
		i += 1;
	push_back(tokens, create_token(SPACE, ft_strdup(" "))); // to be freed
	return (i);
}

int	is_great(char *line, t_token **tokens)
{
	int	i;

	if (!*line)
		return (0);
	i = 0;
	if (line[i + 1] == '>')
	{
		push_back(tokens, create_token(APPEND, ft_strdup(">>"))); // to be freed
		return (2);
	}
	push_back(tokens, create_token(GREAT, ft_strdup(">"))); // to be freed
	return (1);
}

