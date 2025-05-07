/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:17:10 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 08:56:01 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

double	plane_hit(void *p_plane, const t_ray ray)
{
	t_vec3	oc;
	double	denominator;
	double	res;
	t_plane	*plane;

	plane = (t_plane *)p_plane;
	denominator = ft_dot(plane->normal, ray.dir);
	if (fabs(denominator) < 1e-6)
		return (-1);
	oc = vec3_sub(plane->origin, ray.origin);
	res = ft_dot(oc, plane->normal) / denominator;
	if (res >= 0)
		return (res);
	return (-1);
}
