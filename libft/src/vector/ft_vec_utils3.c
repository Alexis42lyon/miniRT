/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:49:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 08:49:54 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "libft/math.h"

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
