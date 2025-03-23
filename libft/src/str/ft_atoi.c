/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:28:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/23 20:28:51 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		res = res * 10 + *nptr++ - '0';
		if (res * sign != (int)(res * sign))
			return (-1);
	}
	return (res * sign);
}

double	ft_atof(const char *nptr)
{
	double	res;
	double	fraction;

	res = ft_atoi(nptr);
	fraction = 0.1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nptr++;
	if (*nptr++ == '.')
	{
		while (*nptr >= '0' && *nptr <= '9')
		{
			res += (*nptr - '0') * fraction;
			fraction *= 0.1;
			nptr++;
		}
	}
	return (res);
}
