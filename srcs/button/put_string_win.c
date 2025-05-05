/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:20:06 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 16:27:27 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	put_mat_info(t_win_button *win_btn, t_mat *mat)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(mat->albedo.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_RED_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(mat->albedo.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_GREEN_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(mat->albedo.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_BLUE_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Shininess: %d", mat->shyniness);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_SHININESS_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Roughness: %.2f", mat->roughtness);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_ROUGHNESS_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Spec Coef: %.2f", mat->spec_coef);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_SPEC_COEF_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Emission: %.2f", mat->emission_power);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_EMISSION_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	if (mat->use_checker)
		snprintf(buffer, sizeof(buffer), "Checker: %s", "ON");
	else
		snprintf(buffer, sizeof(buffer), "Checker: %s", "OFF");
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_MAT_CHECKER_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_string_materials(t_prog *prog, t_win_button *win_btn)
{
	char	buffer[50];
	t_mat	*mat;

	if (prog->scene->nb_materials == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_MAT_SELECTOR_HEIGHT + TEXT_Y_OFFSET,
			TEXT_COLOR, "No materials");
		return ;
	}
	if (prog->scene->selected_material < prog->scene->nb_materials)
	{
		snprintf(buffer, sizeof(buffer), "%s",
			prog->scene->materials[prog->scene->selected_material].name);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_MAT_SELECTOR_HEIGHT + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		mat = &prog->scene->materials[prog->scene->selected_material];
		put_mat_info(win_btn, mat);
	}
}

static void	put_string_objects(t_win_button *win_btn)
{
	const int	stw = (win_btn->width - 30) / SUB_COUNT;
	int			sx;
	int			i;

	sx = 15;
	i = -1;
	while (++i < SUB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, sx + 5,
			TAB_HEIGHT + 15, TEXT_COLOR,
			(char *[]){"Sphere", "Plane", "Cylinder", "Cone"}[i]);
		sx += stw + 5;
	}
}

static void	put_light_info(t_win_button *win_btn, t_light_source *light)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_RATIO_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(light->material.albedo.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_RED_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(light->material.albedo.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_GREEN_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(light->material.albedo.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_BLUE_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Pos x: % .2f      +   -", light->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_BLUE_HEIGHT + 20 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Pos y: % .2f      +   -", light->origin.y);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_LIGHT_BLUE_HEIGHT + 40 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Pos z: % .2f      +   -", light->origin.z);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_LIGHT_BLUE_HEIGHT + 60 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_ambient_info(t_ambient_light *light, t_win_button *win_btn)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_RATIO_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(light->color.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_RED_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(light->color.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_GREEN_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(light->color.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLIDER_LIGHT_BLUE_HEIGHT + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_string_lights(t_prog *prog, t_win_button *win_btn)
{
	char			buffer[50];
	t_light_source	*light;

	if (prog->scene->selected_light == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_LIGHT_SELECTOR_HEIGHT + TEXT_Y_OFFSET,
			TEXT_COLOR, "Ambient Light");
		put_ambient_info(&prog->scene->ambient_light, win_btn);
	}
	else
	{
		snprintf(buffer, sizeof(buffer), "Light %ld", prog->scene->selected_light);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLIDER_LIGHT_SELECTOR_HEIGHT + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		light = &prog->scene->lights[prog->scene->selected_light - 1];
			put_light_info(win_btn, light);
	}
}

void	put_string_win(t_prog *prog, t_win_button *win_btn)
{
	int	i;

	i = -1;
	while (++i < TAB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 30 - i * 2,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, win_btn->tab_buttons[i].text);
	}
	if (win_btn->current_tab == TAB_LIGHTS)
		put_string_lights(prog, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		put_string_objects(win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS)
		put_string_materials(prog, win_btn);
}

#endif
