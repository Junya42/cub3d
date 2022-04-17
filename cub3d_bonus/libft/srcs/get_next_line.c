/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:11:36 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:35:46 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_check_eol(char *memory, int fd, int len)
{
	char	*buffer;
	int		eob;
	int		a;

	eob = 1;
	a = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!gl_strchr(memory, '\n', (a - eob)) && eob)
	{
		eob = read(fd, buffer, BUFFER_SIZE);
		if (eob == -1)
		{
			free(buffer);
			return (NULL);
		}
		a += eob;
		buffer[eob] = '\0';
		memory = gl_strjoin(memory, buffer, (len + a), -1);
	}
	free(buffer);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory = ft_check_eol(memory, fd, gl_strlen(memory));
	if (!memory)
	{
		free(memory);
		return (NULL);
	}
	line = gl_get_line(memory);
	memory = gl_update_memory(memory, gl_strlen(memory));
	return (line);
}
