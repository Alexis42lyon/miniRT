/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dragging_slider.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:28:19 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 12:29:06 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	handle_dragging_slider_materials(int y, t_win_button *win_btn)
{
	if ((y >= SLID_MAT_SELECT_H
			&& y <= SLID_MAT_SELECT_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_RED_H
			&& y <= SLID_MAT_RED_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_GREEN_H
			&& y <= SLID_MAT_GREEN_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_BLUE_H
			&& y <= SLID_MAT_BLUE_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_SHINI_H
			&& y <= SLID_MAT_SHINI_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_ROUGH_H
			&& y <= SLID_MAT_ROUGH_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_SPEC_H
			&& y <= SLID_MAT_SPEC_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_EMIS_H
			&& y <= SLID_MAT_EMIS_H + SLIDER_HEIGHT)
		|| (y >= SLID_MAT_CHECK_H
			&& y <= SLID_MAT_CHECK_H + SLIDER_HEIGHT))
		win_btn->is_dragging = 1;
}

static void	handle_dragging_slider_objects_utils(int y, t_win_button *win_btn)
{
	if (win_btn->current_subtab == SUB_CYLINDER)
	{
		if (y >= CYLINDER_MAT_SELECT_H
			&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
		if (y >= SLID_CYLINDER_SELECT_H
			&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
	else if (win_btn->current_subtab == SUB_CONE)
	{
		if (y >= CYLINDER_MAT_SELECT_H
			&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
		if (y >= SLID_CYLINDER_SELECT_H
			&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
}

static void	handle_dragging_slider_objects(int y, t_win_button *win_btn)
{
	if (win_btn->current_subtab == SUB_SPHERE)
	{
		if (y >= SPHERE_MAT_SELEC_H
			&& y <= SPHERE_MAT_SELEC_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
		if (y >= SLID_SPHERE_SELECT_H
			&& y <= SLID_SPHERE_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
	else if (win_btn->current_subtab == SUB_PLANE)
	{
		if (y >= PLANE_MAT_SELECT_H
			&& y <= PLANE_MAT_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
		if (y >= SLID_PLANE_SELECT_H
			&& y <= SLID_PLANE_SELECT_H + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
	handle_dragging_slider_objects_utils(y, win_btn);
}

static void	handle_dragging_slider_lights(int y, t_win_button *win_btn)
{
	if ((y >= SLID_LIGHT_SELECT_H
			&& y <= SLID_LIGHT_SELECT_H + SLIDER_HEIGHT)
		|| (y >= SLID_LIGHT_RATIO_H
			&& y <= SLID_LIGHT_RATIO_H + SLIDER_HEIGHT)
		|| (y >= SLID_LIGHT_R_H
			&& y <= SLID_LIGHT_R_H + SLIDER_HEIGHT)
		|| (y >= SLID_LIGHT_G_H
			&& y <= SLID_LIGHT_G_H + SLIDER_HEIGHT)
		|| (y >= SLID_LIGHT_B_H
			&& y <= SLID_LIGHT_B_H + SLIDER_HEIGHT))
		win_btn->is_dragging = 1;
}

void	handle_dragging_slider(int y, t_win_button *win_btn, t_prog *prog)
{
	if (win_btn->current_tab == TAB_LIGHTS)
		handle_dragging_slider_lights(y, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		handle_dragging_slider_objects(y, win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS
		&& prog->scene->nb_materials > 0)
		handle_dragging_slider_materials(y, win_btn);
}

#endif
