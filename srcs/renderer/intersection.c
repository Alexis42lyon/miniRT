/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 13:23:53 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "miniRT.h"
#include "raytracer.h"
#include <limits.h>

t_hit	hit_succes(t_scene *scene, t_ray ray, t_hit hit)
{
	enum e_object_type	type;

	type = hit.type;
	if (type == SPHERE)
		hit = hit_result(scene->spheres[hit.obj_index].origin,
				ray, hit.distance, hit.obj_index);
	else if (type == PLANE)
	{
		hit = hit_result(scene->planes[hit.obj_index].origin,
				ray, hit.distance, hit.obj_index);
		hit.normal = scene->planes[hit.obj_index].normal;
	}
	else if (type == CYLINDER)
	{
		hit = hit_result(scene->cylinders[hit.obj_index].origin, ray,
				hit.distance, hit.obj_index);
		hit.normal = cylinder_normal(scene->cylinders[hit.obj_index],
				hit.point);
	}
	hit.type = type;
	return (hit);
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

t_hit	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	t_hit	tmp_hit;

	hit = get_min_dist(sphere_hit, ray, (struct s_objs_data)
		{scene->spheres, scene->nb_spheres, sizeof(t_sphere)});
	hit.type = SPHERE;
	tmp_hit = get_min_dist(plane_hit, ray, (struct s_objs_data)
		{scene->planes, scene->nb_planes, sizeof(t_plane)});
	if (tmp_hit.distance != -1 && tmp_hit.distance < hit.distance)
	{
		hit = tmp_hit;
		hit.type = PLANE;
	}
	tmp_hit = get_min_dist(cylinders_hit, ray, (struct s_objs_data)
		{scene->cylinders, scene->nb_cylinders, sizeof(t_cylinder)});
	if (tmp_hit.distance != -1 && tmp_hit.distance < hit.distance)
	{
		hit = tmp_hit;
		hit.type = CYLINDER;
	}
	if (hit.obj_index != (size_t)-1)
		return (hit_succes(scene, ray, hit));
	return (hit_fail());
}
