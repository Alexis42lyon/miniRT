/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:25:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/10 15:39:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include <stdio.h>

int	in_light(t_scene *scene, t_hit hit, t_vec3 light_dir)
{
	t_hit	light_hit;
	t_ray	ray;

	ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
	ray.dir = vec3_mult(light_dir, -1);
	light_hit = trace_ray(ray, scene);
	return (light_hit.distance == -1);
}

struct light_info	new_info(t_scene *scene, t_hit hit, t_mat mat, t_ray ray)
{
	struct light_info	info;

	info.light = scene->light;
	info.ray = ray;
	info.hit = hit;
	info.mat = mat;
	info.light_dir = vec3_sub(hit.point, scene->light.origin);
	info.attenuation = LIGHT_RANGE / vec3_lenght(info.light_dir);
	if (info.attenuation < 0)
		info.attenuation = 0;
	info.light_dir = vec3_normalize(info.light_dir);
	return (info);
}

t_vec3	phong_shading(t_scene *scene, t_hit hit, t_mat mat, t_ray ray)
{
	t_vec3				ambient;
	t_vec3				diffuse;
	t_vec3				specular;
	t_vec3				merged_pass;
	struct light_info	info;

	ambient = vec3_zero();
	diffuse = vec3_zero();
	specular = vec3_zero();
	scene->vp_flags = DIFFUSE | AMBIENT | SPECULAR;
	info = new_info(scene, hit, mat, ray);
	ambient = phong_ambient(scene, info.mat);
	if (in_light(scene, hit, info.light_dir))
	{
		diffuse = phong_diffuse(info);
		specular = phong_specular(info);
	}
	merged_pass = vec3_zero();
	if (scene->vp_flags & AMBIENT)
		merged_pass = vec3_add(merged_pass, ambient);
	if (scene->vp_flags & DIFFUSE)
		merged_pass = vec3_add(merged_pass, diffuse);
	if (scene->vp_flags & SPECULAR)
		merged_pass = vec3_add(merged_pass, specular);
	return (merged_pass);
}
