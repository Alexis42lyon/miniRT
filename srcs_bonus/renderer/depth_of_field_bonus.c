/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:03:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 16:57:01 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"
#include "window_bonus.h"

static float	gaussien(int i, int j, float sigma)
{
	float	s;

	s = 2.0f * sigma * sigma;
	return ((1.0f / (M_PI * s)) * exp(-(i * i + j * j) / s));
}

float	populate_kernel(const int half, const float sigma,
	const int size, float *kernel)
{
	int		i;
	int		j;
	float	value;
	float	sum;

	sum = 0.0f;
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
	return (sum);
}

float	*create_dof_kernel(const int size)
{
	const float	sigma = 3.0f;
	const int	half = size / 2;
	float		*kernel;
	float		sum;
	int			i;

	kernel = ft_calloc(size * size, sizeof(float));
	if (!kernel)
		return (NULL);
	sum = populate_kernel(half, sigma, size, kernel);
	i = 0;
	while (i < size * size)
	{
		kernel[i] /= sum;
		i++;
	}
	return (kernel);
}

t_gaussien_dof	new_dof(int size)
{
	return ((t_gaussien_dof){
		.size = size,
		.half = size / 2,
		.kernel = create_dof_kernel(size),
		.final = vec3_zero()
	});
}

void	create_blur_pixel(t_gaussien_dof *dof, int i, int j, t_win_scene *win)
{
	int		dx;
	int		dy;
	t_vec3	color;
	float	weight;

	dx = -dof->half;
	while (dx <= dof->half)
	{
		dy = -dof->half;
		while (dy <= dof->half)
		{
			color = int_to_vec(get_pixel(&win->img,
						ft_clamp(i + dx, 0, win->width - 1),
						ft_clamp(j + dy, 0, win->height - 1)
						));
			weight = dof->kernel[
				(dx + dof->half) * dof->size + (dy + dof->half)];
			dof->final = vec3_add(dof->final, vec3_mult(color, weight));
			dy++;
		}
		dx++;
	}
}
