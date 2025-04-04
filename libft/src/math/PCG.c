/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PCG.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:12:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/04 11:19:55 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include <limits.h>

uint	pcg_hash(uint input)
{
	uint state = input * 747796405u + 2891336453u;
	uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}

float	random_float(uint input)
{
	return ((float)pcg_hash(input) / 4294967296.0f) - 0.5f;
}
