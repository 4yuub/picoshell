/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:53:37 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 09:53:37 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_index(char *env_var, char to_find)
{
	int	i;

	i = 0;
	if (!env_var)
		return (-1);
	while (env_var[i])
	{
		if (env_var[i] == to_find)
			return (i);
		i += 1;
	}
	return (-1);
}

char	*get_key(char *envp, int index)
{
	char	*key;
	int		i;

	key = malloc(sizeof(char) * (index + 1));
	if (!key)
		return (0x0);
	i = 0;
	while (i < index && envp[i])
	{
		key[i] = envp[i];
		i += 1;
	}
	key[i] = '\0';
	return (key);
}

char *get_value(char *envp, int index)
{
	char	*value;
	int	i;

	value = malloc(sizeof(char) * (ft_strlen(envp) - index));
	if (!value)
		return (0x0);
	i = 0;
	while (envp[index + i])
	{
		value[i] = envp[index + i];
		i += 1;
	}
	value[i] = '\0';
	return (value);
}

void add_env(t_env **env, t_env *new)
{
	t_env *tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void get_env_list(t_env **env, char **envp)
{
	int			i;
	char		*key;
	char		*value;
	t_env		*new;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i], get_index(envp[i], '=')); // to be freed
		value = get_value(envp[i], get_index(envp[i], '=') + 1); // to be freed
		new = malloc(sizeof(t_env));	// to be freed
		if (!new)
			return ;
		new->key = key;
		new->value = value;
		new->next = 0x0;
		add_env(env, new);
		i += 1;
	}
}
