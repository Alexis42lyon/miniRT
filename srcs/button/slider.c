/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:02:04 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 11:51:54 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

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
	slider_x = SLIDER_X_POS + (int)(value * (SLIDER_WIDTH - SLIDER_HANDLE_WIDTH));
	i = slider_x - 1;
	while (++i < slider_x + SLIDER_HANDLE_WIDTH)
	{
		j = y - 1;
		while (++j < y + SLIDER_HEIGHT)
			*(int *)(img->addr + j * img->line_length + i
					* (img->bits_per_pixel / 8)) = SLIDER_HANDLE_COLOR;
	}
}

#endif
