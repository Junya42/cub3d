/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstback_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:16:14 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:53:56 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstback_dup(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstdupnew(content);
		if (!new)
			return ;
		ft_lstadd_back(alst, new);
	}
}

void	ft_lstback_ptr(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstnew(content);
		if (!new)
			return ;
		ft_lstadd_back(alst, new);
	}
}
