/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:54 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 00:31:36 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

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

static bool	is_click_on_button(int x, int y, t_button *btn)
{
	return (x >= btn->x && x <= btn->x + btn->width
		&& y >= btn->y && y <= btn->y + btn->height);
}

static void	handle_sphere_click(int x, int y, t_prog *prog,
	t_win_button *win_btn)
{
	t_sphere	*sphere;
	float		step;

	sphere = &prog->scene->spheres[prog->scene->selected_sphere];
	step = 0.1f;
	if (is_click_on_button(x, y, &win_btn->sphere_buttons.x_plus))
		sphere->origin.x += step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.x_minus))
		sphere->origin.x -= step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.y_plus))
		sphere->origin.y += step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.y_minus))
		sphere->origin.y -= step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.z_plus))
		sphere->origin.z += step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.z_minus))
		sphere->origin.z -= step;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.diameter_plus))
		sphere->radius += step / 2;
	else if (is_click_on_button(x, y, &win_btn->sphere_buttons.diameter_minus))
		sphere->radius = fmax(0.1f, sphere->radius - step / 2);
	else
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

static void	handle_plane_click(int x, int y, t_prog *prog,
	t_win_button *win_btn)
{
	t_plane	*plane;
	float	step;

	plane = &prog->scene->planes[prog->scene->selected_plane];
	step = 0.1f;
	if (is_click_on_button(x, y, &win_btn->plane_buttons.x_plus))
		plane->origin.x += step;
	else if (is_click_on_button(x, y, &win_btn->plane_buttons.x_minus))
		plane->origin.x -= step;
	else if (is_click_on_button(x, y, &win_btn->plane_buttons.y_plus))
		plane->origin.y += step;
	else if (is_click_on_button(x, y, &win_btn->plane_buttons.y_minus))
		plane->origin.y -= step;
	else if (is_click_on_button(x, y, &win_btn->plane_buttons.z_plus))
		plane->origin.z += step;
	else if (is_click_on_button(x, y, &win_btn->plane_buttons.z_minus))
		plane->origin.z -= step;
	else
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

static void	handle_cylinder_click(int x, int y, t_prog *prog,
	t_win_button *win_btn)
{
	t_cylinder	*cylinder;
	float		step;

	cylinder = &prog->scene->cylinders[prog->scene->selected_cylinder];
	step = 0.1f;
	if (is_click_on_button(x, y, &win_btn->cylinder_buttons.x_plus))
		cylinder->origin.x += step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.x_minus))
		cylinder->origin.x -= step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.y_plus))
		cylinder->origin.y += step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.y_minus))
		cylinder->origin.y -= step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.z_plus))
		cylinder->origin.z += step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.z_minus))
		cylinder->origin.z -= step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.diameter_plus))
		cylinder->radius += step / 2;
	else if (is_click_on_button(x, y,
			&win_btn->cylinder_buttons.diameter_minus))
		cylinder->radius = fmax(0.1f, cylinder->radius - step / 2);
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.height_plus))
		cylinder->height += step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.height_minus))
		cylinder->height = fmax(0.1f, cylinder->height - step);
	else
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

static void	handle_cone_click(int x, int y, t_prog *prog, t_win_button *win_btn)
{
	t_cylinder	*cone;
	float		step;

	cone = &prog->scene->cones[prog->scene->selected_cone];
	step = 0.1f;
	if (is_click_on_button(x, y, &win_btn->cone_buttons.x_plus))
		cone->origin.x += step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.x_minus))
		cone->origin.x -= step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.y_plus))
		cone->origin.y += step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.y_minus))
		cone->origin.y -= step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.z_plus))
		cone->origin.z += step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.z_minus))
		cone->origin.z -= step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.diameter_plus))
		cone->radius += step / 2;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.diameter_minus))
		cone->radius = fmax(0.1f, cone->radius - step / 2);
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.height_plus))
		cone->height += step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.height_minus))
		cone->height = fmax(0.1f, cone->height - step);
	else
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

static void	init_sphere_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[8];

	btns[0] = &win_btn->sphere_buttons.x_plus;
	btns[1] = &win_btn->sphere_buttons.x_minus;
	btns[2] = &win_btn->sphere_buttons.y_plus;
	btns[3] = &win_btn->sphere_buttons.y_minus;
	btns[4] = &win_btn->sphere_buttons.z_plus;
	btns[5] = &win_btn->sphere_buttons.z_minus;
	btns[6] = &win_btn->sphere_buttons.diameter_plus;
	btns[7] = &win_btn->sphere_buttons.diameter_minus;
	i = -1;
	while (++i < 8)
	{
		if (i % 2 == 0)
			btns[i]->x = SPHERE_SLIDER_X_POS;
		else
			btns[i]->x = SPHERE_SLIDER_X_POS + SPHERE_BUTTON_WIDTH + 5;
		if (i < 6)
			btns[i]->y = SPHERE_POS_Y_POS + (i / 2) * OFFSET_BUTTON;
		else
			btns[i]->y = SPHERE_DIAM_Y_POS;
		btns[i]->width = SPHERE_BUTTON_WIDTH;
		btns[i]->height = SPHERE_BUTTON_HEIGHT;
		if (i % 2 == 0)
			btns[i]->text = "+";
		else
			btns[i]->text = "-";
	}
}

static void	init_plane_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[6];

	btns[0] = &win_btn->plane_buttons.x_plus;
	btns[1] = &win_btn->plane_buttons.x_minus;
	btns[2] = &win_btn->plane_buttons.y_plus;
	btns[3] = &win_btn->plane_buttons.y_minus;
	btns[4] = &win_btn->plane_buttons.z_plus;
	btns[5] = &win_btn->plane_buttons.z_minus;
	i = -1;
	while (++i < 6)
	{
		if (i % 2 == 0)
			btns[i]->x = SPHERE_SLIDER_X_POS;
		else
			btns[i]->x = SPHERE_SLIDER_X_POS + SPHERE_BUTTON_WIDTH + 5;
		btns[i]->y = PLANE_POS_Y_POS + (i / 2) * OFFSET_BUTTON;
		btns[i]->width = SPHERE_BUTTON_WIDTH;
		btns[i]->height = SPHERE_BUTTON_HEIGHT;
		if (i % 2 == 0)
			btns[i]->text = "+";
		else
			btns[i]->text = "-";
	}
}

static void	init_cylinder_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[10];

	btns[0] = &win_btn->cylinder_buttons.x_plus;
	btns[1] = &win_btn->cylinder_buttons.x_minus;
	btns[2] = &win_btn->cylinder_buttons.y_plus;
	btns[3] = &win_btn->cylinder_buttons.y_minus;
	btns[4] = &win_btn->cylinder_buttons.z_plus;
	btns[5] = &win_btn->cylinder_buttons.z_minus;
	btns[6] = &win_btn->cylinder_buttons.diameter_plus;
	btns[7] = &win_btn->cylinder_buttons.diameter_minus;
	btns[8] = &win_btn->cylinder_buttons.height_plus;
	btns[9] = &win_btn->cylinder_buttons.height_minus;
	i = -1;
	while (++i < 10)
	{
		if (i % 2 == 0)
			btns[i]->x = SPHERE_SLIDER_X_POS;
		else
			btns[i]->x = SPHERE_SLIDER_X_POS + SPHERE_BUTTON_WIDTH + 5;
		if (i < 6)
			btns[i]->y = CYLINDER_POS_Y_POS + (i / 2) * OFFSET_BUTTON;
		else if (i < 8)
			btns[i]->y = CYLINDER_DIAMETER_Y_POS;
		else
			btns[i]->y = CYLINDER_HEIGHT_Y_POS;
		btns[i]->width = SPHERE_BUTTON_WIDTH;
		btns[i]->height = SPHERE_BUTTON_HEIGHT;
		if (i % 2 == 0)
			btns[i]->text = "+";
		else
			btns[i]->text = "-";
	}
}

static void	init_cone_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[10];

	btns[0] = &win_btn->cone_buttons.x_plus;
	btns[1] = &win_btn->cone_buttons.x_minus;
	btns[2] = &win_btn->cone_buttons.y_plus;
	btns[3] = &win_btn->cone_buttons.y_minus;
	btns[4] = &win_btn->cone_buttons.z_plus;
	btns[5] = &win_btn->cone_buttons.z_minus;
	btns[6] = &win_btn->cone_buttons.diameter_plus;
	btns[7] = &win_btn->cone_buttons.diameter_minus;
	btns[8] = &win_btn->cone_buttons.height_plus;
	btns[9] = &win_btn->cone_buttons.height_minus;
	i = -1;
	while (++i < 10)
	{
		if (i % 2 == 0)
			btns[i]->x = SPHERE_SLIDER_X_POS;
		else
			btns[i]->x = SPHERE_SLIDER_X_POS + SPHERE_BUTTON_WIDTH + 5;
		if (i < 6)
			btns[i]->y = CYLINDER_POS_Y_POS + (i / 2) * OFFSET_BUTTON;
		else if (i < 8)
			btns[i]->y = CYLINDER_DIAMETER_Y_POS;
		else
			btns[i]->y = CYLINDER_HEIGHT_Y_POS;
		btns[i]->width = SPHERE_BUTTON_WIDTH;
		btns[i]->height = SPHERE_BUTTON_HEIGHT;
		if (i % 2 == 0)
			btns[i]->text = "+";
		else
			btns[i]->text = "-";
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

void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y)
{
	const int	subtab_height = 25;
	const int	stw = win_btn->width / SUB_COUNT;
	int			sx;
	int			i;

	i = 0;
	while (i < TAB_COUNT)
	{
		if (x >= win_btn->tab_buttons[i].x
			&& x <= win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width
			&& y >= win_btn->tab_buttons[i].y
			&& y <= win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height)
		{
			win_btn->current_tab = i;
			draw_button_window(prog, win_btn);
			return ;
		}
		i++;
	}
	if (win_btn->current_tab == TAB_OBJECTS)
	{
		sx = 0;
		i = 0;
		while (i < SUB_COUNT)
		{
			if (x >= sx && x <= sx + stw
				&& y >= TAB_HEIGHT && y <= TAB_HEIGHT + subtab_height)
			{
				win_btn->current_subtab = i;
				draw_button_window(prog, win_btn);
				break ;
			}
			sx += stw;
			i++;
		}
	}
}

static void	draw_tab_objects(t_win_button *win_btn, t_data *img)
{
	const int	stw = win_btn->width / SUB_COUNT;
	int			sx;
	int			i;
	int			j;
	int			k;

	sx = 0;
	i = 0;
	while (i < SUB_COUNT)
	{
		j = sx;
		while (j < sx + stw)
		{
			k = TAB_HEIGHT;
			while (k < TAB_HEIGHT + 25)
			{
				if ((int)win_btn->current_subtab == i)
					*(int *)(img->addr + (k * img->line_length + j
								* (img->bits_per_pixel / 8)))
						= ACTIVE_TAB_COLOR;
				else
					*(int *)(img->addr + (k * img->line_length + j
								* (img->bits_per_pixel / 8)))
						= TAB_COLOR;
				k++;
			}
			j++;
		}
		sx += stw;
		i++;
	}
}

static void	draw_tabs(t_data *img, t_win_button *win_btn)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < TAB_COUNT)
	{
		j = win_btn->tab_buttons[i].x - 1;
		while (++j < win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width)
		{
			k = win_btn->tab_buttons[i].y - 1;
			while (++k < win_btn->tab_buttons[i].y
				+ win_btn->tab_buttons[i].height)
			{
				if (win_btn->current_tab == (enum e_tab)i)
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8))
						= ACTIVE_TAB_COLOR;
				else
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8))
						= TAB_COLOR;
			}
		}
	}
	if (win_btn->current_tab == TAB_OBJECTS)
		draw_tab_objects(win_btn, img);
}

static void	draw_light_pos_buttons(t_win_button *win_btn, t_data *img)
{
	draw_button(&win_btn->light_pos_buttons.x_plus, img);
	draw_button(&win_btn->light_pos_buttons.x_minus, img);
	draw_button(&win_btn->light_pos_buttons.y_plus, img);
	draw_button(&win_btn->light_pos_buttons.y_minus, img);
	draw_button(&win_btn->light_pos_buttons.z_plus, img);
	draw_button(&win_btn->light_pos_buttons.z_minus, img);
}

void	draw_button_window(t_prog *prog, t_win_button *win_btn)
{
	t_data			img;
	t_light_source	*light;
	t_mat			*mat;
	float			select_val;

	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_tabs(&img, win_btn);
	if (win_btn->current_tab == TAB_LIGHTS)
	{
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
	else if (win_btn->current_tab == TAB_OBJECTS)
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
	else if (win_btn->current_tab == TAB_MATERIALS
		&& prog->scene->nb_materials > 0)
	{
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
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
	put_string_win(prog, win_btn);
}

static int	handle_mouse_move(int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	float			new_value;
	t_light_source	*light;
	t_mat			*mat;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_cylinder		*cone;

	win_btn = prog->win_button;
	if (!win_btn->is_dragging)
		return (0);
	x = fmax(SLIDER_X_POS, fmin(x, SLIDER_X_POS + SLIDER_WIDTH));
	new_value = (float)(x - SLIDER_X_POS) / SLIDER_WIDTH;
	new_value = fmaxf(0.0f, fminf(1.0f, new_value));
	if (win_btn->current_tab == TAB_LIGHTS)
	{
		if (y >= SLID_LIGHT_SELECT_H
			&& y <= SLID_LIGHT_SELECT_H + SLIDER_HEIGHT)
			prog->scene->selected_light = (int)(new_value
					* prog->scene->nb_lights);
		else if (prog->scene->selected_light == 0)
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
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_SPHERE)
	{
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
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_PLANE)
	{
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
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_CYLINDER)
	{
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
	else if (win_btn->current_tab == TAB_OBJECTS
		&& win_btn->current_subtab == SUB_CONE)
	{
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
	else if (win_btn->current_tab == TAB_MATERIALS
		&& prog->scene->nb_materials > 0)
	{
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
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
	return (0);
}

static int	handle_button_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	t_light_source	*light;
	float			step;

	win_btn = prog->win_button;
	if (button == 1)
	{
		handle_tabs(prog, win_btn, x, y);
		if (x >= SLIDER_X_POS && x <= SLIDER_X_POS + SLIDER_WIDTH)
		{
			if (win_btn->current_tab == TAB_LIGHTS)
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
			else if (win_btn->current_tab == TAB_OBJECTS
				&& win_btn->current_subtab == SUB_SPHERE)
			{
				if (y >= SPHERE_MAT_SELEC_H
					&& y <= SPHERE_MAT_SELEC_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
				if (y >= SLID_SPHERE_SELECT_H
					&& y <= SLID_SPHERE_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
			}
			else if (win_btn->current_tab == TAB_OBJECTS
				&& win_btn->current_subtab == SUB_PLANE)
			{
				if (y >= PLANE_MAT_SELECT_H
					&& y <= PLANE_MAT_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
				if (y >= SLID_PLANE_SELECT_H
					&& y <= SLID_PLANE_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
			}
			else if (win_btn->current_tab == TAB_OBJECTS
				&& win_btn->current_subtab == SUB_CYLINDER)
			{
				if (y >= CYLINDER_MAT_SELECT_H
					&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
				if (y >= SLID_CYLINDER_SELECT_H
					&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
			}
			else if (win_btn->current_tab == TAB_OBJECTS
				&& win_btn->current_subtab == SUB_CONE)
			{
				if (y >= CYLINDER_MAT_SELECT_H
					&& y <= CYLINDER_MAT_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
				if (y >= SLID_CYLINDER_SELECT_H
					&& y <= SLID_CYLINDER_SELECT_H + SLIDER_HEIGHT)
					win_btn->is_dragging = 1;
			}
			else if (win_btn->current_tab == TAB_MATERIALS
				&& prog->scene->nb_materials > 0)
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
		}
	}
	if (button == 1 && win_btn->current_tab == TAB_LIGHTS
		&& prog->scene->selected_light > 0)
	{
		light = &prog->scene->lights[prog->scene->selected_light - 1];
		step = 0.5f;
		if (is_click_on_button(x, y, &win_btn->light_pos_buttons.x_plus))
			light->origin.x += step;
		else if (is_click_on_button(x, y, &win_btn->light_pos_buttons.x_minus))
			light->origin.x -= step;
		else if (is_click_on_button(x, y, &win_btn->light_pos_buttons.y_plus))
			light->origin.y += step;
		else if (is_click_on_button(x, y, &win_btn->light_pos_buttons.y_minus))
			light->origin.y -= step;
		else if (is_click_on_button(x, y, &win_btn->light_pos_buttons.z_plus))
			light->origin.z += step;
		else if (is_click_on_button(x, y, &win_btn->light_pos_buttons.z_minus))
			light->origin.z -= step;
		else
			return (0);
		draw_button_window(prog, win_btn);
		reset_accumulation(prog);
		return (1);
	}
	else if (button == 1 && win_btn->current_tab == TAB_OBJECTS)
	{
		if (win_btn->current_subtab == SUB_SPHERE)
			handle_sphere_click(x, y, prog, win_btn);
		else if (win_btn->current_subtab == SUB_PLANE)
			handle_plane_click(x, y, prog, win_btn);
		else if (win_btn->current_subtab == SUB_CYLINDER)
			handle_cylinder_click(x, y, prog, win_btn);
		else if (win_btn->current_subtab == SUB_CONE)
			handle_cone_click(x, y, prog, win_btn);
	}
	return (0);
}

static int	handle_mouse_up(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	(void)button;
	prog->win_button->is_dragging = 0;
	return (0);
}

static int	key_hook_btn(int keycode, t_prog *prog)
{
	if (keycode == ESC)
		free_all(prog);
	return (0);
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;
	const float		tab_width = CONTROL_WINDOW_WIDTH / TAB_COUNT;
	int				x;
	char			*text;
	t_button		*btns[6];

	if (HEIGHT < 250)
	{
		ft_log(ERROR,
			"Error: Window height is too small for panel control.");
		return ;
	}
	win_btn = prog->win_button;
	*win_btn = (t_win_button)
	{
		.width = CONTROL_WINDOW_WIDTH,
		.height = HEIGHT,
		.mlx_ptr = prog->win_scene->mlx_ptr,
		.win_ptr = mlx_new_window(prog->win_scene->mlx_ptr,
			CONTROL_WINDOW_WIDTH, prog->win_scene->height, "Control Panel"),
		.current_tab = TAB_LIGHTS,
		.is_dragging = 0,
	};
	i = -1;
	while (++i < TAB_COUNT)
	{
		win_btn->tab_buttons[i] = (t_button)
		{
			.x = i * tab_width,
			.y = 0,
			.width = tab_width,
			.height = TAB_HEIGHT,
			.text = (char *[]){"Lights", "Objects", "Materials"}[i]
		};
	}
	btns[0] = &win_btn->light_pos_buttons.x_plus;
	btns[1] = &win_btn->light_pos_buttons.x_minus;
	btns[2] = &win_btn->light_pos_buttons.y_plus;
	btns[3] = &win_btn->light_pos_buttons.y_minus;
	btns[4] = &win_btn->light_pos_buttons.z_plus;
	btns[5] = &win_btn->light_pos_buttons.z_minus;
	i = -1;
	while (++i < 6)
	{
		if (i % 2 == 0)
		{
			x = SLIDER_X_POS;
			text = "+";
		}
		else
		{
			x = SLIDER_X_POS + LIGHT_POS_BUTTON_WIDTH + 5;
			text = "-";
		}
		*btns[i] = (t_button)
		{
			.x = x,
			.y = LIGHT_POS_Y_POS + OFFSET_BUTTON * (i / 2),
			.width = LIGHT_POS_BUTTON_WIDTH,
			.height = LIGHT_POS_BUTTON_HEIGHT,
			.text = text
		};
	}
	init_sphere_buttons(win_btn);
	init_plane_buttons(win_btn);
	init_cylinder_buttons(win_btn);
	init_cone_buttons(win_btn);
	mlx_hook(win_btn->win_ptr, 2, 1L << 0, key_hook_btn, prog);
	mlx_hook(win_btn->win_ptr, 17, 0, window_close, prog);
	mlx_hook(win_btn->win_ptr, 4, 1L << 2, handle_button_click, prog);
	mlx_hook(win_btn->win_ptr, 6, 1L << 6, handle_mouse_move, prog);
	mlx_hook(win_btn->win_ptr, 5, 1L << 3, handle_mouse_up, prog);
	draw_button_window(prog, win_btn);
}

#else

void	init_button_window(t_prog *prog)
{
	(void)prog;
}

#endif
