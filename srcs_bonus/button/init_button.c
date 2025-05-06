/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:54:01 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 12:58:40 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	init_cylinder_buttons_utils(t_win_button *win_btn,
	t_button *btns[10])
{
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
}

void	init_cylinder_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[10];

	init_cylinder_buttons_utils(win_btn, btns);
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
	}
}

static void	init_cone_buttons_utils(t_win_button *win_btn, t_button *btns[10])
{
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
}

void	init_cone_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[10];

	init_cone_buttons_utils(win_btn, btns);
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
	}
}

void	init_button(t_win_button *win_btn, t_button *btns[6])
{
	int		i;
	int		x;

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
			x = SLIDER_X_POS;
		else
			x = SLIDER_X_POS + LIGHT_POS_BUTTON_WIDTH + 5;
		*btns[i] = (t_button)
		{
			.x = x,
			.y = LIGHT_POS_Y_POS + OFFSET_BUTTON * (i / 2),
			.width = LIGHT_POS_BUTTON_WIDTH,
			.height = LIGHT_POS_BUTTON_HEIGHT,
		};
	}
}

#endif
