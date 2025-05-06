/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:39:46 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	get_color_subtab(t_win_button *win_btn, int i, int *pixel)
{
	if ((int)win_btn->current_subtab == i)
		*pixel = ACTIVE_TAB_COLOR;
	else
		*pixel = TAB_COLOR;
}

static void	draw_tab_objects(t_win_button *win_btn, t_data *img)
{
	const int	stw = win_btn->width / SUB_COUNT;
	int			sx;
	int			i;
	int			j;
	int			k;

	sx = 0;
	i = -1;
	while (++i < SUB_COUNT)
	{
		j = sx;
		while (j < sx + stw)
		{
			k = TAB_HEIGHT - 1;
			while (++k < TAB_HEIGHT + 25)
			{
				get_color_subtab(win_btn, i, (int *)(img->addr
						+ (k * img->line_length + j
							* (img->bits_per_pixel / 8))));
			}
			j++;
		}
		sx += stw;
	}
}

static void	get_color_tab(t_win_button *win_btn, int i, int *pixel)
{
	if (win_btn->current_tab == (enum e_tab)i)
		*pixel = ACTIVE_TAB_COLOR;
	else
		*pixel = TAB_COLOR;
}

void	draw_tabs(t_data *img, t_win_button *win_btn)
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
				get_color_tab(win_btn, i, (int *)(img->addr
						+ k * img->line_length + j
						* (img->bits_per_pixel / 8)));
			}
		}
	}
	if (win_btn->current_tab == TAB_OBJECTS)
		draw_tab_objects(win_btn, img);
}

void	draw_light_pos_buttons(t_win_button *win_btn, t_data *img)
{
	draw_button(&win_btn->light_pos_buttons.x_plus, img);
	draw_button(&win_btn->light_pos_buttons.x_minus, img);
	draw_button(&win_btn->light_pos_buttons.y_plus, img);
	draw_button(&win_btn->light_pos_buttons.y_minus, img);
	draw_button(&win_btn->light_pos_buttons.z_plus, img);
	draw_button(&win_btn->light_pos_buttons.z_minus, img);
}

#endif
