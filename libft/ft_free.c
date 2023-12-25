/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:15:11 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 22:00:08 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *ptr, t_list *mem)
{
	t_list	*prev;

	if (!mem || !ptr)
		return ;
	prev = mem;
	mem = mem->next;
	while (mem)
	{
		if (mem->content == ptr)
		{
			prev->next = mem->next;
			ft_lstdelone(mem, &free);
			break ;
		}
		prev = mem;
		mem = mem->next;
	}
}

void	ft_free_all(t_list *mem)
{
	if (!mem)
		return ;
	ft_lstclear(&mem->next, &free);
}
