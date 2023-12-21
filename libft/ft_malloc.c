/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:09:38 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/08 16:18:33 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size, t_list *mem)
{
	void	*new;
	t_list	*tail;

	new = malloc(size);
	if (!new)
	{
		ft_free_all(mem);
		return (NULL);
	}
	tail = ft_lstlast(mem);
	tail->next = ft_lstnew(new);
	return (new);
}
