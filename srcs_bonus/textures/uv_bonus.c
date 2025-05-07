/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:56:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 09:15:58 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"

static void	sp_coordinate_to_uv(t_vec3 normal, float *u, float *v);
static void	co_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v);
static void	cy_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v);
static void	pl_coordinate_to_uv(t_hit hit, t_plane *plane, float *u, float *v);

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

static void	pl_coordinate_to_uv(t_hit hit, t_plane *plane, float *u, float *v)
{
	const float	uv_scaling = 1.0f;
	t_vec3		tangent;
	t_vec3		bitangent;

	get_tangents(plane->normal, &tangent, &bitangent);
	*u = ft_dot(tangent, vec3_sub(plane->origin, hit.point)) * uv_scaling;
	*v = ft_dot(bitangent, vec3_sub(plane->origin, hit.point)) * uv_scaling;
	*u = fmodf(*u, 1.0f);
	if (*u < 0.0f)
		*u += 1.0f;
	*v = fmodf(*v, 1.0f);
	if (*v < 0.0f)
		*v += 1.0f;
}

static void	sp_coordinate_to_uv(t_vec3 normal, float *u, float *v)
{
	*u = 0.5 - (atan2(normal.z, normal.x) / (2 * M_PI));
	*v = 0.5 - (asin(normal.y) / M_PI);
}

static void	co_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v)
{
	float		slant;
	t_vec3		tangent;
	t_vec3		bitangent;
	t_vec3		local;
	float		height;

	get_tangents(cy->normal, &tangent, &bitangent);
	local = vec3_sub(hit.point, cy->origin);
	*u = 0.5 + (atan2(ft_dot(local, bitangent),
				ft_dot(local, tangent)) / (2.0 * M_PI));
	slant = sqrt(cy->radius * cy->radius + cy->height + cy->height);
	height = ft_dot(local, cy->normal);
	*v = (cy->height / 2 - height) / slant + 0.5f;
	*u = ft_clamp(*u, 0, 1);
	*v = ft_clamp(*v, 0, 1);
}

static void	cy_coordinate_to_uv(t_hit hit, t_cylinder *cy, float *u, float *v)
{
	t_vec3		tangent;
	t_vec3		bitangent;
	t_vec3		local;
	float		height;

	get_tangents(cy->normal, &tangent, &bitangent);
	local = vec3_sub(hit.point, cy->origin);
	*u = 0.5f + atan2f(ft_dot(local, bitangent),
			ft_dot(local, tangent)) / (2.0f * M_PI);
	height = ft_dot(local, cy->normal);
	*v = (height + cy->height / 2.0f) / cy->height - 0.5f;
	*v = 1 - *v;
	*v = ft_clamp(*v, 0, 1);
	*u = ft_clamp(*u, 0, 1);
}
