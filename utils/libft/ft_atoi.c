/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:30:35 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 13:29:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	skip_ws(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	unsigned long long	max;
	int					i;
	int					sign;

	result = 0;
	max = 922337203685477580;
	sign = 1;
	i = skip_ws(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((result > max || (result == max && str[i] - '0' > 7)) && sign == 1)
			return (-1);
		if ((result > max || (result == max && str[i] - '0' > 8)) && sign == -1)
			return (0);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
