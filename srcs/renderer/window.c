/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/24 17:09:04 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/memory.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
}

void	init_win(t_prog *prog)
{
	t_win_scene	*win;

	win = prog->win_scene;
	win->height = HEIGHT;
	win->width = WIDTH;
	win->half_width = HEIGHT / 2;
	win->half_height = WIDTH / 2;
	win->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		print_exit(prog, "Mlx init failed");
	mlx_do_key_autorepeaton(prog->win_scene->mlx_ptr);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
			win->height, "miniRT");
	if (!win->win_ptr)
		print_exit(prog, "Mlx new_window failed");
	if (create_img(win) == -1)
		print_exit(prog, "Mlx create img failed");
	mlx_loop_hook(prog->win_scene->mlx_ptr, new_frame, prog);
	mlx_hook(win->win_ptr, ON_DESTROY, MOUSEDOWN_MASK, window_close, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(win->height * win->width, sizeof(t_vec3)),
		(void **)&win->accumulation_data, prog);
	init_button_window(prog);
	/* ----------------------------- // mouse hooks // ----------------------------- */
	mlx_hook(win->win_ptr, ON_MOUSEDOWN, MOUSEDOWN_MASK, mouse_down, prog);
	mlx_hook(win->win_ptr, ON_MOUSEUP, MOUSEUP_MASK, mouse_up, prog);
	/* ------------------------------ // key hooks // ------------------------------- */
	mlx_hook(win->win_ptr, ON_KEYDOWN, KEYDOWN_MASK, key_down, prog);
	mlx_hook(win->win_ptr, ON_KEYUP, KEYUP_MASK, key_up, prog);
	mlx_loop(win->mlx_ptr);
}
