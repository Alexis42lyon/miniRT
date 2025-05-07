/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects_complex_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:27:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 09:09:47 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"

void	posterize(t_win_scene *win, int i, int j)
{
	const int	level = 10;
	const int	interval = 256 / level;
	t_vec3		px_col;

	px_col = int_to_vec(get_pixel(&win->img, i, j));
	px_col = vec3_mult(px_col, 255);
	px_col.x = ((int)px_col.x / interval) * interval;
	px_col.y = ((int)px_col.y / interval) * interval;
	px_col.z = ((int)px_col.z / interval) * interval;
	px_col = vec3_divide(px_col, 255);
	set_pixel(&win->img, i, j, vec_to_int(px_col));
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
	col.x = int_to_vec(get_pixel(&win->img, do_offset(i,
					offset.x, win->width),
				do_offset(j, offset.y, win->height))).x;
	col.y = int_to_vec(get_pixel(&win->img, i, j)).y;
	col.z = int_to_vec(get_pixel(&win->img, do_offset(i,
					-offset.x, win->width),
				do_offset(j, -offset.y, win->height))).z;
	col = vec3_clamp(col, 0, 1);
	set_pixel(&win->img, i, j, vec_to_int(col));
}

void	depth_of_field(t_win_scene *win, int i, int j)
{
	t_gaussien_dof	dof;
	float			t;
	t_vec3			new_px;

	dof = new_dof(11);
	if (!dof.kernel)
		return ;
	create_blur_pixel(&dof, i, j, win);
	free(dof.kernel);
	dof.final = vec3_clamp(dof.final, 0, 1);
	t = ft_clamp(vec3_length_square(win->pass[i + j * win->width].depth_map),
			0, 1);
	new_px = vec3_add(vec3_mult(
				int_to_vec(get_pixel(&win->img, i, j)), (1.0 - t)),
			vec3_mult(dof.final, t));
	set_pixel(&win->img, i, j, vec_to_int(new_px));
}
