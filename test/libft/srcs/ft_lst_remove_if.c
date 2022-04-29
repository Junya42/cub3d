/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:55:57 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:54:57 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lst_remove_if(t_list **alst, char *content)
{
	t_list	*previous;
	t_list	*current;
	t_list	*ptr;

	previous = *alst;
	while (previous->next)
	{
		current = previous->next;
		if (ft_strstr(content, current->content) == 1)
		{
			ptr = current;
			current = current->next;
			previous->next = current;
			free(ptr);
			return ;
		}
		previous = previous->next;
	}
}
