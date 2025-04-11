/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:49:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 08:50:22 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include <math.h>

inline double	vec3_lenght(const t_vec3 vec)
{
	return (sqrt(vec3_lenght_square(vec)));
}

inline double	vec3_lenght_square(const t_vec3 vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

inline t_vec3	vec3_normalize(const t_vec3 v)
{
	if (vec3_lenght_square(v) == 0)
		return (vec3_zero());
	return (vec3_divide(v, vec3_lenght(v)));
}

inline float	ft_dot(const t_vec3 v1, const t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

inline t_vec3	vec3_reflect(const t_vec3 vec, const t_vec3 n)
{
	return (vec3_sub(vec, vec3_mult(n, 2 * ft_dot(vec, n))));
}
