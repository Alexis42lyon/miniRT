/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_move_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:21:57 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:02:57 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

#include <math.h>

static void	handle_mouse_move_ambient_light(int y, float new_value,
	t_prog *prog)
{
	if (y >= SLID_LIGHT_RATIO_H && y <= SLID_LIGHT_RATIO_H
		+ SLIDER_HEIGHT)
		prog->scene->ambient_light.ratio = new_value;
	else if (y >= SLID_LIGHT_R_H && y <= SLID_LIGHT_R_H
		+ SLIDER_HEIGHT)
		prog->scene->ambient_light.color.x = new_value;
	else if (y >= SLID_LIGHT_G_H && y <= SLID_LIGHT_G_H
		+ SLIDER_HEIGHT)
		prog->scene->ambient_light.color.y = new_value;
	else if (y >= SLID_LIGHT_B_H && y <= SLID_LIGHT_B_H
		+ SLIDER_HEIGHT)
		prog->scene->ambient_light.color.z = new_value;
}

static void	handle_mouse_move_lights(int y, float new_value, t_prog *prog)
{
	t_light_source	*light;

	if (y >= SLID_LIGHT_SELECT_H && y <= SLID_LIGHT_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_light = (int)(new_value
				* prog->scene->nb_lights);
	else if (prog->scene->selected_light == 0)
		handle_mouse_move_ambient_light(y, new_value, prog);
	else if (prog->scene->selected_light > 0)
	{
		light = &prog->scene->lights[prog->scene->selected_light - 1];
		if (y >= SLID_LIGHT_RATIO_H && y <= SLID_LIGHT_RATIO_H
			+ SLIDER_HEIGHT)
			light->ratio = new_value;
		else if (y >= SLID_LIGHT_R_H && y <= SLID_LIGHT_R_H + SLIDER_HEIGHT)
			light->material.albedo.x = new_value;
		else if (y >= SLID_LIGHT_G_H && y <= SLID_LIGHT_G_H + SLIDER_HEIGHT)
			light->material.albedo.y = new_value;
		else if (y >= SLID_LIGHT_B_H && y <= SLID_LIGHT_B_H + SLIDER_HEIGHT)
			light->material.albedo.z = new_value;
	}
}

static void	handle_mouse_move_materials(int y, float new_value, t_prog *prog)
{
	t_mat			*mat;

	mat = &prog->scene->materials[prog->scene->selected_material];
	if (y >= SLID_MAT_SELECT_H && y <= SLID_MAT_SELECT_H + SLIDER_HEIGHT)
		prog->scene->selected_material = (int)(new_value
				* (prog->scene->nb_materials - 1));
	else if (y >= SLID_MAT_RED_H && y <= SLID_MAT_RED_H + SLIDER_HEIGHT)
		mat->albedo.x = new_value;
	else if (y >= SLID_MAT_GREEN_H && y <= SLID_MAT_GREEN_H + SLIDER_HEIGHT)
		mat->albedo.y = new_value;
	else if (y >= SLID_MAT_BLUE_H && y <= SLID_MAT_BLUE_H + SLIDER_HEIGHT)
		mat->albedo.z = new_value;
	else if (y >= SLID_MAT_SHINI_H && y <= SLID_MAT_SHINI_H + SLIDER_HEIGHT)
		mat->shyniness = (int)(new_value * MAX_MAT_SHININESS);
	else if (y >= SLID_MAT_ROUGH_H && y <= SLID_MAT_ROUGH_H + SLIDER_HEIGHT)
		mat->roughtness = new_value;
	else if (y >= SLID_MAT_SPEC_H && y <= SLID_MAT_SPEC_H + SLIDER_HEIGHT)
		mat->spec_coef = new_value;
	else if (y >= SLID_MAT_EMIS_H && y <= SLID_MAT_EMIS_H + SLIDER_HEIGHT)
		mat->emission_power = new_value * MAX_EMISSION_POWER;
	else if (y >= SLID_MAT_CHECK_H && y <= SLID_MAT_CHECK_H + SLIDER_HEIGHT)
		mat->use_checker = (new_value > 0.5f);
}

int	handle_mouse_move(int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	float			new_value;

	win_btn = prog->win_button;
	if (!win_btn->is_dragging)
		return (0);
	x = fmax(SLIDER_X_POS, fmin(x, SLIDER_X_POS + SLIDER_WIDTH));
	new_value = (float)(x - SLIDER_X_POS) / SLIDER_WIDTH;
	new_value = fmaxf(0.0f, fminf(1.0f, new_value));
	if (win_btn->current_tab == TAB_LIGHTS)
		handle_mouse_move_lights(y, new_value, prog);
	else if (win_btn->current_tab == TAB_OBJECTS)
		handle_mouse_move_objects(y, new_value, prog, win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS
		&& prog->scene->nb_materials > 0)
		handle_mouse_move_materials(y, new_value, prog);
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
	return (0);
}

#endif
