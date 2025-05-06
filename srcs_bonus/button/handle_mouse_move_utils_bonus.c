/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_move_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:24:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	handle_mouse_move_plane(int y, float new_value, t_prog *prog)
{
	t_plane			*plane;

	if (y >= PLANE_MAT_SELECT_H && y <= PLANE_MAT_SELECT_H + SLIDER_HEIGHT)
	{
		plane = &prog->scene->planes[prog->scene->selected_plane];
		plane->mat_idx = (int)(new_value * (prog->scene->nb_materials - 1));
		plane->material = prog->scene->materials[plane->mat_idx];
	}
	if (y >= SLID_PLANE_SELECT_H
		&& y <= SLID_PLANE_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_plane = (int)(new_value
				* (prog->scene->nb_planes - 1));
}

static void	handle_mouse_move_sphere(int y, float new_value, t_prog *prog)
{
	t_sphere		*sphere;

	if (y >= SPHERE_MAT_SELEC_H && y <= SPHERE_MAT_SELEC_H + SLIDER_HEIGHT)
	{
		sphere = &prog->scene->spheres[prog->scene->selected_sphere];
		sphere->mat_idx = (int)(new_value
				* (prog->scene->nb_materials - 1));
		sphere->material = prog->scene->materials[sphere->mat_idx];
	}
	if (y >= SLID_SPHERE_SELECT_H
		&& y <= SLID_SPHERE_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_sphere = (int)(new_value
				* (prog->scene->nb_spheres - 1));
}

static void	handle_mouse_move_cylinder(int y, float new_value, t_prog *prog)
{
	t_cylinder		*cylinder;

	if (y >= CYLINDER_MAT_SELECT_H
		&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
	{
		cylinder = &prog->scene->cylinders[prog->scene->selected_cylinder];
		cylinder->mat_idx
			= (int)(new_value * (prog->scene->nb_materials - 1));
		cylinder->material = prog->scene->materials[cylinder->mat_idx];
	}
	if (y >= SLID_CYLINDER_SELECT_H
		&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_cylinder = (int)(new_value
				* (prog->scene->nb_cylinders - 1));
}

static void	handle_mouse_move_cone(int y, float new_value, t_prog *prog)
{
	t_cylinder		*cone;

	if (y >= CYLINDER_MAT_SELECT_H
		&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
	{
		cone = &prog->scene->cones[prog->scene->selected_cone];
		cone->mat_idx = (int)(new_value * (prog->scene->nb_materials - 1));
		cone->material = prog->scene->materials[cone->mat_idx];
	}
	if (y >= SLID_CYLINDER_SELECT_H
		&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_cone = (int)(new_value
				* (prog->scene->nb_cones - 1));
}

void	handle_mouse_move_objects(int y, float new_value,
	t_prog *prog, t_win_button *win_btn)
{
	if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_SPHERE)
	{
		handle_mouse_move_sphere(y, new_value, prog);
	}
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_PLANE)
	{
		handle_mouse_move_plane(y, new_value, prog);
	}
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_CYLINDER)
	{
		handle_mouse_move_cylinder(y, new_value, prog);
	}
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_CONE)
	{
		handle_mouse_move_cone(y, new_value, prog);
	}
}

#endif
