/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:31 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"

t_mat	default_mat(void)
{
	return ((t_mat)
		{
			.albedo = {1, 0, 1},
			.emission_power = 0.0f,
			.roughtness = 0.7f,
			.shyniness = 126,
			.spec_coef = 0.6f,
			.use_checker = 1,
		});
}

t_vec3	normal_color(t_hit hit)
{
	t_vec3	color;

	color = vec3_mult(vec3_add(hit.normal, (t_vec3){1, 1, 1}), 0.5);
	return (color);
}

t_uint	vec_to_int(const t_vec3 color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	r = (unsigned char)(color.x * 255.0f);
	g = (unsigned char)(color.y * 255.0f);
	b = (unsigned char)(color.z * 255.0f);
	a = 255;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

t_vec3	int_to_vec(t_uint color)
{
	return ((t_vec3){
		((color >> 16) & 0xFF) / 255.0f,
		((color >> 8) & 0xFF) / 255.0f,
		(color & 0xFF) / 255.0f
	});
}

t_vec3	sky_col(t_ray ray, t_scene *scene)
{
	const t_vec3	unit_direction = vec3_normalize(ray.dir);
	const float		a = 0.5 * (unit_direction.y + 1.0);
	t_vec3			sky_col;

	sky_col = vec3_add(
			vec3_mult((t_vec3){1.0, 1.0, 1.0}, (1.0 - a)),
			vec3_mult(scene->ambient_light.color, a)
			);
	return (vec3_mult(sky_col, scene->ambient_light.ratio));
}
