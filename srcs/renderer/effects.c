/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:27:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/25 12:48:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/io.h"
#include "libft/math.h"
#include "libft/vector.h"
#include "raytracer.h"
#include <stdio.h>
#include "window.h"

void	invert_effect(t_win_scene *win, int i, int j)
{
	set_pixel(&win->img, i, j, 0xFFFFFF - get_pixel(&win->img, i, j));
}

void	depth_effect(t_win_scene *win, int i, int j)
{
	set_pixel(&win->img, i, j, vec_to_int(win->depth_map[i + j * win->width]));
}

static float	gaussien(int i, int j, float sigma)
{
	float s;

	s = 2.0f * sigma * sigma;
    return (1.0f / (3.1415 * s)) * exp(-(i * i + j * j) / s);
}

float	*create_dof_kernel(const int size)
{
	const float	sigma = 3.0f;
	float		*kernel;
	float		sum = 0.0f;
	int			half = size / 2;

	int		i;
	int		j;
	float	value;

	kernel = malloc(size * size * sizeof(float));
	if (!kernel)
		return (NULL);
	i = -half;
	while (i <= half)
	{
		j = -half;
		while (j <= half)
		{
			value = gaussien(i, j, sigma);
			kernel[(i + half) * size + (j + half)] = value;
			sum += value;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size * size)
	{
		kernel[i] /= sum;
		i++;
	}
	return (kernel);
}

void	depth_of_field(t_win_scene *win, int i, int j)
{
	t_vec3	final;
	const int	size = 11;
	int	half = size / 2;

	final = vec3_zero();

	int dx;
	int dy;

	float	*kernel = create_dof_kernel(size);
	if (kernel == NULL)
		return;

	dx = -half;
	while (dx <= half)
	{
		dy = -half;
		while (dy <= half)
		{
			int x = ft_clamp(i + dx, 0, win->width - 1);
			int y = ft_clamp(j + dy, 0, win->height - 1);
			t_vec3	color = int_to_vec(get_pixel(&win->img, x, y));
			float weight = kernel[(dx + half) * size + (dy + half)];
			final = vec3_add(final, vec3_mult(color, weight));
			dy++;
		}
		dx++;
	}
	free(kernel);
	final = vec3_clamp(final, 0, 1);
	float t = vec3_lenght(win->depth_map[i + j * win->width]);
	t = ft_clamp(t, 0, 1);
	t_vec3 dof = vec3_add(vec3_mult(int_to_vec(get_pixel(&win->img, i, j)), (1.0 - t)), vec3_mult(final, t));
	set_pixel(&win->img, i, j,  vec_to_int(dof));
}

