/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PCG.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:12:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/08 16:54:11 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include <limits.h>

t_uint	pcg_hash(t_uint input)
{
	t_uint	state;
	t_uint	word;

	state = input * 747796405u + 2891336453u;
	word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}

float	random_float(t_uint input)
{
	return (((float)pcg_hash(input) / 4294967296.0f) - 0.5f);
}
