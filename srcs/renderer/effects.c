/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:27:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/01 11:36:10 by mjuncker         ###   ########.fr       */
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

int	do_offset(int i, int offset, int max)
{
	if (i + offset < 0)
		return (0);
	if (i + offset >= max)
		return (max);
	return (i + offset);
}

void	chromatic_aberation(t_win_scene *win, int i, int j)
{
	t_vec3			col;
	t_vec3			offset;
	const t_vec3	dir = (t_vec3){1, 1, 0};
	const float		strenght = 2;

	offset = vec3_mult(dir, strenght);
	col.x = int_to_vec(get_pixel(&win->img, do_offset(i, offset.x, win->width), do_offset(j, offset.y, win->height))).x;
	col.y = int_to_vec(get_pixel(&win->img, i, j)).y;
	col.z = int_to_vec(get_pixel(&win->img, do_offset(i, -offset.x, win->width), do_offset(j, -offset.y, win->height))).z;
	
	col = vec3_clamp(col, 0, 1);
	set_pixel(&win->img, i, j, vec_to_int(col));
}

void	grayscale(t_win_scene *win, int i, int j)
{
	t_vec3	px;
	float	gray;

	px = int_to_vec(get_pixel(&win->img, i, j));
	gray = ft_dot(px, (t_vec3){0.299, 0.587, 0.114});

	set_pixel(&win->img, i, j, vec_to_int((t_vec3){gray, gray, gray}));
}

void	pixelate(t_win_scene *win, int i, int j)
{
	int			new_i;
	int			new_j;
	const int	strenght = 10;

	new_i = i;
	new_j = j;
	while (new_i % strenght != 0)
		new_i--;
	while (new_j % strenght != 0)
		new_j--;
	set_pixel(&win->img, i, j, get_pixel(&win->img, new_i, new_j));
	
}
