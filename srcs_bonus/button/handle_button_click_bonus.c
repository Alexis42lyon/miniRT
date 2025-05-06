/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_button_click_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

bool	is_click_on_button(int x, int y, t_button *btn)
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

static void	handle_button_click_light(int x, int y, t_prog *prog,
	t_win_button *win_btn)
{
	t_light_source	*light;
	const float		step = 0.5f;

	light = &prog->scene->lights[prog->scene->selected_light - 1];
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
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

int	handle_button_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;

	win_btn = prog->win_button;
	if (button == 1)
		handle_tabs(prog, win_btn, x, y);
	if (button == 1 && win_btn->current_tab == TAB_LIGHTS
		&& prog->scene->selected_light > 0)
	{
		handle_button_click_light(x, y, prog, win_btn);
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

#endif
