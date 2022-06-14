/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:56:18 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/05/15 09:56:18 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
static char	*ft_join(const char *s1, const char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!(join))
		return (NULL);
	while (s1[i])
	{
		join[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		join[j] = s2[i];
		j++;
		i++;
	}
	join[j] = '\0';
	return (join);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup((char *) s2));
	if (s2 == NULL)
		return (ft_strdup((char *) s1));
	return (ft_join(s1, s2));
}
int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i += 1;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char ) * (ft_strlen(s1) + 1));
	if (!s2)
		return (0x0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strndup(const char *str, int size)
{
	char *s;
	int i;

	i = 0;
	s = (char *)malloc(sizeof(char) * (size + 1));
	while (str[i] != '\0' && i < size)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int not_in(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}
