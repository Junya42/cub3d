/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfront_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:15:08 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:54:40 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstfront_dup(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstdupnew(content);
		if (!new)
			return ;
		ft_lstadd_front(alst, new);
	}
}

void	ft_lstfront_ptr(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstnew(content);
		if (!new)
			return ;
		ft_lstadd_front(alst, new);
	}
}
