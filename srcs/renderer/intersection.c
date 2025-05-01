/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/01 10:27:44 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "miniRT.h"
#include "raytracer.h"
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

// t_hit	trace_ray(t_ray ray, t_scene *scene)
// {
// 	t_hit	hit;
// 	t_hit	tmp_hit;

// 	ft_bzero(&hit, sizeof(t_hit));
// 	hit.distance = 2147483648;
// 	hit.obj_index = -1;
// 	tmp_hit = get_min_dist(sphere_hit, ray, (struct s_objs_data)
// 		{scene->spheres, scene->nb_spheres, sizeof(t_sphere)});
// 	if (tmp_hit.distance != -1 && tmp_hit.distance < ray.length)
// 	{
// 		hit = tmp_hit;
// 		hit.type = SPHERE;
// 	}
// 	tmp_hit = get_min_dist(plane_hit, ray, (struct s_objs_data)
// 		{scene->planes, scene->nb_planes, sizeof(t_plane)});
// 	if (is_closest(hit, tmp_hit, ray))
// 	{
// 		hit = tmp_hit;
// 		hit.type = PLANE;
// 	}
// 	tmp_hit = get_min_dist(cylinders_hit, ray, (struct s_objs_data)
// 		{scene->cylinders, scene->nb_cylinders, sizeof(t_cylinder)});
// 	if (is_closest(hit, tmp_hit, ray))
// 	{
// 		hit = tmp_hit;
// 		hit.type = CYLINDER;
// 	}
// 	tmp_hit = get_min_dist(cone_hit, ray, (struct s_objs_data)
// 		{scene->cones, scene->nb_cones, sizeof(t_cylinder)});
// 	if (is_closest(hit, tmp_hit, ray))
// 	{
// 		hit = tmp_hit;
// 		hit.type = CONE;
// 	}
// 	if (hit.obj_index != (size_t) - 1)
// 		return (hit_succes(scene, ray, hit));
// 	return (hit_fail());
// }
