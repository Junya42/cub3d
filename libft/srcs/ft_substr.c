/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:30:50 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:35:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = -1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str || !s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	while (s[++i + start] && i < len)
		str[i] = s[i + start];
	str[i] = '\0';
	return (str);
}
