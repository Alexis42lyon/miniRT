/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 14:03:40 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"
#include "texture_bonus.h"

/*
 * Diffuse = Kd * DOT(N, L) * Od * Ld
 * Kd = obj diffuse coef
 * N = normal
 * L = light dir
 * Od = obj albedo
 * Ld = light albedo
*/
t_vec3	phong_diffuse(struct s_light_info info)
{
	t_vec3	diffuse;

	diffuse = vec3_mult(info.mat.albedo,
			info.mat.roughtness * ft_clamp(
				ft_dot(info.hit.normal, vec3_mult(info.light_dir, -1)), 0, 1));
	diffuse = vec3_multv(diffuse, info.light.material.albedo);
	diffuse = vec3_mult(diffuse, info.light.ratio);
	diffuse = vec3_mult(diffuse, info.attenuation);
	return (vec3_clamp(diffuse, 0, 1));
}

/*
 * Ambient = Ka * Od * Ld
 * Ka = obj ambient coef
 * Od = obj color
 * Ld = ambient color
*/
t_vec3	phong_ambient(t_frame_data *frame)
{
	if (frame->hit.mat.emission_power != 0)
		frame->radiance = vec3_mult(
				frame->hit.mat.albedo, frame->hit.mat.emission_power
				);
	else
		frame->radiance = vec3_multv(frame->radiance, frame->hit.mat.albedo);
	return (vec3_multv(vec3_divide(frame->hit.mat.albedo, M_PI),
			frame->radiance));
}

t_vec3	phong_specular(struct s_light_info info)
{
	t_vec3	specular;
	t_vec3	view_vec;
	t_vec3	reflect_vec;
	float	d;
	double	spec;

	view_vec = vec3_normalize(vec3_sub(info.ray.origin, info.hit.point));
	reflect_vec = vec3_reflect(info.light_dir, info.hit.normal);
	d = ft_dot(view_vec, reflect_vec);
	if (d < 0)
		d = 0;
	spec = pow(d, info.mat.shyniness);
	specular = vec3_mult(info.light.material.albedo,
			info.mat.spec_coef * spec * info.light.ratio);
	specular = vec3_multv(specular, info.mat.albedo);
	specular = vec3_mult(specular, info.attenuation);
	return (specular);
}

void	phong_shading(t_scene *scene, t_frame_data *frame)
{
	struct s_light_info	info;
	size_t				i;

	if (is_header_valid(&frame->hit.mat.normal_map.header))
		recalculate_normal(scene, frame->hit, frame->pass, &frame->hit.normal);
	if (vec3_length_square(frame->pass->normal) == 0)
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
