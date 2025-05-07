/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects_simple_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:27:13 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 09:10:12 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"

void	invert_effect(t_win_scene *win, int i, int j)
{
	set_pixel(&win->img, i, j,
		0xFFFFFF - get_pixel(&win->img, i, j));
}

void	vp_filter(t_win_scene *win, int i, int j)
{
	if (win->vp_flags & UV)
		set_pixel(&win->img, i, j,
			vec_to_int(win->pass[i + j * win->width].uv));
	if (win->vp_flags & NORMAL)
		set_pixel(&win->img, i, j,
			vec_to_int(win->pass[i + j * win->width].normal));
	if (win->vp_flags & DEPTH_MAP)
		set_pixel(&win->img, i, j,
			vec_to_int(win->pass[i + j * win->width].depth_map));
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
	const int	strenght = 2;

	new_i = i;
	new_j = j;
	while (new_i % strenght != 0)
		new_i--;
	while (new_j % strenght != 0)
		new_j--;
	set_pixel(&win->img, i, j,
		get_pixel(&win->img, new_i, new_j));
}
