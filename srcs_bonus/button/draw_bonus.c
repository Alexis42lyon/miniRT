/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:33:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:01:07 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

void	draw_button(t_button *btn, t_data *img)
{
	int	x;
	int	y;

	y = btn->y - 1;
	while (++y < btn->y + btn->height)
	{
		x = btn->x - 1;
		while (++x < btn->x + btn->width)
		{
			if (btn->is_hovered)
				*(int *)(img->addr + y * img->line_length + x
						* (img->bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
			else
				*(int *)(img->addr + y * img->line_length + x
						* (img->bits_per_pixel / 8)) = TAB_COLOR;
		}
	}
}

void	draw_slider(int y, float value, t_data *img)
{
	int	i;
	int	j;
	int	slider_x;

	i = -1;
	while (++i < SLIDER_WIDTH)
	{
		j = -1;
		while (++j < SLIDER_HEIGHT)
			*(int *)(img->addr + (y + j) * img->line_length + (SLIDER_X_POS + i)
					* (img->bits_per_pixel / 8)) = SLIDER_COLOR;
	}
	slider_x = SLIDER_X_POS + (int)(value
			* (SLIDER_WIDTH - SLIDER_HANDLE_WIDTH));
	i = slider_x - 1;
	while (++i < slider_x + SLIDER_HANDLE_WIDTH)
	{
		j = y - 1;
		while (++j < y + SLIDER_HEIGHT)
			*(int *)(img->addr + j * img->line_length + i
					* (img->bits_per_pixel / 8)) = SLIDER_HANDLE_COLOR;
	}
}

static void	draw_tab_lights(t_prog *prog, t_data img, t_win_button *win_btn)
{
	t_light_source	*light;

	draw_slider(SLID_LIGHT_SELECT_H,
		(float)prog->scene->selected_light / prog->scene->nb_lights, &img);
	if (prog->scene->selected_light == 0)
	{
		draw_slider(SLID_LIGHT_RATIO_H, prog->scene->ambient_light.ratio,
			&img);
		draw_slider(SLID_LIGHT_R_H, prog->scene->ambient_light.color.x,
			&img);
		draw_slider(SLID_LIGHT_G_H, prog->scene->ambient_light.color.y,
			&img);
		draw_slider(SLID_LIGHT_B_H, prog->scene->ambient_light.color.z,
			&img);
	}
	else if (prog->scene->selected_light <= (prog->scene->nb_lights))
	{
		light = &prog->scene->lights[prog->scene->selected_light - 1];
		draw_slider(SLID_LIGHT_RATIO_H, light->ratio, &img);
		draw_slider(SLID_LIGHT_R_H, light->material.albedo.x, &img);
		draw_slider(SLID_LIGHT_G_H, light->material.albedo.y, &img);
		draw_slider(SLID_LIGHT_B_H, light->material.albedo.z, &img);
	}
	if (prog->scene->selected_light > 0)
		draw_light_pos_buttons(win_btn, &img);
}

static void	draw_tab_materials(t_prog *prog, t_data img)
{
	t_mat			*mat;
	float			select_val;

	mat = &prog->scene->materials[prog->scene->selected_material];
	select_val = (float)prog->scene->selected_material
		/ (prog->scene->nb_materials - 1);
	draw_slider(SLID_MAT_SELECT_H, select_val, &img);
	draw_slider(SLID_MAT_RED_H, mat->albedo.x, &img);
	draw_slider(SLID_MAT_GREEN_H, mat->albedo.y, &img);
	draw_slider(SLID_MAT_BLUE_H, mat->albedo.z, &img);
	draw_slider(SLID_MAT_SHINI_H,
		(float)mat->shyniness / MAX_MAT_SHININESS, &img);
	draw_slider(SLID_MAT_ROUGH_H, mat->roughtness, &img);
	draw_slider(SLID_MAT_SPEC_H, mat->spec_coef, &img);
	draw_slider(SLID_MAT_EMIS_H, mat->emission_power
		/ MAX_EMISSION_POWER, &img);
	if (mat->use_checker)
		draw_slider(SLID_MAT_CHECK_H, 1.0f, &img);
	else
		draw_slider(SLID_MAT_CHECK_H, 0.0f, &img);
}

void	draw_button_window(t_prog *prog, t_win_button *win_btn)
{
	t_data			img;

	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	if (!img.img)
		print_exit(prog, "Failed to create control window image.");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	if (!img.addr)
	{
		mlx_destroy_image(win_btn->mlx_ptr, img.img);
		print_exit(prog, "Failed to get control window image data.");
	}
	draw_tabs(&img, win_btn);
	if (win_btn->current_tab == TAB_LIGHTS)
		draw_tab_lights(prog, img, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		draw_objects_controls(prog, win_btn, img);
	else if (win_btn->current_tab == TAB_MATERIALS
		&& prog->scene->nb_materials > 0)
		draw_tab_materials(prog, img);
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
	put_string_win(prog, win_btn);
}

#endif
