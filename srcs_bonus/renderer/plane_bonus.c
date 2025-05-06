/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:17:10 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"
#include "libft/vector.h"
#include <stdio.h>

double	plane_hit(void *p_plane, const t_ray ray)
{
	t_vec3	oc;
	double	denominator;
	double	res;
	t_plane	*plane;

	plane = (t_plane *)p_plane;
	denominator = ft_dot(plane->normal, ray.dir);
	if (fabs(denominator) < 1e-6)
		return (-1.0);
	oc = vec3_sub(plane->origin, ray.origin);
	res = ft_dot(oc, plane->normal) / denominator;
	if (res >= 1e-3)
		return (res);
	return (-1);
}
