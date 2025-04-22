/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:01:58 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/21 21:44:16 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "window.h"
#include <math.h>
#include <stdlib.h>

static t_vec3	vec3_scale(t_vec3 v, float s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

static t_vec3	bilinear_sample(t_vec3 *buffer, int width, int height, float u, float v)
{
	int		x0 = (int)fmax(0, fmin(u, width - 1));
	int		y0 = (int)fmax(0, fmin(v, height - 1));
	int		x1 = fmin(x0 + 1, width - 1);
	int		y1 = fmin(y0 + 1, height - 1);
	float	dx = u - x0;
	float	dy = v - y0;
	t_vec3	c00 = buffer[y0 * width + x0];
	t_vec3	c10 = buffer[y0 * width + x1];
	t_vec3	c01 = buffer[y1 * width + x0];
	t_vec3	c11 = buffer[y1 * width + x1];
	t_vec3	c0 = vec3_add(vec3_scale(c00, 1 - dx), vec3_scale(c10, dx));
	t_vec3	c1 = vec3_add(vec3_scale(c01, 1 - dx), vec3_scale(c11, dx));
	return (vec3_add(vec3_scale(c0, 1 - dy), vec3_scale(c1, dy)));
}

void	anti_aliaser(t_prog *prog, t_win_scene *win)
{
	const int	w = win->width;
	const int	h = win->height;
	t_vec3		*src;
	t_vec3		*dst;
	t_data		*img = &win->img;

	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(w * h * sizeof(t_vec3)),
		(void **)&src, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(w * h * sizeof(t_vec3)),
		(void **)&dst, prog);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int		color = *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8));
			src[y * w + x] = int_to_vec(color);
		}
	}
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			t_vec3	sum = {0};
			for (float i = 0.125f; i < 1.0f; i += 0.25f)
			{
				for (float j = 0.125f; j < 1.0f; j += 0.25f)
				{
					float	u = x + i;
					float	v = y + j;
					sum = vec3_add(sum, bilinear_sample(src, w, h, u, v));
				}
			}
			dst[y * w + x] = vec3_scale(sum, 1.0f / 16.0f);
		}
	}
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int	color = vec_to_int(dst[y * w + x]);
			*(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)) = color;
		}
	}
	free(src);
	free(dst);
}
