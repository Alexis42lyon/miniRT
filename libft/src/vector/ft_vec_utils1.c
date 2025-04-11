/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:47:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 08:49:33 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/vector.h"

inline t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline t_vec3	vec3_divide(const t_vec3 v1, const double d)
{
	return ((t_vec3){v1.x / d, v1.y / d, v1.z / d});
}

inline t_vec3	vec3_mult(const t_vec3 v1, const double d)
{
	return ((t_vec3){v1.x * d, v1.y * d, v1.z * d});
}

inline t_vec3	vec3_multv(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

inline t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}
