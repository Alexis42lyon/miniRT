/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:54 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 14:52:57 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

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
								* (img->bits_per_pixel / 8))) = TAB_COLOR;
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
	int		i;
	int		j;
	int		k;

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
							* (img->bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
				else
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8)) = TAB_COLOR;
			}
		}
	}
	if (win_btn->current_tab == TAB_OBJECTS)
		draw_tab_objects(win_btn, img);
}

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
				*(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
			else
				*(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)) = TAB_COLOR;
		}
	}
}

static void draw_light_pos_buttons(t_win_button *win_btn, t_data *img)
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
	t_data img;

	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_tabs(&img, win_btn);
	if (win_btn->current_tab == TAB_LIGHTS)
	{
		draw_slider(SLIDER_LIGHT_SELECTOR_HEIGHT,
				(float)prog->scene->selected_light/prog->scene->nb_lights,
				&img);
		if (prog->scene->selected_light == 0)
		{
			draw_slider(SLIDER_LIGHT_RATIO_HEIGHT, prog->scene->ambient_light.ratio, &img);
			draw_slider(SLIDER_LIGHT_RED_HEIGHT, prog->scene->ambient_light.color.x, &img);
			draw_slider(SLIDER_LIGHT_GREEN_HEIGHT, prog->scene->ambient_light.color.y, &img);
			draw_slider(SLIDER_LIGHT_BLUE_HEIGHT, prog->scene->ambient_light.color.z, &img);
		}
		else if (prog->scene->selected_light <= (prog->scene->nb_lights))
		{
			t_light_source *light = &prog->scene->lights[prog->scene->selected_light - 1];
			draw_slider(SLIDER_LIGHT_RATIO_HEIGHT, light->ratio, &img);
			draw_slider(SLIDER_LIGHT_RED_HEIGHT, light->material.albedo.x, &img);
			draw_slider(SLIDER_LIGHT_GREEN_HEIGHT, light->material.albedo.y, &img);
			draw_slider(SLIDER_LIGHT_BLUE_HEIGHT, light->material.albedo.z, &img);
		}
		if (prog->scene->selected_light > 0)
			draw_light_pos_buttons(win_btn, &img);
	}
	else if (win_btn->current_tab == TAB_MATERIALS && prog->scene->nb_materials > 0)
	{
		t_mat *mat = &prog->scene->materials[prog->scene->selected_material];
		float select_val = (float)prog->scene->selected_material /
						(prog->scene->nb_materials - 1);
		draw_slider(SLIDER_MAT_SELECTOR_HEIGHT, select_val, &img);
		draw_slider(SLIDER_MAT_RED_HEIGHT, mat->albedo.x, &img);
		draw_slider(SLIDER_MAT_GREEN_HEIGHT, mat->albedo.y, &img);
		draw_slider(SLIDER_MAT_BLUE_HEIGHT, mat->albedo.z, &img);
		draw_slider(SLIDER_MAT_SHININESS_HEIGHT, (float)mat->shyniness / MAX_MAT_SHININESS, &img);
		draw_slider(SLIDER_MAT_ROUGHNESS_HEIGHT, mat->roughtness, &img);
		draw_slider(SLIDER_MAT_SPEC_COEF_HEIGHT, mat->spec_coef, &img);
		draw_slider(SLIDER_MAT_EMISSION_HEIGHT, mat->emission_power / MAX_EMISSION_POWER, &img);
		if (mat->use_checker)
			draw_slider(SLIDER_MAT_CHECKER_HEIGHT, 1.0f, &img);
		else
			draw_slider(SLIDER_MAT_CHECKER_HEIGHT, 0.0f, &img);
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

	win_btn = prog->win_button;
	if (!win_btn->is_dragging)
		return (0);
	x = fmax(SLIDER_X_POS, fmin(x, SLIDER_X_POS + SLIDER_WIDTH));
	new_value = (float)(x - SLIDER_X_POS) / SLIDER_WIDTH;
	new_value = fmaxf(0.0f, fminf(1.0f, new_value));
	if (win_btn->current_tab == TAB_LIGHTS)
	{
		if (y >= SLIDER_LIGHT_SELECTOR_HEIGHT && y <= SLIDER_LIGHT_SELECTOR_HEIGHT + SLIDER_HEIGHT)
			prog->scene->selected_light = (int)(new_value * prog->scene->nb_lights);
		else if (prog->scene->selected_light == 0)
		{
			if (y >= SLIDER_LIGHT_RATIO_HEIGHT && y <= SLIDER_LIGHT_RATIO_HEIGHT + SLIDER_HEIGHT)
				prog->scene->ambient_light.ratio = new_value;
			else if (y >= SLIDER_LIGHT_RED_HEIGHT && y <= SLIDER_LIGHT_RED_HEIGHT + SLIDER_HEIGHT)
				prog->scene->ambient_light.color.x = new_value;
			else if (y >= SLIDER_LIGHT_GREEN_HEIGHT && y <= SLIDER_LIGHT_GREEN_HEIGHT + SLIDER_HEIGHT)
				prog->scene->ambient_light.color.y = new_value;
			else if (y >= SLIDER_LIGHT_BLUE_HEIGHT && y <= SLIDER_LIGHT_BLUE_HEIGHT + SLIDER_HEIGHT)
				prog->scene->ambient_light.color.z = new_value;
		}
		else if (prog->scene->selected_light > 0)
		{
			light = &prog->scene->lights[prog->scene->selected_light - 1];
			if (y >= SLIDER_LIGHT_RATIO_HEIGHT && y <= SLIDER_LIGHT_RATIO_HEIGHT + SLIDER_HEIGHT)
				light->ratio = new_value;
			else if (y >= SLIDER_LIGHT_RED_HEIGHT && y <= SLIDER_LIGHT_RED_HEIGHT + SLIDER_HEIGHT)
				light->material.albedo.x = new_value;
			else if (y >= SLIDER_LIGHT_GREEN_HEIGHT && y <= SLIDER_LIGHT_GREEN_HEIGHT + SLIDER_HEIGHT)
				light->material.albedo.y = new_value;
			else if (y >= SLIDER_LIGHT_BLUE_HEIGHT && y <= SLIDER_LIGHT_BLUE_HEIGHT + SLIDER_HEIGHT)
				light->material.albedo.z = new_value;
		}
	}
	else if (win_btn->current_tab == TAB_MATERIALS && prog->scene->nb_materials > 0)
	{
		mat = &prog->scene->materials[prog->scene->selected_material];
		if (y >= SLIDER_MAT_SELECTOR_HEIGHT && y <= SLIDER_MAT_SELECTOR_HEIGHT + SLIDER_HEIGHT)
			prog->scene->selected_material = (int)(new_value * (prog->scene->nb_materials - 1));
		else if (y >= SLIDER_MAT_RED_HEIGHT && y <= SLIDER_MAT_RED_HEIGHT + SLIDER_HEIGHT)
			mat->albedo.x = new_value;
		else if (y >= SLIDER_MAT_GREEN_HEIGHT && y <= SLIDER_MAT_GREEN_HEIGHT + SLIDER_HEIGHT)
			mat->albedo.y = new_value;
		else if (y >= SLIDER_MAT_BLUE_HEIGHT && y <= SLIDER_MAT_BLUE_HEIGHT + SLIDER_HEIGHT)
			mat->albedo.z = new_value;
		else if (y >= SLIDER_MAT_SHININESS_HEIGHT && y <= SLIDER_MAT_SHININESS_HEIGHT + SLIDER_HEIGHT)
			mat->shyniness = (int)(new_value * MAX_MAT_SHININESS);
		else if (y >= SLIDER_MAT_ROUGHNESS_HEIGHT && y <= SLIDER_MAT_ROUGHNESS_HEIGHT + SLIDER_HEIGHT)
			mat->roughtness = new_value;
		else if (y >= SLIDER_MAT_SPEC_COEF_HEIGHT && y <= SLIDER_MAT_SPEC_COEF_HEIGHT + SLIDER_HEIGHT)
			mat->spec_coef = new_value;
		else if (y >= SLIDER_MAT_EMISSION_HEIGHT && y <= SLIDER_MAT_EMISSION_HEIGHT + SLIDER_HEIGHT)
			mat->emission_power = new_value * MAX_EMISSION_POWER;
		else if (y >= SLIDER_MAT_CHECKER_HEIGHT && y <= SLIDER_MAT_CHECKER_HEIGHT + SLIDER_HEIGHT)
			mat->use_checker = (new_value > 0.5f);
	}
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
	return (0);
}

static bool is_click_on_button(int x, int y, t_button *btn)
{
	return (x >= btn->x && x <= btn->x + btn->width &&
			y >= btn->y && y <= btn->y + btn->height);
}

static int handle_button_click(int button, int x, int y, t_prog *prog)
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
				if ((y >= SLIDER_LIGHT_SELECTOR_HEIGHT && y <= SLIDER_LIGHT_SELECTOR_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_LIGHT_RATIO_HEIGHT && y <= SLIDER_LIGHT_RATIO_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_LIGHT_RED_HEIGHT && y <= SLIDER_LIGHT_RED_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_LIGHT_GREEN_HEIGHT && y <= SLIDER_LIGHT_GREEN_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_LIGHT_BLUE_HEIGHT && y <= SLIDER_LIGHT_BLUE_HEIGHT + SLIDER_HEIGHT))
				{
					win_btn->is_dragging = 1;
				}
			}
			else if (win_btn->current_tab == TAB_MATERIALS && prog->scene->nb_materials > 0)
			{
				if ((y >= SLIDER_MAT_SELECTOR_HEIGHT && y <= SLIDER_MAT_SELECTOR_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_RED_HEIGHT && y <= SLIDER_MAT_RED_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_GREEN_HEIGHT && y <= SLIDER_MAT_GREEN_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_BLUE_HEIGHT && y <= SLIDER_MAT_BLUE_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_SHININESS_HEIGHT && y <= SLIDER_MAT_SHININESS_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_ROUGHNESS_HEIGHT && y <= SLIDER_MAT_ROUGHNESS_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_SPEC_COEF_HEIGHT && y <= SLIDER_MAT_SPEC_COEF_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_EMISSION_HEIGHT && y <= SLIDER_MAT_EMISSION_HEIGHT + SLIDER_HEIGHT) ||
					(y >= SLIDER_MAT_CHECKER_HEIGHT && y <= SLIDER_MAT_CHECKER_HEIGHT + SLIDER_HEIGHT))
				{
					win_btn->is_dragging = 1;
				}
			}
		}
	}
	if (button == 1 && win_btn->current_tab == TAB_LIGHTS && prog->scene->selected_light > 0)
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

	if (HEIGHT < 250)
	{
		ft_dprintf(2, RED
			"Error: Window height is too small for panel control.\n", RESET);
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
	t_button *btns[6] = {
		&win_btn->light_pos_buttons.x_plus,
		&win_btn->light_pos_buttons.x_minus,
		&win_btn->light_pos_buttons.y_plus,
		&win_btn->light_pos_buttons.y_minus,
		&win_btn->light_pos_buttons.z_plus,
		&win_btn->light_pos_buttons.z_minus
	};
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
