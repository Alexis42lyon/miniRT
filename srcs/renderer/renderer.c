/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:24:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/03 08:42:32 by mjuncker         ###   ########.fr       */
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

t_hit	bounce(t_scene *scene, t_ray *ray, t_render_pass *pass)
{
	t_hit	hit;
	float	u;
	float	v;

	hit = trace_ray(*ray, scene);
	if (hit.distance == -1)
		return (hit_fail());
	if (vec3_lenght_square(pass->depth_map) == 0)
	{
		pass->depth_map.x = hit.distance / scene->camera.focal_length;
		pass->depth_map.y = hit.distance / scene->camera.focal_length;
		pass->depth_map.z = hit.distance / scene->camera.focal_length;
		pass->depth_map = vec3_clamp(pass->depth_map, 0, 1);
	}
	if (hit.mat.texture_map.header.type[0] != -1)
	{
		get_uv(scene, hit, &u, &v);
		hit.mat.albedo = vec3_multv(hit.mat.albedo,
				get_px(u, v, &hit.mat.texture_map));
	}
	if (hit.mat.use_checker)
		hit.mat.albedo = checker_color(hit, hit.mat);
	return (hit);
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

t_frame_data	frame_data(t_scene *scene, t_viewport *vp, int i, int j)
{
	return ((t_frame_data){
		.final_color = vec3_zero(),
		.hit = hit_fail(),
		.pass = &vp->win->pass[i + j * vp->width],
		.radiance = vec3_mult(scene->ambient_light.color,
			scene->ambient_light.ratio),
		.ray = get_ray((float)i / ((float)vp->width),
			(float)j / (float)vp->height, *vp)
	});
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

t_ray	bounce_ray(t_ray ray, t_hit hit, t_uint seed)
{
	t_ray	new_ray;

	new_ray.origin = vec3_add(hit.point,
			vec3_mult(hit.normal, 0.0001));
	new_ray.dir = vec3_reflect(ray.dir, vec3_add(hit.normal,
				vec3_mult(random_vec(seed), hit.mat.roughtness)));
	return (new_ray);
}

t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_frame_data	frame;
	t_uint			seed;
	int				x;

	frame = frame_data(scene, &vp, i, j);
	seed = (i + (j * vp.win->width)) * scene->frame_count;
	x = 0;
	while (x < scene->nb_bounces)
	{
		seed *= x + 1;
		frame.hit = bounce(scene, &frame.ray, frame.pass);
		if (frame.hit.distance == -1)
		{
			if (vp.win->vp_flags & AMBIENT)
				frame.final_color = vec3_add(frame.final_color,
						vec3_divide(sky_col(frame.ray, scene), x + 1));
			break ;
		}
		apply_shading(scene, &frame, &vp);
		// frame.ray = bounce_ray(frame.ray, frame.hit, seed);
		frame.ray.origin = vec3_add(frame.hit.point, vec3_mult(frame.hit.normal, 0.0001));
		frame.ray.dir = vec3_reflect(frame.ray.dir,
			vec3_add(frame.hit.normal, vec3_mult(random_vec(seed), frame.hit.mat.roughtness)));		x++;
		x++;
	}
	return (vec3_clamp(frame.final_color, 0, 1));
}

t_vec3	process_accumulation(
	t_vec3 *accumulation_data, t_thread_context *ctx, t_vec3 color)
{
	t_vec3	accumulation;

	accumulation_data[ctx->i + ctx->j * ctx->vp.win->width] = vec3_add(
			accumulation_data[ctx->i + ctx->j * ctx->vp.win->width], color
			);
	accumulation = accumulation_data[ctx->i + ctx->j * ctx->vp.win->width];
	accumulation = vec3_divide(accumulation, ctx->scene.frame_count);
	accumulation = vec3_clamp(accumulation, 0, 1);
	return (accumulation);
}

void	*thread_routine(void *pcontext)
{
	t_thread_context	*ctx;
	t_vec3				color;
	t_vec3				*accumulation_data;

	ctx = (t_thread_context *)pcontext;
	accumulation_data = ctx->vp.win->accumulation_data;
	while (ctx->j < ctx->vp.win->height)
	{
		while (ctx->i < ctx->vp.win->width)
		{
			color = get_px_col(ctx->i, ctx->j, ctx->vp, &ctx->scene);
			set_pixel(&ctx->vp.win->img, ctx->i, ctx->j, vec_to_int(
					process_accumulation(accumulation_data, ctx, color)
					));
			ctx->i += MAX_TRHEAD;
		}
		ctx->i -= ctx->vp.win->width;
		ctx->j++;
	}
	return (NULL);
}

void	render(t_viewport vp, t_scene *scene)
{
	t_thread_context	ctx[MAX_TRHEAD];
	size_t				i;

	i = 0;
	while (i < MAX_TRHEAD)
	{
		ctx[i].id = i;
		ctx[i].i = i;
		ctx[i].j = 0;
		ctx[i].scene = *scene;
		ctx[i].vp = vp;
		pthread_create(&ctx[i].th, NULL, thread_routine, (void *)&(ctx[i]));
		i++;
	}
	i = 0;
	while (i < MAX_TRHEAD)
	{
		pthread_join(ctx[i].th, NULL);
		i++;
	}
}
