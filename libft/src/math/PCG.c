/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PCG.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:12:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/01 09:38:58 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft/math.h"

uint	PCG_Hash(uint input)
{
	uint state = input * 747796405u + 2891336453u;
	uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}

float	PCG_Hash_range(uint range, uint input)
{
	uint state = input * 747796405u + 2891336453u;
	uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return (((float)((float)((word >> 22u) ^ word)/ (float)2147483647) - 1) * range);
}
