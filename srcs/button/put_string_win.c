/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:20:06 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/30 15:16:33 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	put_string_materials(t_prog *prog, t_win_button *win_btn)
{
	size_t	i;

	i = -1;
	while (++i < prog->scene->nb_materials)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			25, 50 + i * 20,
			TEXT_COLOR, prog->scene->materials[i].name);
	}
}

static void	put_string_objects(t_win_button *win_btn)
{
	const int	stw = (win_btn->width - 30) / SUB_COUNT;
	int			sx;
	int			i;

	sx = 15;
	i = -1;
	while (++i < SUB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, sx + 5,
			TAB_HEIGHT + 15, TEXT_COLOR,
			(char *[]){"Sphere", "Plane", "Cylinder", "Cone"}[i]);
		sx += stw + 5;
	}
}

static void	put_string_lights(t_prog *prog, t_win_button *win_btn)
{
	char	ratio_str[12];
	char	color_ambient_light[23];

	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		CONTROL_WINDOW_WIDTH / 2 - 50, TAB_HEIGHT + 25,
		TEXT_COLOR, "Ambient Lightning:");
	snprintf(ratio_str, 12, "Ratio: %.2f", prog->scene->ambient_light.ratio);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		20, SLIDER_RATIO_AMBIENT_HEIGHT + 13,
		TEXT_COLOR, ratio_str);
	snprintf(color_ambient_light, 23, "Color: (%d, %d, %d)",
		(int)(prog->scene->ambient_light.color.x * 255),
		(int)(prog->scene->ambient_light.color.y * 255),
		(int)(prog->scene->ambient_light.color.z) * 255);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		CONTROL_WINDOW_WIDTH / 2 - 60, SLIDER_RATIO_AMBIENT_HEIGHT * 1.5 + 13,
		TEXT_COLOR, color_ambient_light);
}

void	put_string_win(t_prog *prog, t_win_button *win_btn)
{
	int	i;

	i = -1;
	while (++i < TAB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 30 - i * 2,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, win_btn->tab_buttons[i].text);
	}
	if (win_btn->current_tab == TAB_LIGHTS)
		put_string_lights(prog, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		put_string_objects(win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS)
		put_string_materials(prog, win_btn);
}

#endif
