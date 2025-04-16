/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:24:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/16 11:17:10 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>
#include <pthread.h>

t_viewport	viewport(t_win_scene *win, t_scene *scene)
{
	t_viewport	vp;

	vp.win = win;
	vp.cam = &scene->camera;
	vp.witdh = win->width;
	vp.height = win->height;
	vp.vp_height = 2 * tan((double)vp.cam->fov / 2 * 3.1415 / 180)
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

int	bounce(t_vec3 *final_color, t_scene *scene, t_ray *ray, t_uint seed)
{
	t_hit	hit;
	t_mat	mat;

	hit = trace_ray(*ray, scene);
	if (hit.distance == -1)
	{
		t_vec3 unit_direction = vec3_normalize(ray->dir);
		float a = 0.5 * (unit_direction.y + 1.0);
		t_vec3 sky_col = vec3_add(
			vec3_mult((t_vec3){1.0, 1.0, 1.0}, (1.0-a)),
			vec3_mult(scene->sky_color, a));
		sky_col = vec3_mult(sky_col, scene->ambient_light.ratio);

		*final_color = vec3_add(*final_color, sky_col);
		return (1);
	}
	if (hit.type == SPHERE)
		mat = scene->spheres[hit.obj_index].material;
	else if (hit.type == PLANE)
		mat = scene->planes[hit.obj_index].material;
	else if (hit.type == CYLINDER)
		mat = scene->cylinders[hit.obj_index].material;
	else if (hit.type == CONE)
		mat = scene->cones[hit.obj_index].material;
	*final_color = mat.albedo;
	//*final_color = phong_shading(scene, hit, mat, *ray);
	*final_color = checker_color(hit, mat);

	ray->origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
	ray->dir = vec3_reflect(ray->dir,
			vec3_add(hit.normal, vec3_mult(random_vec(seed), mat.roughtness)));
	return (0);
}

t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_ray	ray;
	t_vec3	final_color;
	float	mutiplier;
	t_uint	seed;

	mutiplier = 1.0f;
	final_color = vec3_zero();
	ray = get_ray((float)(i) / ((float)vp.witdh),
			(float)(j) / (float)(vp.height), vp);
	seed = (i + (j * vp.win->width)) * scene->frame_count;
	i = 0;
	while (i < scene->nb_bounces)
	{
		seed *= i + 1;
		if (bounce(&final_color, scene, &ray, seed) == 1)
			break ;
		final_color = vec3_mult(final_color, mutiplier);
		mutiplier *= 0.5f;
		i++;
	}
	if (i != scene->nb_bounces)
		final_color = vec3_mult(final_color, mutiplier);
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
		// if (ctx->id == 0)
		// 	show_progress(ctx->j * ctx->vp.witdh + ctx->i, ctx->vp.witdh * ctx->vp.height);
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
