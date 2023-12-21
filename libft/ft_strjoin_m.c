/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:48 by yu                #+#    #+#             */
/*   Updated: 2023/12/14 15:04:36 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_m(char **strarr, t_list *mem)
{
	char	*new;
	int		i;
	int		j;
	int		size;

	if (!strarr)
		return (NULL);
	size = 1;
	i = 0;
	while (strarr[i])
		size += ft_strlen(strarr[i++]);
	new = ft_malloc(size, mem);
	if (!new)
		return (NULL);
	size = 0;
	i = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j])
			new[size++] = strarr[i][j++];
		i++;
	}
	return (new);
}
