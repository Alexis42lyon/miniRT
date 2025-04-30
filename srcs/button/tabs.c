/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:44 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/30 11:19:22 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "button.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

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
