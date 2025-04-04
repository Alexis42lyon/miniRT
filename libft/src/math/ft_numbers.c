/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:00:07 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/04 08:54:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

float ft_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_clamp(float f, float min, float max)
{
	if (f < min)
		return (min);
	if (f > max)
		return (max);
	return (f);
}