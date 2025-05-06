/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:25:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer_bonus.h"
#include "texture_bonus.h"
#include <stdio.h>
#include "window_bonus.h"

int	in_light(t_scene *scene, t_hit hit, struct s_light_info infos)
{
	t_hit	light_hit;
	t_ray	ray;

	ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
	ray.dir = vec3_mult(infos.light_dir, -1);
	ray.length = vec3_length(vec3_sub(infos.light.origin, ray.origin));
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
	info.attenuation = LIGHT_RANGE / vec3_length(info.light_dir);
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
	if (vec3_length_square(pass->uv) == 0)
		pass->uv = (t_vec3){u, v, 0};
	return (*world_normal);
}

t_vec3	create_merge_pass(t_render_pass *pass, t_uint flags)
{
	pass->merged_pass = vec3_zero();
	if (flags & AMBIENT)
		pass->merged_pass = vec3_add(pass->merged_pass, pass->ambient);
	if (flags & DIFFUSE)
		pass->merged_pass = vec3_add(pass->merged_pass, pass->diffuse);
	if (flags & SPECULAR)
		pass->merged_pass = vec3_add(pass->merged_pass, pass->specular);
	return (pass->merged_pass);
}

void	apply_shading(t_scene *scene, t_frame_data *frame, t_viewport *vp)
{
	phong_shading(scene, frame);
	if (frame->hit.mat.emission_power == 0)
		frame->final_color = vec3_add(frame->final_color,
				create_merge_pass(frame->pass, vp->win->vp_flags));
	else
		frame->final_color = vec3_add(frame->final_color,
				frame->pass->ambient);
}
