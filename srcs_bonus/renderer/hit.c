/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:20:05 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/02 16:10:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_hit	hit_succes2(t_scene *scene, t_ray ray,
	t_hit hit, enum e_object_type type)
{
	if (type == CYLINDER)
	{
		hit = hit_result(scene->cylinders[hit.obj_index].origin, ray,
				hit.distance, hit.obj_index);
		hit.normal = cylinder_normal(scene->cylinders[hit.obj_index],
				hit.point);
		hit.mat = scene->materials[scene->cylinders[hit.obj_index].mat_idx];
	}
	else if (type == CONE)
	{
		hit = hit_result(scene->cones[hit.obj_index].origin, ray,
				hit.distance, hit.obj_index);
		hit.normal = cone_normal(scene->cones[hit.obj_index],
				hit.point);
		hit.mat = scene->materials[scene->cones[hit.obj_index].mat_idx];
	}
	return (hit);
}

t_hit	hit_succes(t_scene *scene, t_ray ray, t_hit hit)
{
	enum e_object_type	type;

	type = hit.type;
	if (type == SPHERE)
	{
		hit = hit_result(scene->spheres[hit.obj_index].origin,
				ray, hit.distance, hit.obj_index);
		hit.mat = scene->materials[scene->spheres[hit.obj_index].mat_idx];
	}
	else if (type == PLANE)
	{
		hit = hit_result(scene->planes[hit.obj_index].origin, ray,
				hit.distance, hit.obj_index);
		if (ft_dot(ray.dir, scene->planes[hit.obj_index].normal) > 0)
			hit.normal = vec3_mult(scene->planes[hit.obj_index].normal, -1.0);
		else
			hit.normal = scene->planes[hit.obj_index].normal;
		hit.mat = scene->materials[scene->planes[hit.obj_index].mat_idx];
	}
	else
		hit = hit_succes2(scene, ray, hit, type);
	hit.type = type;
	return (hit);
}
