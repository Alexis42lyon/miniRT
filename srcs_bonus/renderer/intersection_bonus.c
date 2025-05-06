/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 14:03:30 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "miniRT.h_bonus.h"
#include "raytracer_bonus.h"
#include <limits.h>
#include <stdio.h>

t_vec3	cone_normal(t_cylinder co, t_vec3 hit_point)
{
	t_vec3	axis;
	t_vec3	cp;
	double	dist;
	t_vec3	base_center;
	t_vec3	to_hit;

	axis = vec3_normalize(co.normal);
	cp = vec3_sub(hit_point, co.origin);
	base_center = vec3_add(co.origin, vec3_mult(axis, co.height));
	to_hit = vec3_sub(hit_point, base_center);
	dist = ft_dot(to_hit, axis);
	if (fabs(dist) < 1e-6)
		return (axis);
	return (vec3_normalize(vec3_sub(cp,
				vec3_mult(axis, ft_dot(cp, axis)
					* (1.0 + (co.radius * co.radius)
						/ (co.height * co.height))))));
}

t_vec3	cylinder_normal(t_cylinder cy, t_vec3 hit_point)
{
	t_vec3	cp;
	double	projection;

	cp = vec3_sub(hit_point, cy.origin);
	projection = ft_dot(cp, cy.normal);
	if (fabs(projection) < 1e-6)
		return (vec3_mult(cy.normal, -1.0));
	if (fabs(ft_dot(vec3_sub(hit_point, vec3_add(cy.origin,
						vec3_mult(cy.normal, cy.height))), cy.normal)) < 1e-6)
		return (cy.normal);
	return (vec3_normalize(vec3_sub(cp, vec3_mult(cy.normal, projection))));
}

t_hit	get_min_dist(double (*f)(void*, t_ray), t_ray ray,
		struct s_objs_data data)
{
	size_t	i;
	double	dist;
	t_hit	hit;

	i = 0;
	hit.distance = INT_MAX;
	hit.obj_index = -1;
	while (i < data.n_obj)
	{
		dist = f((char *)data.objs + (i * data.size), ray);
		if (dist > 0 && dist < hit.distance)
		{
			hit.distance = dist;
			hit.obj_index = i;
		}
		i++;
	}
	return (hit);
}

int	is_closest(t_hit hit, t_hit new_hit, t_ray ray)
{
	return (new_hit.distance != -1
		&& new_hit.distance < hit.distance
		&& new_hit.distance < ray.length
	);
}
