/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:25:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/02 15:42:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer.h"
#include "texture.h"
#include <stdio.h>
#include "window.h"

int	in_light(t_scene *scene, t_hit hit, struct s_light_info infos)
{
	t_hit	light_hit;
	t_ray	ray;

	ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
	ray.dir = vec3_mult(infos.light_dir, -1);
	ray.length = vec3_lenght(vec3_sub(infos.light.origin, ray.origin));
	light_hit = trace_ray(ray, scene);
	return (light_hit.distance == -1);
}

struct s_light_info	new_info(
	t_light_source light, t_hit hit, t_mat mat, t_ray ray)
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

t_vec3	recalculate_normal(t_scene *scene, t_hit hit,
	t_render_pass *pass, t_vec3 *world_normal)
{
	float	u;
	float	v;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	map_normal;

	get_uv(scene, hit, &u, &v);
	get_tangents(hit.normal, &tangent, &bitangent);
	map_normal = get_px(u, v, &hit.mat.normal_map);
	map_normal = vec3_add(vec3_mult(map_normal, 2.0f), (t_vec3){-1, -1, -1});
	*world_normal = vec3_add(
			vec3_mult(tangent, map_normal.x),
			vec3_add(
				vec3_mult(bitangent, map_normal.y),
				vec3_mult(hit.normal, map_normal.z)
				)
			);
	*world_normal = vec3_normalize(*world_normal);
	if (vec3_lenght_square(pass->uv) == 0)
		pass->uv = (t_vec3){u, v, 0};
	return (*world_normal);
}

void	phong_shading(t_scene *scene, t_frame_data *frame)
{
	struct s_light_info	info;
	size_t				i;

	if (is_header_valid(&frame->hit.mat.normal_map.header))
		recalculate_normal(scene, frame->hit, frame->pass, &frame->hit.normal);
	if (vec3_lenght_square(frame->pass->normal) == 0)
		frame->pass->normal = normal_color(frame->hit);
	i = 0;
	while (i < scene->nb_lights)
	{
		info = new_info(scene->lights[i], frame->hit,
				frame->hit.mat, frame->ray);
		frame->pass->ambient = vec3_add(frame->pass->ambient,
				phong_ambient(frame));
		if (in_light(scene, frame->hit, info))
		{
			frame->pass->diffuse = vec3_add(
					frame->pass->diffuse, phong_diffuse(info));
			frame->pass->specular = vec3_add(
					frame->pass->specular, phong_specular(info));
		}
		i++;
	}
}
