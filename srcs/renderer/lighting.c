/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:25:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/22 09:27:41 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer.h"
#include "texture.h"
#include <stdio.h>

int	in_light(t_scene *scene, t_hit hit, t_vec3 light_dir)
{
	t_hit	light_hit;
	t_ray	ray;
	float	u, v;

	sp_coordinate_to_uv(hit.normal, &u, &v);
	// if (vec3_lenght_square(get_px(u, v, &scene->bump_map)) > 0.1)
	// 	return (0);

	ray.origin =vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
	ray.dir = vec3_mult(light_dir, -1);
	light_hit = trace_ray(ray, scene);
	return (light_hit.distance == -1);
}

// int	in_light(t_scene *scene, t_hit hit, t_vec3 light_dir)
// {
// 	t_hit	light_hit;
// 	t_ray	ray;
//
//
// 	ray.origin =vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
// 	ray.dir = vec3_mult(light_dir, -1);
// 	light_hit = trace_ray(ray, scene);
// 	return (light_hit.distance == -1);
// }

struct s_light_info	new_info(t_light_source light, t_hit hit, t_mat mat, t_ray ray)
{
	struct s_light_info	info;

	info.light = light;
	info.ray = ray;
	info.hit = hit;
	info.mat = mat;
	info.light_dir = vec3_sub(hit.point, light.origin);
	info.attenuation = LIGHT_RANGE / vec3_lenght(info.light_dir);
	if (info.attenuation < 0)
		info.attenuation = 0;
	info.light_dir = vec3_normalize(info.light_dir);
	return (info);
}

t_vec3	phong_shading(t_scene *scene, t_hit hit, t_mat mat, t_ray ray)
{
	t_vec3				ambient;
	t_vec3				diffuse = vec3_zero();
	t_vec3				specular = vec3_zero();
	t_vec3				merged_pass;
	struct s_light_info	info;

	if (scene->vp_flags & NORMAL)
		mat.albedo = normal_color(hit);
	ambient = vec3_zero();
	diffuse = vec3_zero();
	specular = vec3_zero();
	if (scene->vp_flags & AMBIENT)
		ambient = phong_ambient(scene, mat);
	for (size_t i = 0; i < scene->nb_lights; i++)
	{
		info = new_info(scene->lights[i], hit, mat, ray);
		if (in_light(scene, hit, info.light_dir))
		{
			if (scene->vp_flags & DIFFUSE)
				diffuse = vec3_add(diffuse, phong_diffuse(info));
			if (scene->vp_flags & SPECULAR)
				specular = vec3_add(specular, phong_specular(info));
		}
	}
	merged_pass = vec3_zero();
	merged_pass = vec3_add(merged_pass, ambient);
	merged_pass = vec3_add(merged_pass, diffuse);
	merged_pass = vec3_add(merged_pass, specular);
	return (merged_pass);
}
