/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tabs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:59:40 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:03:11 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

static void	handle_tabs_objects(t_prog *prog, t_win_button *win_btn, int x,
	int y)
{
	int			sx;
	int			i;
	const int	subtab_height = 25;
	const int	stw = win_btn->width / SUB_COUNT;

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

void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y)
{
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
		handle_tabs_objects(prog, win_btn, x, y);
	if (x >= SLIDER_X_POS && x <= SLIDER_X_POS + SLIDER_WIDTH)
		handle_dragging_slider(y, win_btn, prog);
}

#endif
