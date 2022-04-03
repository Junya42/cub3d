/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 01:56:10 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:35:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*elem;
	t_list	*new;

	if (lst)
	{
		tmp = lst;
		new = ft_lstnew((*f)(tmp->content));
		if (new == NULL)
			return (NULL);
		tmp = tmp->next;
		while (tmp)
		{
			elem = ft_lstnew((*f)(tmp->content));
			if (elem == NULL)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, elem);
			tmp = tmp->next;
		}
		return (new);
	}
	return (NULL);
}
