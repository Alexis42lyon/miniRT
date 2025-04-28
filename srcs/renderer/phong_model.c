/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/28 15:44:56 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "texture.h"

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
t_vec3	phong_ambient(t_scene *scene, t_mat mat)
{
	t_vec3	ambient;

	ambient = vec3_multv(mat.albedo, scene->ambient_light.color);
	ambient = vec3_mult(ambient, scene->ambient_light.ratio);
	return (ambient);
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
