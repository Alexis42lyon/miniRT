/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:01:58 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/16 19:05:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "window.h"
#include <math.h>
#include <stdlib.h>

static float	get_luminance(int color)
{
	return (0.299f * ((color >> 16) & 0xFF) + 0.587f
		* ((color >> 8) & 0xFF) + 0.114f
		* (color & 0xFF));
}

static int	blend_pixels(int x, int y, int *buffer, int width, int height)
{
	t_vec3i	color;
	int		count;
	int		dy;
	int		dx;
	int		nx;
	int		ny;
	int		pixel;

	color = (t_vec3i){0, 0, 0};
	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			nx = x + dx;
			ny = y + dy;
			if (nx >= 0 && nx < width && ny >= 0 && ny < height)
			{
				pixel = buffer[ny * width + nx];
				color.x += (pixel >> 16) & 0xFF;
				color.y += (pixel >> 8) & 0xFF;
				color.z += pixel & 0xFF;
				count++;
			}
			dx++;
		}
		dy++;
	}
	return (((color.x / count) << 16)
		| ((color.y / count) << 8)
		| (color.z / count));
}

void	anti_aliaser(t_prog *prog, t_viewport *vp, t_win_scene *win)
{
	int		*img_data;
	int		*buffer;
	float	luma_diff;
	int		y;
	int		x;
	int		dy;
	int		dx;

	img_data = (int *)mlx_get_data_addr(win->img.img, &win->img.bits_per_pixel,
			&win->img.line_length, &win->img.endian);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(vp->width * vp->height * sizeof(int)),
		(void **)&buffer, prog);
	ft_memcpy(buffer, img_data, vp->width * vp->height * sizeof(int));
	y = 0;
	while (++y < vp->height - 1)
	{
		x = 0;
		while (++x < vp->width - 1)
		{
			luma_diff = 0.0f;
			dy = -2;
			while (++dy <= 1)
			{
				dx = -2;
				while (++dx <= 1)
				{
					if (dx == 0 && dy == 0)
						continue ;
					luma_diff += fabs(get_luminance(buffer[y * vp->width + x])
							- get_luminance(buffer[(y + dy)
								* vp->width + (x + dx)]));
				}
			}
			if (luma_diff > 0.12f)
				img_data[y * vp->width + x] = blend_pixels(x, y, buffer,
						vp->width, vp->height);
		}
	}
	free(buffer);
}
