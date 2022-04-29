/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:56:28 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 16:50:16 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	fatal_error(char *str)
{
	write(STDERR, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

char	*ft_strndup(char *str, int limit)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (limit + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < limit)
		tmp[i] = str[i];
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

void	check_line(char *str)
{
	while (*str++)
		if (*(str - 1) == 32)
			*(str - 1) = 49;
}

int	close_fd(int fd, char *line, int i, int retvalue)
{
	if (fd)
		close(fd);
	if (!line[i])
		ft_printf("!No path were found in line\n");
	if (fd < 0)
		ft_printf("!Invalid file descriptor given by : %s\n", &line[i]);
	return (retvalue);
}
