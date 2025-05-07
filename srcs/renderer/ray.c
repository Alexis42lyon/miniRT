/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 08:56:22 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3	ray_to_vec(t_ray r)
{
	return (vec3_add(r.origin, vec3_mult(r.dir, r.length)));
}

t_ray	get_ray(float u, float v, t_viewport vp)
{
	t_ray	ray;
	t_vec3	px_center;

	px_center = vec3_add(vp.px_up_left,
			vec3_add(vec3_mult(vp.horizontal, u), vec3_mult(vp.vertical, v)));
	ray.origin = vp.cam->origin;
	ray.dir = vec3_normalize(vec3_sub(px_center, ray.origin));
	return (ray);
}

t_hit	hit_fail(void)
{
	return ((t_hit){
		{0, 0, 0},
		{0, 0, 0},
		-1,
		-1,
		NONE,
	});
}
