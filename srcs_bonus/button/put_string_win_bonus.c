/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_win_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:20:06 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:04:00 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include <stdio.h>

static void	put_string_materials(t_prog *prog, t_win_button *win_btn)
{
	char	buffer[50];
	t_mat	*mat;

	if (prog->scene->nb_materials == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_MAT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, "No materials");
		return ;
	}
	if (prog->scene->selected_material < prog->scene->nb_materials)
	{
		snprintf(buffer, sizeof(buffer), "%s",
			prog->scene->materials[prog->scene->selected_material].name);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_MAT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		mat = &prog->scene->materials[prog->scene->selected_material];
		put_mat_info(win_btn, mat);
	}
}

static void	put_light_info(t_win_button *win_btn, t_light_source *light)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Red: %d",
		(int)(light->material.albedo.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_R_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d",
		(int)(light->material.albedo.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_G_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d",
		(int)(light->material.albedo.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", light->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 20 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", light->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 40 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", light->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 60 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_ambient_info(t_ambient_light *light, t_win_button *win_btn)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_RATIO_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(light->color.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_R_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(light->color.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_G_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(light->color.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_string_lights(t_prog *prog, t_win_button *win_btn)
{
	char			buffer[50];
	t_light_source	*light;

	if (prog->scene->selected_light == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, "Ambient Light");
		put_ambient_info(&prog->scene->ambient_light, win_btn);
	}
	else
	{
		snprintf(buffer, sizeof(buffer),
			"Light %ld", prog->scene->selected_light);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		light = &prog->scene->lights[prog->scene->selected_light - 1];
		snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_RATIO_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
		put_light_info(win_btn, light);
	}
}

void	put_string_win(t_prog *prog, t_win_button *win_btn)
{
	int		i;
	char	*text[3];

	text[0] = "Lights";
	text[1] = "Objects";
	text[2] = "Materials";
	i = -1;
	while (++i < TAB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 30 - i * 2,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, text[i]);
	}
	if (win_btn->current_tab == TAB_LIGHTS)
		put_string_lights(prog, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		put_string_objects(prog, win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS)
		put_string_materials(prog, win_btn);
}

#endif
