/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:01:58 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 11:46:07 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "window.h"
#include <math.h>
#include <stdlib.h>



#define SAMPLES 4

static t_vec3	sample_pixel(int x, int y, t_viewport vp, t_scene *scene)
{
	t_vec3	color;
	float	offsets[SAMPLES][2] = {{0.25, 0.25}, {0.75, 0.25},
								  {0.25, 0.75}, {0.75, 0.75}};
	int		i;

	color = vec3_zero();
	i = -1;
	while (++i < SAMPLES)
	{
		color = vec3_add(color, get_px_col(
				x + offsets[i][0],
				y + offsets[i][1],
				vp,
				scene
			));
	}
	return (vec3_divide(color, SAMPLES));
}

void	anti_aliaser(t_viewport vp, t_scene *scene)
{
	int		x;
	int		y;
	t_vec3	color;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(vp.win->img.img, &bpp, &size_line, &endian);
	y = -1;
	while (++y < vp.height)
	{
		x = -1;
		while (++x < vp.width)
		{
			color = sample_pixel(x, y, vp, scene);
			set_pixel(&vp.win->img, x, y, vec_to_int(vec3_clamp(color, 0, 1)));
		}
	}
}
