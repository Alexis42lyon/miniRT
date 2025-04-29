/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:44 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/29 18:43:07 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "button.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static void	handle_sub_tabs(t_prog *prog, t_win_button *win_btn)
{
	int			i;
	const int	stw = (win_btn->width - 30) / SUB_COUNT;
	int			sx;

	i = -1;
	sx = 15;
	while (++i < SUB_COUNT)
	{
		if ((int)win_btn->current_subtab == i)
		{
			win_btn->current_subtab = i;
			draw_button_window(prog, win_btn);
			return ;
		}
		sx += stw + 5;
	}
}

void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y)
{
	int	i;

	i = -1;
	while (++i < TAB_COUNT)
	{
		if (x >= win_btn->tab_buttons[i].x
			&& x <= win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width
			&& y >= win_btn->tab_buttons[i].y
			&& y <= win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height)
		{
			win_btn->current_tab = i;
			draw_button_window(prog, win_btn);
			break ;
		}
	}
	if (win_btn->current_tab == TAB_OBJECTS && y > TAB_HEIGHT
		&& y < TAB_HEIGHT + 30)
		handle_sub_tabs(prog, win_btn);
}
