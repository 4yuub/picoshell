/* **************************************************************************
 * */
/*                                                                            */
/*                                                        :::      ::::::::
 *                                                        */
/*   main.c                                             :+:      :+:    :+:
 *   */
/*                                                    +:+ +:+         +:+
 *                                                    */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:53:14 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:49 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char		*cmd;
	t_token	*tokens;
	t_env		*env_list;

	(void) ac;
	(void) av;
	tokens = 0x0;
	env_list = 0x0;
	get_env_list(&env_list, env);
	while (1)
	{
		cmd = readline("awbx$ "); // to be freed
		if (!cmd)
			break ;
		tokenize(cmd, &tokens); // to be freed
		free(cmd);
		//expande(tokens, env); // to be freed
		print_tokens(tokens);
		//parse(&tokens);
		//drop tokens 
		tokens = 0x0;
	}
}
