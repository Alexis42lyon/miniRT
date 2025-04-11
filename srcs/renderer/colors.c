/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:31 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 14:10:18 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_mat	default_mat(void)
{
	return ((t_mat){
		{1, 1, 1},
		1.0f,
		-1.0f
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
	t_vec3			vec;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	vec.x = r / 255.0f;
	vec.y = g / 255.0f;
	vec.z = b / 255.0f;
	return (vec);
}
