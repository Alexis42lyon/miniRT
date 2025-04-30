/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:24:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/30 15:58:19 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/math.h"
#include "libft/string.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "texture.h"
#include "window.h"
#include "raytracer.h"
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "texture.h"

t_viewport	viewport(t_win_scene *win, t_scene *scene)
{
	t_viewport	vp;

	vp.win = win;
	vp.cam = &scene->camera;
	vp.width = win->width;
	vp.height = win->height;
	vp.vp_height = 2 * tan((float)vp.cam->fov / 2 * 3.1415 / 180)
		* vp.cam->focal_length;
	vp.vp_width = vp.vp_height * win->aspect_ratio;
	vp.px_up_left = vec3_add(vp.cam->origin,
			vec3_add(
				vec3_sub(
					vec3_mult(vp.cam->forward, vp.cam->focal_length),
					vec3_mult(vp.cam->right, vp.vp_width / 2)
					),
				vec3_mult(vp.cam->up, vp.vp_height / 2)
				)
			);
	vp.horizontal = vec3_mult(vp.cam->right, vp.vp_width);
	vp.vertical = vec3_mult(vec3_mult(vp.cam->up, -1), vp.vp_height);
	return (vp);
}

t_hit	bounce(t_scene *scene, t_ray *ray, t_vec3 *dof_px)
{
	t_hit	hit;
	float u, v;

	hit = trace_ray(*ray, scene);
	if (hit.distance == -1)
		return (hit_fail());
	if (vec3_lenght_square(*dof_px) == 0)
	{
		dof_px->x = hit.distance / scene->camera.focal_length;
		dof_px->y = hit.distance / scene->camera.focal_length;
		dof_px->z = hit.distance / scene->camera.focal_length;
		*dof_px = vec3_clamp(*dof_px, 0, 1);
	}

	if (hit.mat.texture_map.header.type[0] != -1)
	{
		get_uv(scene, hit, &u, &v);
		hit.mat.albedo = vec3_multv(hit.mat.albedo, get_px(u, v, &hit.mat.texture_map));
	}

	if (scene->vp_flags & UV)
	{
		get_uv(scene, hit, &u, &v);
		hit.mat.albedo = (t_vec3){u, v, 0};
		hit.mat.emission_power = 5;
	}
	if (hit.mat.use_checker)
		hit.mat.albedo = checker_color(hit, hit.mat);
	return (hit);
}

t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_ray	ray;
	t_vec3	final_color;
	t_vec3	radiance;
	t_uint	seed;
	t_hit	hit;
	int	x;

	radiance = vec3_mult(scene->ambient_light.color, scene->ambient_light.ratio);
	final_color = vec3_zero();
	ray = get_ray((float)(i) / ((float)vp.width),
			(float)(j) / (float)(vp.height), vp);
	seed = (i + (j * vp.win->width)) * scene->frame_count;
	x = 0;
	while (x < scene->nb_bounces)
	{
		seed *= x + 1;
		hit = bounce(scene, &ray, &vp.win->depth_map[i + j * vp.width]);
		if (hit.distance == -1)
		{
			t_vec3 unit_direction = vec3_normalize(ray.dir);
			float a = 0.5 * (unit_direction.y + 1.0);
			t_vec3 sky_col = vec3_add(
			vec3_mult((t_vec3){1.0, 1.0, 1.0}, (1.0-a)),
			vec3_mult(scene->sky_color, a));
			sky_col = vec3_mult(sky_col, scene->ambient_light.ratio);
			final_color = vec3_add(final_color, vec3_divide(sky_col, x + 1));
			break ;
		}
		if (hit.mat.emission_power != 0)
			radiance = vec3_mult(hit.mat.albedo, hit.mat.emission_power);
		else
			radiance = vec3_multv(radiance, hit.mat.albedo);
		final_color = vec3_add(final_color, vec3_multv(vec3_divide(hit.mat.albedo, 3.1415), radiance));
		final_color = vec3_add(final_color, phong_shading(scene, hit, hit.mat, ray));
		
		ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
		ray.dir = vec3_reflect(ray.dir,
			vec3_add(hit.normal, vec3_mult(random_vec(seed), hit.mat.roughtness)));
		x++;
	}
	return (vec3_clamp(final_color, 0, 1));
}

void	*thread_routine(void *pcontext)
{
	t_thread_context	*ctx;
	t_vec3	color;
	t_vec3	*accumulation_data;
	t_vec3	accumulation;


	ctx = (t_thread_context *)pcontext;
	accumulation_data = ctx->vp.win->accumulation_data;
	while (ctx->j < ctx->vp.win->height)
	{
		while (ctx->i < ctx->vp.win->width)
		{
			color = get_px_col(ctx->i, ctx->j, ctx->vp, &ctx->scene);
			accumulation_data[ctx->i + ctx->j * ctx->vp.win->width] = vec3_add(
					accumulation_data[ctx->i + ctx->j * ctx->vp.win->width], color);
			accumulation = accumulation_data[ctx->i + ctx->j * ctx->vp.win->width];
			accumulation = vec3_divide(accumulation, ctx->scene.frame_count);
			accumulation = vec3_clamp(accumulation, 0, 1);
			set_pixel(&ctx->vp.win->img, ctx->i, ctx->j, vec_to_int(accumulation));
			ctx->i += MAX_TRHEAD;
		}
		ctx->i -= ctx->vp.win->width;
		ctx->j++;
	}
	return (NULL);
}

void	render(t_viewport vp, t_scene *scene)
{
	t_thread_context ctx[MAX_TRHEAD];

	for (size_t x = 0; x < MAX_TRHEAD; x++)
	{
		ctx[x].id = x;
		ctx[x].i = x;
		ctx[x].j = 0;
		ctx[x].scene = *scene;
		ctx[x].vp = vp;
		pthread_create(&ctx[x].th, NULL, thread_routine, (void *)&(ctx[x]));
	}
	for (size_t x = 0; x < MAX_TRHEAD; x++)
	{
		pthread_join(ctx[x].th, NULL);
	}
}
