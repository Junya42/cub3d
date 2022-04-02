/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:11:09 by anremiki          #+#    #+#             */
/*   Updated: 2021/09/24 22:19:13 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	j;

	j = ft_strlen(s);
	if (c == 0)
		return ((char *)&s[j]);
	while (j--)
		if (s[j] == c)
			return ((char *)&s[j]);
	return (NULL);
}
