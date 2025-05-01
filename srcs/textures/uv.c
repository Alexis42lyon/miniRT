/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:56:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/01 10:02:50 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "raytracer.h"
#include <math.h>
#include <stdio.h>

void	sp_coordinate_to_uv(t_vec3 normal, float *u, float *v);
void	co_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v);
void	cy_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v);
void	pl_coordinate_to_uv(t_hit hit, t_plane *plane, float *u, float *v);

void	get_uv(t_scene *scene, t_hit hit, float *u, float *v)
{
	if (hit.type == SPHERE)
		sp_coordinate_to_uv(hit.normal, u, v);
	else if (hit.type == CYLINDER)
		cy_coordinate_to_uv(hit, &scene->cylinders[hit.obj_index], u, v);
	else if (hit.type == CONE)
		co_coordinate_to_uv(hit, &scene->cones[hit.obj_index], u, v);
	else if (hit.type == PLANE)
		pl_coordinate_to_uv(hit, &scene->planes[hit.obj_index], u, v);
	else
	{
		*u = 0;
		*v = 0;
	}
}

void	pl_coordinate_to_uv(t_hit hit, t_plane *plane, float *u, float *v)
{
	const float	uv_scaling = 1.0f;
	t_vec3		tangent;
	t_vec3		bitangent;
	t_vec3		axis;

	axis = (t_vec3){0, 1, 0};
	if (fabsf(ft_dot(plane->normal, axis)) > 0.999f)
		axis = (t_vec3){1, 0, 0};
	tangent = vec3_normalize(vec3_cross(axis, plane->normal));
	bitangent = vec3_normalize(vec3_cross(plane->normal, tangent));
	*u = ft_dot(tangent, vec3_sub(plane->origin, hit.point)) * uv_scaling;
	*v = ft_dot(bitangent, vec3_sub(plane->origin, hit.point)) * uv_scaling;
	*u = fmodf(*u, 1.0f);
	if (*u < 0.0f)
		*u += 1.0f;
	*v = fmodf(*v, 1.0f);
	if (*v < 0.0f)
		*v += 1.0f;
}

void	sp_coordinate_to_uv(t_vec3 normal, float *u, float *v)
{
	*u = 0.5 - (atan2(normal.z, normal.x) / (2 * M_PI));
	*v = 0.5 - (asin(normal.y) / M_PI);
}

void	co_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v)
{
	float	slant;

	*u = 0.5 + (atan2(hit.normal.z, hit.normal.x) / (2.0 * M_PI));
	slant = sqrt(cy->radius * cy->radius + cy->height + cy->height);
	*v = (cy->height / 2 - (hit.point.y - cy->origin.y)) / slant;
	*u = ft_clamp(*u, 0, 1);
	*v = ft_clamp(*v, 0, 1);
}

void	cy_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v)
{
	*u = 0.5 + (atan2(hit.normal.z, hit.normal.x) / (2.0 * M_PI));
	*v = (hit.point.y - cy->origin.y + cy->height / 2) / cy->height - 0.5;
	*v = 1 - *v;
	*u = ft_clamp(*u, 0, 1);
	*v = ft_clamp(*v, 0, 1);
}
