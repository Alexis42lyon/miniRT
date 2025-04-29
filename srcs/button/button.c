/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:54 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/29 18:42:56 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "button.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#if SHOW_BUTTON

static void	draw_tab_objects(t_win_button *win_btn, t_data *img, int stw)
{
	int			i;
	int			j;
	int			k;
	int			sx;

	sx = 15;
	i = -1;
	while (++i < SUB_COUNT)
	{
		j = sx - 1;
		while (++j < sx + stw)
		{
			k = TAB_HEIGHT - 1;
			while (++k < TAB_HEIGHT * 2)
			{
				if (win_btn->current_subtab == (enum e_subtab)i)
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
				else
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8)) = TAB_COLOR;
			}
		}
		sx += stw + 5;
	}
}

static void	draw_tabs(t_data *img, t_win_button *win_btn)
{
	int		i;
	int		j;
	int		k;

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
				if (win_btn->current_tab == (enum e_tab)i)
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
				else
					*(int *)(img->addr + k * img->line_length + j
							* (img->bits_per_pixel / 8)) = TAB_COLOR;
			}
		}
	}
	if (win_btn->current_tab == TAB_OBJECTS)
		draw_tab_objects(win_btn, img, (win_btn->width - 30) / SUB_COUNT);
}

static void	draw_button_window(t_prog *prog, t_win_button *win_btn)
{
	t_data	img;

	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_tabs(&img, win_btn);
	draw_slider(50, 100, win_btn->ambient_ratio, &img);
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
	put_string_win(prog, win_btn);
}

static int	handle_mouse_move(int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	float			new_ratio;

	(void)y;
	win_btn = prog->win_button;
	if (win_btn->is_dragging && win_btn->current_tab == TAB_LIGHTS)
	{
		x = fmax(15, fmin(x, 15 + SLIDER_WIDTH));
		new_ratio = (float)(x - 15) / SLIDER_WIDTH;
		new_ratio = fmaxf(0.0f, fminf(1.0f, new_ratio));
		win_btn->ambient_ratio = new_ratio;
		prog->scene->ambient_light.ratio = new_ratio;
		draw_button_window(prog, win_btn);
	}
	reset_accumulation(prog);
	return (0);
}


static int	handle_button_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;

	win_btn = prog->win_button;
	if (button == 1)
	{
		handle_tabs(prog, win_btn, x, y);
		if (win_btn->current_tab == TAB_LIGHTS && x >= 25
			&& x <= 25 + SLIDER_WIDTH && y >= 80 && y <= 80 + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
	return (0);
}

static int	handle_mouse_up(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	(void)button;
	prog->win_button->is_dragging = 0;
	return (0);
}

static int	key_hook_btn(int keycode, t_prog *prog)
{
	if (keycode == ESC)
		free_all(prog);
	return (0);
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;
	const float		tab_width = CONTROL_WINDOW_WIDTH / TAB_COUNT;

	win_btn = prog->win_button;
	*win_btn = (t_win_button){
		.width = CONTROL_WINDOW_WIDTH,
		.height = prog->win_scene->height,
		.mlx_ptr = prog->win_scene->mlx_ptr,
		.win_ptr = mlx_new_window(prog->win_scene->mlx_ptr,
			CONTROL_WINDOW_WIDTH, prog->win_scene->height, "Control Panel"),
		.current_tab = TAB_LIGHTS,
		.ambient_ratio = prog->scene->ambient_light.ratio,
		.is_dragging = 0
	};
	i = -1;
	while (++i < TAB_COUNT)
	{
		win_btn->tab_buttons[i] = (t_button)
		{
			.x = i * tab_width,
			.y = 0,
			.width = tab_width,
			.height = TAB_HEIGHT,
			.text = (char *[]){"Lights", "Objects", "Materials"}[i]
		};
	}
	mlx_hook(win_btn->win_ptr, 2, 1L << 0, key_hook_btn, prog);
	mlx_hook(win_btn->win_ptr, 17, 0, window_close, prog);
	mlx_hook(win_btn->win_ptr, 4, 1L << 2, handle_button_click, prog);
	mlx_hook(win_btn->win_ptr, 6, 1L << 6, handle_mouse_move, prog);
	mlx_hook(win_btn->win_ptr, 5, 1L << 3, handle_mouse_up, prog);
	draw_button_window(prog, win_btn);
}

#else

void	init_button_window(t_prog *prog)
{
	(void)prog;
}

#endif
