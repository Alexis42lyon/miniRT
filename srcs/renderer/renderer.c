/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:24:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 14:47:58 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>

t_viewport	viewport(t_win_scene *win, t_scene *scene)
{
	t_viewport	vp;

	vp.win = win;
	vp.cam = &scene->camera;
	vp.witdh = win->width;
	vp.height = win->height;
	vp.cam->focal_length = 1.0f;
	vp.vp_height = 2 * tan(vp.cam->fov / 2 * 3.1415 / 180)
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

int	bounce(t_vec3 *final_color, t_scene *scene, t_ray *ray, uint seed)
{
	t_hit	hit;
	t_mat	mat;

	hit = trace_ray(*ray, scene);
	if (hit.distance == -1)
	{
		*final_color = vec3_add(*final_color, scene->sky_color);
		return (1);
	}
	if (hit.type == SPHERE)
		mat = scene->spheres[hit.obj_index].material;
	else if (hit.type == PLANE)
		mat = scene->planes[hit.obj_index].material;
	else if (hit.type == CYLINDER)
		mat = scene->cylinders[hit.obj_index].material;
	*final_color = mat.albedo;
	*final_color = phong_shading(scene, hit, mat, *ray);
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
	uint	seed;

	mutiplier = 1.0f;
	final_color = vec3_zero();
	ray = get_ray((float)(i) / ((float)vp.witdh),
			(float)(j) / (float)(vp.height), vp);
	seed = (i + (j * vp.win->width)) * scene->frame_count;
	i = 0;
	while (i < BOUNCES)
	{
		seed *= i + 1;
		if (bounce(&final_color, scene, &ray, seed) == 1)
			break ;
		final_color = vec3_mult(final_color, mutiplier);
		mutiplier *= 0.5f;
		i++;
	}
	if (i != BOUNCES)
		final_color = vec3_mult(final_color, mutiplier);
	return (vec3_clamp(final_color, 0, 1));
}

void	render(t_viewport vp, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	color;
	t_vec3	*accumulation_data;
	t_vec3	accumulation;

	accumulation_data = vp.win->accumulation_data;
	j = 0;
	while (j < vp.win->height)
	{
		i = 0;
		while (i < vp.win->width)
		{
			color = get_px_col(i, j, vp, scene);
			accumulation_data[i + j * vp.win->width] = vec3_add(
					accumulation_data[i + j * vp.win->width], color);
			accumulation = accumulation_data[i + j * vp.win->width];
			accumulation = vec3_divide(accumulation, scene->frame_count);
			accumulation = vec3_clamp(accumulation, 0, 1);
			set_pixel(&vp.win->img, i, j, vec_to_int(accumulation));
			i++;
		}
		show_progress(vp.win->width * j + i, vp.win->width * vp.win->height);
		j++;
	}
}
