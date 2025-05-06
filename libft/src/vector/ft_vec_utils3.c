/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:49:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/02 12:52:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "libft/math.h"
#include <math.h>

inline t_vec3	vec3_cross(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	});
}

inline t_vec3	vec3_clamp(const t_vec3 vec, double min, double max)
{
	return ((t_vec3){
		ft_clamp(vec.x, min, max),
		ft_clamp(vec.y, min, max),
		ft_clamp(vec.z, min, max)
	});
}

t_vec3	random_vec(t_uint seed)
{
	return ((t_vec3){
		random_float(seed ^ 0x1F1F1F1F),
		random_float(seed ^ 0x2E2E2E2E),
		random_float(seed ^ 0x3D3D3D3D)
	});
}

void	get_tangents(t_vec3 normal, t_vec3 *ref_tangent, t_vec3 *ref_bitangent)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	axis;

	axis = (t_vec3){0, 1, 0};
	if (fabsf(ft_dot(normal, axis)) > 0.999f)
		axis = (t_vec3){1, 0, 0};
	tangent = vec3_normalize(vec3_cross(axis, normal));
	bitangent = vec3_normalize(vec3_cross(normal, tangent));
	if (ref_tangent)
		*ref_tangent = tangent;
	if (ref_bitangent)
		*ref_bitangent = bitangent;
}
