/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:54 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 08:33:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

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

static void	init_struct(t_prog *prog, t_win_button *win_btn)
{
	int				i;

	*win_btn = (t_win_button)
	{
		.width = CONTROL_WINDOW_WIDTH,
		.height = HEIGHT,
		.mlx_ptr = prog->win_scene->mlx_ptr,
		.win_ptr = mlx_new_window(prog->win_scene->mlx_ptr,
			CONTROL_WINDOW_WIDTH, HEIGHT, "Control Panel"),
		.current_tab = TAB_LIGHTS,
		.is_dragging = 0,
	};
	if (!win_btn->win_ptr)
		print_exit(prog, "Failed to create control window.");
	i = -1;
	while (++i < TAB_COUNT)
	{
		win_btn->tab_buttons[i] = (t_button)
		{
			.x = i * CONTROL_WINDOW_WIDTH / TAB_COUNT,
			.y = 0,
			.width = CONTROL_WINDOW_WIDTH / TAB_COUNT,
			.height = TAB_HEIGHT,
		};
	}
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	t_button		*btns[6];

	if (HEIGHT < 250 || CONTROL_WINDOW_WIDTH < 300)
	{
		ft_log(ERROR,
			"Error: Window dimensions are too small for panel control.");
		return ;
	}
	win_btn = prog->win_button;
	init_struct(prog, win_btn);
	init_button(win_btn, btns);
	init_sphere_buttons(win_btn);
	init_plane_buttons(win_btn);
	init_cylinder_buttons(win_btn);
	init_cone_buttons(win_btn);
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
