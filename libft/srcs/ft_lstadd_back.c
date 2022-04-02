/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 01:30:34 by anremiki          #+#    #+#             */
/*   Updated: 2021/09/25 01:47:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			ptr = ft_lstlast(*alst);
			ptr->next = new;
		}	
	}
}
