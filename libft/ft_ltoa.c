/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:07:36 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/26 17:32:09 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_arr(char **str, long long n, int idx)
{
	if (n == LLONG_MIN)
	{
		ft_strlcpy(*str, "-9223372036854775808", 21);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		(*str)[0] = '-';
	}
	if (n >= 10)
	{
		put_arr(str, n / 10, idx - 1);
	}
	(*str)[idx] = '0' + (n % 10);
}

static int	get_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	if (digits == 0)
		digits++;
	return (digits);
}

char	*ft_ltoa(long long n)
{
	long long	digits;
	char		*ans;

	digits = get_digits(n);
	ans = malloc(digits + 1);
	if (!ans)
		return (0);
	ans[digits] = 0;
	put_arr(&ans, n, digits - 1);
	return (ans);
}
