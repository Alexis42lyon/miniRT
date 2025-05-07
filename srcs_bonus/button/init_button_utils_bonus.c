/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_button_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:54:08 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:03:25 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

static void	init_sphere_buttons_utils(t_win_button *win_btn, t_button *btns[8])
{
	btns[0] = &win_btn->sphere_buttons.x_plus;
	btns[1] = &win_btn->sphere_buttons.x_minus;
	btns[2] = &win_btn->sphere_buttons.y_plus;
	btns[3] = &win_btn->sphere_buttons.y_minus;
	btns[4] = &win_btn->sphere_buttons.z_plus;
	btns[5] = &win_btn->sphere_buttons.z_minus;
	btns[6] = &win_btn->sphere_buttons.diameter_plus;
	btns[7] = &win_btn->sphere_buttons.diameter_minus;
}

void	init_sphere_buttons(t_win_button *win_btn)
{
	int			i;
	t_button	*btns[8];

	init_sphere_buttons_utils(win_btn, btns);
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
	}
}

void	init_plane_buttons(t_win_button *win_btn)
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
	}
}

#endif
