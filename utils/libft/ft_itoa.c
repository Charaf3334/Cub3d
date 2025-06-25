/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:47:11 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/25 09:54:46 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*if_zero(void)
{
	char	*str;

	str = (char *)malloc(2);
	if (str)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}

static char	*populate_str(char *str, long long num, int len)
{
	int	sign;

	sign = 0;
	if (num < 0)
	{
		sign = 1;
		num = -num;
	}
	str[len--] = '\0';
	while (num)
	{
		str[len--] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		str[len] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long long	tmp;
	int			len;
	char		*str;

	if (n == 0)
		return (if_zero());
	len = 0;
	tmp = n;
	if (n < 0)
	{
		len = 1;
		tmp = -tmp;
	}
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	return (populate_str(str, n, len));
}
