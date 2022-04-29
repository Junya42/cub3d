/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:46:08 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:36:00 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	gl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gl_strjoin(char *s1, char *s2, int a, size_t j)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (a + 1));
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[++j])
		tmp[i + j] = s2[j];
	tmp[i + j] = '\0';
	free(s1);
	return (tmp);
}

char	*gl_get_line(char *s1)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s1[0])
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		tmp[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*gl_update_memory(char *s1, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (s1)
	{
		while (s1[i] && s1[i] != '\n')
			i++;
		if (!s1[i] || !s1[i + 1])
		{
			free(s1);
			return (NULL);
		}
		tmp = (char *)malloc(sizeof(char) * (len - i + 1));
		if (!tmp)
			return (NULL);
		j = i + 1;
		while (s1[++i])
			tmp[i - j] = s1[i];
		tmp[i - j] = '\0';
		free(s1);
		return (tmp);
	}
	return (NULL);
}

char	*gl_strchr(char *s, int c, int start)
{
	size_t	i;

	if (start == -1)
		start++;
	i = -1 + start;
	if (!s)
		return (NULL);
	while (s[++i])
		if (s[i] == c)
			return (&s[i]);
	return (NULL);
}
