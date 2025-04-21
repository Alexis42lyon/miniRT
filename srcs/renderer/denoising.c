/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   denoising.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:26:14 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/21 20:46:29 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include <math.h>

#define KERNEL_SIZE 3
#define SIGMA_SPATIAL 1.5
#define SIGMA_RANGE 0.2
#define TEMPORAL_WEIGHT 0.5

void	blend_frames(t_vec3 *current, t_vec3 *prev, int total, float weight);
void	apply_bilateral(t_prog *p);
void	process_pixel(t_prog *p, int x, int y);
float	gaussian(float x, float sigma);
void	clamp_extremes(t_vec3 *color);
float	apply_kernel(t_prog *p, int x, int y, int i, int j,
	t_vec3 *sum, t_vec3 center);

void	denoiser(t_prog *prog, t_win_scene *win)
{
	static t_vec3	*prev_frame = NULL;
	t_vec3			*current;
	int				i;
	int				total;

	(void)win;
	if (prog->scene->frame_count < 2)
		return ;
	total = prog->win_scene->view_width * prog->win_scene->view_height;
	current = malloc(sizeof(t_vec3) * total);
	if (!current)
		return ;
	i = -1;
	while (++i < total)
		current[i] = vec3_divide(prog->win_scene->accumulation_data[i],
				prog->scene->frame_count);
	apply_bilateral(prog);
	if (prev_frame)
		blend_frames(current, prev_frame, total, TEMPORAL_WEIGHT);
	free(prev_frame);
	prev_frame = current;
}

void	apply_bilateral(t_prog *p)
{
	int		x;
	int		y;
	int		w;
	int		h;

	w = p->win_scene->view_width;
	h = p->win_scene->view_height;
	y = KERNEL_SIZE;
	while (y < h - KERNEL_SIZE)
	{
		x = KERNEL_SIZE;
		while (x < w - KERNEL_SIZE)
		{
			process_pixel(p, x, y);
			x++;
		}
		y++;
	}
}

void	process_pixel(t_prog *p, int x, int y)
{
	t_vec3	sum;
	t_vec3	center;
	float	weight;
	int		i;
	int		j;
	int		idx;
	int		w;

	w = p->win_scene->view_width;
	idx = y * w + x;
	center = p->win_scene->accumulation_data[idx];
	sum = vec3_zero();
	weight = 0.0f;
	i = -KERNEL_SIZE;
	while (i <= KERNEL_SIZE)
	{
		j = -KERNEL_SIZE;
		while (j <= KERNEL_SIZE)
		{
			weight += apply_kernel(p, x, y, i, j, &sum, center);
			j++;
		}
		i++;
	}
	if (weight > 0.0f)
		p->win_scene->accumulation_data[idx] = vec3_divide(sum, weight);
	clamp_extremes(&p->win_scene->accumulation_data[idx]);
}

float	apply_kernel(t_prog *p, int x, int y, int i, int j,
					t_vec3 *sum, t_vec3 center)
{
	int		idx;
	int		w;
	t_vec3	current;
	float	spatial;
	float	range;
	float	w_total;

	w = p->win_scene->view_width;
	idx = (y + j) * w + (x + i);
	current = p->win_scene->accumulation_data[idx];
	spatial = gaussian(sqrtf(i * i + j * j), SIGMA_SPATIAL);
	range = gaussian(vec3_lenght(vec3_sub(current, center)), SIGMA_RANGE);
	w_total = spatial * range;
	*sum = vec3_add(*sum, vec3_mult(current, w_total));
	return (w_total);
}

float	gaussian(float x, float sigma)
{
	return (expf(-(x * x) / (2 * sigma * sigma)));
}

void	clamp_extremes(t_vec3 *color)
{
	color->x = 1.0f;
	color->y = 1.0f;
	color->z = 1.0f;
	// color->x = fmax(0.001f, fmin(1.0f, color->x));
	// color->y = fmax(0.001f, fmin(1.0f, color->y));
	// color->z = fmax(0.001f, fmin(1.0f, color->z));
}

void	blend_frames(t_vec3 *current, t_vec3 *prev, int total, float weight)
{
	int	i;

	i = -1;
	while (++i < total)
	{
		current[i] = vec3_add(
				vec3_mult(current[i], weight),
				vec3_mult(prev[i], 1.0f - weight));
	}
}
