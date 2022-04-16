/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:06:46 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:35:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_lstsplit(t_list **lst)
{
	char	**res;
	t_list	*ptr;
	int		size;
	int		i;

	ptr = *lst;
	i = -1;
	size = ft_lstsize(ptr);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	while (++i < size)
	{
		res[i] = ptr->content;
		if (!res[i])
			return (NULL);
		ptr = ptr->next;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_lstsplit_dup(t_list **lst)
{
	char	**res;
	t_list	*ptr;
	int		size;
	int		i;

	ptr = *lst;
	i = -1;
	size = ft_lstsize(ptr);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	while (++i < size)
	{
		res[i] = ft_strdup(ptr->content);
		if (!res[i])
			return (NULL);
		ptr = ptr->next;
	}
	res[i] = NULL;
	return (res);
}
