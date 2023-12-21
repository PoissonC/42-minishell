/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:24:47 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/14 17:52:16 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	fill_mark(int *mark, char *str, char *charset)
{
	int	num;
	int	i;
	int	j;

	if (ft_strlen(str) == 0 || !mark)
		return (-1);
	num = 0;
	i = 0;
	mark[num++] = -1;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
				mark[num++] = i;
			j++;
		}
		i++;
	}
	mark[num] = ft_strlen(str);
	return (num);
}

static void	memory_alloc(int *mark, char ***ans, char *str, int num)
{
	int	i;
	int	j;

	i = 0;
	(*ans) = (char **)malloc(sizeof(char *) * (num + 1));
	if (!(*ans))
		return ;
	j = 0;
	(*ans)[j] = 0;
	while (i < num)
	{
		if (mark[i + 1] - mark[i] > 1)
		{
			(*ans)[j] = (char *)malloc(mark[i + 1] - mark[i]);
			if (!(*ans)[j])
				return ;
			ft_strncpy((*ans)[j], str + mark[i] + 1, mark[i + 1] - mark[i] - 1);
			j++;
			(*ans)[j] = 0;
		}
		i++;
	}
}

char	**ft_strtok(char *str, char *charset)
{
	char	**ans;
	int		*mark;
	int		num;

	mark = (int *)malloc(sizeof(int) * (ft_strlen(str) + 2));
	if (!mark)
		return (0);
	num = fill_mark(mark, str, charset);
	if (num == -1)
	{
		ans = (char **)malloc(sizeof(char *));
		ans[0] = 0;
		free(mark);
		return (ans);
	}
	memory_alloc(mark, &ans, str, num);
	free(mark);
	return (ans);
}
