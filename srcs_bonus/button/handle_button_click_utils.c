/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_button_click_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:16:59 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 12:18:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static int	handle_cylinder_click_utils(int x, int y,
	t_win_button *win_btn, t_cylinder *cylinder)
{
	const float	step = 0.1f;

	if (is_click_on_button(x, y,
			&win_btn->cylinder_buttons.diameter_minus))
		cylinder->radius = fmax(step, cylinder->radius - step / 2);
	else if (is_click_on_button(x, y,
			&win_btn->cylinder_buttons.height_plus))
		cylinder->height += step;
	else if (is_click_on_button(x, y, &win_btn->cylinder_buttons.height_minus))
		cylinder->height = fmax(step, cylinder->height - step);
	else
		return (1);
	return (0);
}

void	handle_cylinder_click(int x, int y, t_prog *prog,
	t_win_button *win_btn)
{
	t_cylinder	*cylinder;
	const float	step = 0.1f;

	cylinder = &prog->scene->cylinders[prog->scene->selected_cylinder];
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
	else if (handle_cylinder_click_utils(x, y, win_btn, cylinder))
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

static int	handle_cone_click_utils(int x, int y,
	t_win_button *win_btn, t_cylinder *cone)
{
	const float	step = 0.1f;

	if (is_click_on_button(x, y, &win_btn->cone_buttons.height_plus))
		cone->height += step;
	else if (is_click_on_button(x, y, &win_btn->cone_buttons.height_minus))
		cone->height = fmax(0.1f, cone->height - step);
	else
		return (1);
	return (0);
}

void	handle_cone_click(int x, int y, t_prog *prog, t_win_button *win_btn)
{
	t_cylinder	*cone;
	const float	step = 0.1f;

	cone = &prog->scene->cones[prog->scene->selected_cone];
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
	else if (handle_cone_click_utils(x, y, win_btn, cone))
		return ;
	draw_button_window(prog, win_btn);
	reset_accumulation(prog);
}

#endif
