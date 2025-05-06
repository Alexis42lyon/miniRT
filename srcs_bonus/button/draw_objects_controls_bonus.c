/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects_controls_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:46 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	draw_sphere_controls(t_prog *prog, t_win_button *win_btn,
	t_data *img)
{
	t_sphere	*sphere;
	float		select_val;
	float		mat_val;

	if (prog->scene->nb_spheres == 0)
		return ;
	select_val = (float)prog->scene->selected_sphere
		/ (prog->scene->nb_spheres - 1);
	draw_slider(SLID_SPHERE_SELECT_H, select_val, img);
	sphere = &prog->scene->spheres[prog->scene->selected_sphere];
	mat_val = (float)sphere->mat_idx / (prog->scene->nb_materials - 1);
	draw_slider(SPHERE_MAT_SELEC_H, mat_val, img);
	draw_button(&win_btn->sphere_buttons.x_plus, img);
	draw_button(&win_btn->sphere_buttons.x_minus, img);
	draw_button(&win_btn->sphere_buttons.y_plus, img);
	draw_button(&win_btn->sphere_buttons.y_minus, img);
	draw_button(&win_btn->sphere_buttons.z_plus, img);
	draw_button(&win_btn->sphere_buttons.z_minus, img);
	draw_button(&win_btn->sphere_buttons.diameter_plus, img);
	draw_button(&win_btn->sphere_buttons.diameter_minus, img);
}

static void	draw_plane_controls(t_prog *prog, t_win_button *win_btn,
	t_data *img)
{
	t_plane	*plane;
	float	select_val;
	float	mat_val;

	if (prog->scene->nb_planes == 0)
		return ;
	select_val = (float)prog->scene->selected_plane
		/ (prog->scene->nb_planes - 1);
	draw_slider(SLID_PLANE_SELECT_H, select_val, img);
	plane = &prog->scene->planes[prog->scene->selected_plane];
	mat_val = (float)plane->mat_idx / (prog->scene->nb_materials - 1);
	draw_slider(PLANE_MAT_SELECT_H, mat_val, img);
	draw_button(&win_btn->plane_buttons.x_plus, img);
	draw_button(&win_btn->plane_buttons.x_minus, img);
	draw_button(&win_btn->plane_buttons.y_plus, img);
	draw_button(&win_btn->plane_buttons.y_minus, img);
	draw_button(&win_btn->plane_buttons.z_plus, img);
	draw_button(&win_btn->plane_buttons.z_minus, img);
}

static void	draw_cylinder_controls(t_prog *prog, t_win_button *win_btn,
	t_data *img)
{
	t_cylinder	*cylinder;
	float		select_val;
	float		mat_val;

	if (prog->scene->nb_cylinders == 0)
		return ;
	select_val = (float)prog->scene->selected_cylinder
		/ (prog->scene->nb_cylinders - 1);
	draw_slider(SLID_CYLINDER_SELECT_H, select_val, img);
	cylinder = &prog->scene->cylinders[prog->scene->selected_cylinder];
	mat_val = (float)cylinder->mat_idx / (prog->scene->nb_materials - 1);
	draw_slider(CYLINDER_MAT_SELECT_H, mat_val, img);
	draw_button(&win_btn->cylinder_buttons.x_plus, img);
	draw_button(&win_btn->cylinder_buttons.x_minus, img);
	draw_button(&win_btn->cylinder_buttons.y_plus, img);
	draw_button(&win_btn->cylinder_buttons.y_minus, img);
	draw_button(&win_btn->cylinder_buttons.z_plus, img);
	draw_button(&win_btn->cylinder_buttons.z_minus, img);
	draw_button(&win_btn->cylinder_buttons.diameter_plus, img);
	draw_button(&win_btn->cylinder_buttons.diameter_minus, img);
	draw_button(&win_btn->cylinder_buttons.height_plus, img);
	draw_button(&win_btn->cylinder_buttons.height_minus, img);
}

static void	draw_cone_controls(t_prog *prog, t_win_button *win_btn, t_data *img)
{
	t_cylinder	*cone;
	float		select_val;
	float		mat_val;

	if (prog->scene->nb_cones == 0)
		return ;
	select_val = (float)prog->scene->selected_cone
		/ (prog->scene->nb_cones - 1);
	draw_slider(SLID_CYLINDER_SELECT_H, select_val, img);
	cone = &prog->scene->cones[prog->scene->selected_cone];
	mat_val = (float)cone->mat_idx / (prog->scene->nb_materials - 1);
	draw_slider(CYLINDER_MAT_SELECT_H, mat_val, img);
	draw_button(&win_btn->cone_buttons.x_plus, img);
	draw_button(&win_btn->cone_buttons.x_minus, img);
	draw_button(&win_btn->cone_buttons.y_plus, img);
	draw_button(&win_btn->cone_buttons.y_minus, img);
	draw_button(&win_btn->cone_buttons.z_plus, img);
	draw_button(&win_btn->cone_buttons.z_minus, img);
	draw_button(&win_btn->cone_buttons.diameter_plus, img);
	draw_button(&win_btn->cone_buttons.diameter_minus, img);
	draw_button(&win_btn->cone_buttons.height_plus, img);
	draw_button(&win_btn->cone_buttons.height_minus, img);
}

void	draw_objects_controls(t_prog *prog, t_win_button *win_btn, t_data img)
{
	if (win_btn->current_subtab == SUB_SPHERE)
		draw_sphere_controls(prog, win_btn, &img);
	else if (win_btn->current_subtab == SUB_PLANE)
		draw_plane_controls(prog, win_btn, &img);
	else if (win_btn->current_subtab == SUB_CYLINDER)
		draw_cylinder_controls(prog, win_btn, &img);
	else if (win_btn->current_subtab == SUB_CONE)
		draw_cone_controls(prog, win_btn, &img);
}

#endif
