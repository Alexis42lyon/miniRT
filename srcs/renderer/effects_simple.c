/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:27:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 16:28:00 by mjuncker         ###   ########.fr       */
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
	set_pixel(&win->final_image, i, j,
		0xFFFFFF - get_pixel(&win->final_image, i, j));
}

void	vp_filter(t_win_scene *win, int i, int j)
{
	if (win->vp_flags & UV)
		set_pixel(&win->final_image, i, j,
			vec_to_int(win->pass[i + j * WIDTH].uv));
	if (win->vp_flags & NORMAL)
		set_pixel(&win->final_image, i, j,
			vec_to_int(win->pass[i + j * WIDTH].normal));
	if (win->vp_flags & DEPTH_MAP)
		set_pixel(&win->final_image, i, j,
			vec_to_int(win->pass[i + j * WIDTH].depth_map));
}

void	grayscale(t_win_scene *win, int i, int j)
{
	t_vec3	px;
	float	gray;

	px = int_to_vec(get_pixel(&win->final_image, i, j));
	gray = ft_dot(px, (t_vec3){0.299, 0.587, 0.114});
	set_pixel(&win->final_image, i, j, vec_to_int((t_vec3){gray, gray, gray}));
}

void	pixelate(t_win_scene *win, int i, int j)
{
	int			new_i;
	int			new_j;
	const int	strenght = 2;

	new_i = i;
	new_j = j;
	while (new_i % strenght != 0)
		new_i--;
	while (new_j % strenght != 0)
		new_j--;
	set_pixel(&win->final_image, i, j,
		get_pixel(&win->final_image, new_i, new_j));
}
