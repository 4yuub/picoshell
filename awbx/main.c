/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:52:06 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 09:52:06 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char		*cmd;
	t_env		*env_list;
	t_token	*tokens;

	tokens = 0x0;
	env_list = 0x0;
	get_env_list(&env_list, env);
	while (1)
	{
		cmd = readline("awbx$ "); // to be freed
		if (!cmd)
			break ;
		if (!tokenize(&tokens, cmd))
			continue;
		if (!expande(&tokens, env_list))
			continue;
		print_tokens(tokens);
		printf("\n------\n");
		print_rev_tokens(tokens);
	}
}
